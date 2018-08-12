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
  /// should recognize all features by default
  m_features.insert(FFR::Age);
  m_features.insert(FFR::Emotion);
  m_features.insert(FFR::Gender);

  /// putText params
  m_fontFace = cv::FONT_HERSHEY_SIMPLEX;
  m_fontScale = 0.75f;
  m_fontColor = Scalar(240, 40, 240);
  m_lineType = 8;
}

BaseRecognizer::~BaseRecognizer() {
  // TODO: YTI
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
    /// Load cascade classifier
    m_faceCascade.load("haarcascade_frontalface_default.xml");
    if (m_faceCascade.empty()) {
      err = FFR::ImageReadError;
      DEBUGLE("Error reading Cascade Classifier\n");
      break;
    }

    Mat frame;
    while (1) {
      cap >> frame;
      if (frame.empty()) {
        err = FFR::ImageReadError;
        DEBUGLE("Error reading video stream or file\n");
        break;
      }

      /// Detect faces in the frame
      cv::Mat frame_gray;
      std::vector<Rect> faces;
      err = this->detectFace(frame, faces, frame_gray);

      /// Recognize facial features
      std::vector<ResultsSet> results(faces.size());
      this->recognizeFeatures(m_features, results, frame_gray, faces);

      /// Draw the results on the original frame
      this->drawResults(frame, faces, m_features, results);

      /// Display the resulting frame
      imshow("video", frame);

      /// Press  ESC or 'q' on keyboard to exit
      char c = (char) waitKey(10);
      if (c == 27 || c == 'q') {
        err = FFR::OK;
        DEBUGLD("Pressed=[0x%x], reading video stream or file exit\n", (int )c);
        break;
      }
    }  // while(1)
  } while (0);

  return err;
}

ErrorCode BaseRecognizer::detectFace(cv::Mat& frame, std::vector<Rect>& faces,
                                     cv::Mat& frame_gray) {
  ErrorCode err = FFR::OK;

  do {  // for common error handling
    /// Pre-process input frame for face detection
    cvtColor(frame, frame_gray, CV_BGR2GRAY);
    equalizeHist(frame_gray, frame_gray);

    /// Detect faces
    m_faceCascade.detectMultiScale(frame_gray, faces, 1.1, 3,
                                   0 | CV_HAAR_SCALE_IMAGE, Size(30, 30));

  } while (0);

  return err;
}

ErrorCode BaseRecognizer::recognizeFeatures(const FeaturesSet& features,
                                            vector<ResultsSet>& results,
                                            cv::Mat& frame_gray,
                                            std::vector<cv::Rect>& faces) {
  ErrorCode err = FFR::OK;

  do {  // for common error handling
    /// pre-process faces to get HOG fv

    cv::Mat face_mat;  // dont modify frame_gray
    for (size_t fa = 0; fa < faces.size(); fa++) {
      /// observed seg fault here, hence putting try-catch block
      try {
        /// 1. crop the face from the frame
        face_mat = frame_gray(faces.at(fa));

        /// 2. resize to 50,50
        cv::resize(face_mat, face_mat, cv::Size(50, 50));

        /// 3. get HOG fv

        /// 4. make predictions for each feature
        FeaturesSet::iterator itr_f = features.begin();
        for (; itr_f != features.end(); itr_f++) {
          FFRecognizer ffr;
          ffr.fr = FFR::getRecognizer(*itr_f);
          results.at(fa).insert(ffr.fr->getResult());
        }
      } catch (const cv::Exception& e) {
        // ignore any error after printing its message
        stringstream ss;
        ss << faces.at(fa);
        DEBUGLE("raised cv exception, faces[%ld]: rect=%s, face_gray\n", fa,
                ss.str().c_str());
      } catch (...) {
        // ignore any error after printing its message
        DEBUGLE("raised an unknown exception\n");
      }
    }
  } while (0);

  return err;
}

ErrorCode BaseRecognizer::drawResults(cv::Mat& frame,
                                      const std::vector<cv::Rect>& faces,
                                      const FeaturesSet& features,
                                      const std::vector<ResultsSet>& results) {
  ErrorCode err = FFR::OK;

  do {  // for common error handling

    for (size_t fa = 0; fa < faces.size(); fa++) {
      /// 1. Draw ellipses around the faces
      const Rect& face_rect = faces.at(fa);
      Point center(face_rect.x + face_rect.width * 0.5,
                   face_rect.y + face_rect.height * 0.5);
      ellipse(frame, center,
              Size(face_rect.width * 0.5, face_rect.height * 0.5), 0, 0, 360,
              Scalar(255, 0, 0), 4, 8, 0);
      /// 2. Draw features results text near the faces
      FeaturesSet::iterator itr_f = features.begin();
      ResultsSet::iterator itr_r = results.at(fa).begin();
      for (int li = 0; itr_f != features.end(); itr_f++, itr_r++, li += 22) {
        const FFR::Feature& f = *itr_f;
        putText(frame, format("%s: %s", enum2str(f).c_str(), itr_r->c_str()),
                Point(face_rect.x, face_rect.y + li), m_fontFace, m_fontScale,
                m_fontColor, 2);
      }
    }
  } while (0);

  return err;
}

int execute(int argc, char **argv) {
  ErrorCode err = FFR::OK;
  BaseRecognizer br;
  /// Detect facial features in the video stream
  err = br.readVideoFromFile();

  return static_cast<int>(err);
}

} /* namespace FFR */