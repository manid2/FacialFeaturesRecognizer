/****************************************************************************\
 * Copyright (c) 2018 Mani Kumar <maniyoung.d2@gmail.com>
 * ---------------------------------------------------------------------------
 * Project     :  FacialFeaturesRecognizer
 * Author      :  Mani Kumar
 * License     :  GNU GPL v3
 * Origin date :  08-Aug-2018
 *
 * Filename    :  baserecognizer.cpp
 * Description :  Base class for facial features recognizer.
 \***************************************************************************/

#include <baserecognizer.h>

using namespace cv;
using namespace std;

namespace FFR {

BaseRecognizer::BaseRecognizer()
    : _className(FUNC_NAME) {
  // should recognize all features by default
  m_features.insert(FFR::Age);
  m_features.insert(FFR::Emotion);
  m_features.insert(FFR::Gender);

  // putText params
  m_fontFace = cv::FONT_HERSHEY_SIMPLEX;
  m_fontScale = 0.75f;
  m_fontColor = Scalar(240, 40, 240);
  m_lineType = 8;

  m_ffrVec.reserve(m_features.size());
}

BaseRecognizer::~BaseRecognizer() {
  for (auto fr : m_ffrVec) {
    if (fr)
      delete fr;
  }
}

void BaseRecognizer::printLog() {
  DEBUGLE(" hello world\n");
}

ErrorCode BaseRecognizer::readVideoFromFile(const std::string& vidFileName) {
  ErrorCode err = FFR::OK;
  do {  // for common error handling
    VideoCapture cap(vidFileName);
    // Check if camera opened successfully
    if (!cap.isOpened()) {
      err = FFR::ImageReadError;
      DEBUGLE("Error opening video stream or file\n");
      break;
    }

    err = this->readVideo(cap);

    cap.release();
    destroyAllWindows();
  } while (0);
  return err;
}

ErrorCode BaseRecognizer::readVideoFromCam(const int id) {
  ErrorCode err = FFR::OK;
  do {  // for common error handling
    VideoCapture cap(id);
    // Check if camera opened successfully
    if (!cap.isOpened()) {
      err = FFR::ImageReadError;
      DEBUGLE("Error opening video stream or file\n");
      break;
    }

    err = this->readVideo(cap);

    cap.release();
    destroyAllWindows();
  } while (0);
  return err;
}

ErrorCode BaseRecognizer::readVideo(cv::VideoCapture& cap) {
  ErrorCode err = FFR::OK;
  do {  // for common error handling
    // one-time (expensive calls) initialization functions,
    // i.e. loading models, classifiers
    this->init();

    Mat frame;
    while (1) {
      cap >> frame;
      if (frame.empty()) {
        err = FFR::ImageReadError;
        DEBUGLE("Error reading video stream or file\n");
        break;
      }

      // read the frame as image
      this->readImage(frame);

      // Display the resulting frame
      imshow("video", frame);

      // Press  ESC or 'q' on keyboard to exit
      char c = (char) waitKey(10);
      if (c == 27 || c == 'q') {
        err = FFR::OK;
        DEBUGLD("Pressed=[0x%x], reading video stream or file exit\n", (int )c);
        break;
      }
    }  // while(1)

    // TODO: YTI, finish(), to clean up resources and also to make it
    // available outside the class, i.e. for unit testing.
  } while (0);
  return err;
}

ErrorCode BaseRecognizer::init() {
  ErrorCode err = FFR::OK;
  do {  // for common error handling
    this->loadClassifier("");
    this->initRecognizers();
  } while (0);
  return err;
}

ErrorCode BaseRecognizer::loadClassifier(const FFR::String& /*fileName*/) {
  ErrorCode err = FFR::OK;
  do {  // for common error handling
    // Load cascade classifier
    m_faceCascade.load("haarcascade_frontalface_default.xml");
    if (m_faceCascade.empty()) {
      err = FFR::ImageReadError;
      DEBUGLE("Error reading Cascade Classifier\n");
      break;
    }
  } while (0);
  return err;
}

ErrorCode BaseRecognizer::initRecognizers(void) {
  ErrorCode err = FFR::OK;
  do {  // for common error handling
    // get recognizers for each feature
    FeaturesSet::iterator itr_f = m_features.begin();
    for (; itr_f != m_features.end(); itr_f++) {
      FeaturesRecognizer* fr = FFR::getRecognizer(*itr_f);
      if (fr && !fr->loadSVM()) {
        err = FFR::GenericError;
        DEBUGLE("SVM load failed for [%s]\n", enum2str(*itr_f).c_str());
        break;
      }
      m_ffrVec.push_back(fr);
    }
  } while (0);
  return err;
}

ErrorCode BaseRecognizer::readImageFromFile(const FFR::String& fileName,
                                            cv::Mat& img_o) {
  ErrorCode err = FFR::OK;
  do {  // for common error handling
    cv::Mat img = cv::imread(fileName);  // load image in default
    this->readImage(img);
    img_o = img;
    // currently using this just for unit testing, will extend in future
  } while (0);
  return err;
}

ErrorCode BaseRecognizer::readImage(cv::Mat& img) {
  ErrorCode err = FFR::OK;
  do {
    // Detect faces in the image
    cv::Mat frame_gray;
    std::vector<Rect> faces;
    err = this->detectFace(img, faces, frame_gray);

    // Recognize facial features
    m_resultsVec = ResultsVec(faces.size());
    this->recognizeFeatures(m_features, m_resultsVec, frame_gray, faces);

    // Draw the results on the original image
    this->drawResults(img, faces, m_features, m_resultsVec);
  } while (0);
  return err;
}

ErrorCode BaseRecognizer::detectFace(cv::Mat& frame, std::vector<Rect>& faces,
                                     cv::Mat& frame_gray) {
  ErrorCode err = FFR::OK;
  do {  // for common error handling
    // Pre-process input frame for face detection
    cvtColor(frame, frame_gray, CV_BGR2GRAY);
    equalizeHist(frame_gray, frame_gray);

    // Detect faces
    m_faceCascade.detectMultiScale(frame_gray, faces, 1.1, 3,
                                   0 | CV_HAAR_SCALE_IMAGE, Size(30, 30));

  } while (0);
  return err;
}

ErrorCode BaseRecognizer::recognizeFeatures(const FeaturesSet& features,
                                            ResultsVec& results,
                                            cv::Mat& frame_gray,
                                            std::vector<cv::Rect>& faces) {
  ErrorCode err = FFR::OK;
  do {  // for common error handling
    cv::Mat face_mat;  // dont modify frame_gray
    for (size_t fa = 0; fa < faces.size(); fa++) {
      // 1. crop the face from the frame
      face_mat = frame_gray(faces.at(fa));

      // 2. resize to 50,50
      cv::resize(face_mat, face_mat, cv::Size(50, 50));

      // 3. get HOG fv
      std::vector<float> hog_fv;
      this->computeHOG(face_mat, hog_fv);

      // 4. make predictions for each feature
      std::vector<FFR::FeaturesRecognizer*>::iterator itr_ffr =
          m_ffrVec.begin();
      for (; itr_ffr != m_ffrVec.end(); itr_ffr++) {
        FFR::String res = (*itr_ffr)->getResult(hog_fv);
        ResultPair res_pair((*itr_ffr)->getFeatureType(), res);
        results.at(fa).insert(res_pair);
      }
    }
  } while (0);
  return err;
}

ErrorCode BaseRecognizer::computeHOG(const cv::Mat& img,
                                     std::vector<float>& hog_features) {
  ErrorCode err = FFR::OK;
  do {  // for common error handling
    // NOTE: Confirmed this is the same hog function as calculated in the python
    // script used in training the SVM model.
    m_HOGDescriptor.compute(img, hog_features);
  } while (0);
  return err;
}

ErrorCode BaseRecognizer::drawResults(cv::Mat& frame,
                                      const std::vector<cv::Rect>& faces,
                                      const FeaturesSet& features,
                                      const ResultsVec& results) {
  ErrorCode err = FFR::OK;
  do {  // for common error handling
    for (size_t fa = 0; fa < faces.size(); fa++) {
      // 1. Draw ellipses around the faces
      const Rect& face_rect = faces.at(fa);
      Point center(face_rect.x + face_rect.width * 0.5,
                   face_rect.y + face_rect.height * 0.5);
      ellipse(frame, center,
              Size(face_rect.width * 0.5, face_rect.height * 0.5), 0, 0, 360,
              Scalar(255, 0, 0), 4, 8, 0);
      // 2. Draw features results text near the faces
      int li = 0;
      // for each face in the results vector iterate through the results pair set
      for (auto res_pair : results.at(fa)) {
        // extract results data here
        const FFR::Feature& f = res_pair.first;
        const FFR::String& res = res_pair.second;

        // put text on the frame
        putText(frame, format("%-10s: %s", enum2str(f).c_str(), res.c_str()),
                Point(face_rect.x, face_rect.y + li), m_fontFace, m_fontScale,
                m_fontColor, 2);
        li += 22;
      }
    }
  } while (0);
  return err;
}

/**
 * Entry point into the application
 */
int execute(int argc, char **argv) {
  ErrorCode err = FFR::OK;

  // Detect facial features in the default video stream
  BaseRecognizer br;
  err = br.readVideoFromFile();

  return static_cast<int>(err);
}

} /* namespace FFR */
