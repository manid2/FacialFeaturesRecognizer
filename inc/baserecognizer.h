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

#include "opencv2/core/core.hpp"
#include "opencv2/contrib/contrib.hpp"
#include "opencv2/highgui/highgui.hpp"

namespace FFR {

/**
 * Class to interact with the FeaturesRecognizer and with the UI.
 * It handles the pre-processing of the input image for feature vector
 * generation and displaying the result on the UI
 */
class BaseRecognizer {
 public:
  BaseRecognizer(void);
  virtual ~BaseRecognizer();

  // simple test for logger
  void printLog(void);

 public:
  ErrorCode detectFace(const std::string& vidFileName = "test.m4v");
};

extern int execute(int argc, char **argv);

} /* namespace FFR */

#endif /* FFR_INC_BASERECOGNIZER_H_ */
