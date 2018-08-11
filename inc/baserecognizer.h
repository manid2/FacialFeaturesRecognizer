/****************************************************************************\
 * Copyright (c) 2018 Mani Kumar <maniyoung.d2@gmail.com>
 * ---------------------------------------------------------------------------
 * Project     :  FacialFeaturesRecognizer
 * Author      :  Mani Kumar
 * License     :  GNU GPL v3
 * Origin date :  08-Aug-2018
 *
 * Filename    :  baserecognizer.h
 * Description :  Base class for facial features recognizer.
 \***************************************************************************/

#ifndef FFR_INC_BASERECOGNIZER_H_
#define FFR_INC_BASERECOGNIZER_H_

#include <ffr_precomp.h>
#include <logger.h>

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

namespace FFR {

/**
 * Class to interact with the FeaturesRecognizer and with the UI.
 * It handles the pre-processing of the input image for feature vector
 * generation and displaying the result on the UI
 */
class BaseRecognizer {
 public:
  const FFR::String _className;
  BaseRecognizer(void);
  virtual ~BaseRecognizer();

  // simple test for logger
  void printLog(void);

 public:
  ErrorCode readVideoFromFile(const std::string& vidFileName = "test.m4v");
  ErrorCode readVideoFromCam(const int id = 0);
  ErrorCode detectFace(cv::Mat& frame, std::vector<cv::Rect>& faces,
                       cv::Mat& frame_gray);

 private:
  cv::CascadeClassifier m_faceCascade;
  ErrorCode readVideo(cv::VideoCapture& cap);
};

extern int execute(int argc, char **argv);

} /* namespace FFR */

#endif /* FFR_INC_BASERECOGNIZER_H_ */
