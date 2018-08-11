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

namespace FFR {

BaseRecognizer::BaseRecognizer()
    : _className(FUNC_NAME) {
  // TODO: YTI
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

      /// pre-process faces to get HOG fv
      /// 1. crop the face

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

    for (size_t i = 0; i < faces.size(); i++) {
      Point center(faces[i].x + faces[i].width * 0.5,
                   faces[i].y + faces[i].height * 0.5);
      ellipse(frame, center, Size(faces[i].width * 0.5, faces[i].height * 0.5),
              0, 0, 360, Scalar(255, 0, 0), 4, 8, 0);
    }
  } while (0);

  return err;
}

int execute(int argc, char **argv) {
  ErrorCode err = FFR::OK;
  BaseRecognizer br;
  /// Detect face on the video stream
  err = br.readVideoFromFile();

  return static_cast<int>(err);
}

} /* namespace FFR */
