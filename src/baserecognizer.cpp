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

BaseRecognizer::BaseRecognizer() {
  // TODO: YTI
}

BaseRecognizer::~BaseRecognizer() {
  // TODO: YTI
}

void BaseRecognizer::printLog() {
  DEBUGLE(" hello world\n");
}

ErrorCode BaseRecognizer::detectFace(const std::string& vidFileName) {
  ErrorCode err = FFR::OK;

  do {  // for common error handling

    VideoCapture cap(vidFileName);
    // Check if camera opened successfully
    if (!cap.isOpened()) {
      err = FFR::ImageReadError;
      DEBUGLE("Error opening video stream or file\n");
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

      // Display the resulting frame
      imshow("video", frame);

      // Press  ESC or 'q' on keyboard to exit
      char c = (char) waitKey(25);
      if (c == 27 || c == 'q') {
        err = FFR::OK;
        DEBUGLD("Pressed=[0x%x], reading video stream or file exit\n", (int )c);
        break;
      }
    }  // while(1)

    cap.release();
    destroyAllWindows();
  } while (0);

  return err;
}

int execute(int argc, char **argv) {
  ErrorCode err = FFR::OK;
  BaseRecognizer br;
  /// Detect face
  err = br.detectFace();

  return static_cast<int>(err);
}

} /* namespace FFR */
