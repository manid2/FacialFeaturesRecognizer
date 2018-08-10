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

#include "opencv2/core/core.hpp"
#include "opencv2/contrib/contrib.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <logger.h>

namespace FFR {

/**
 * Class to contain the facial features recognition operations
 */
class BaseRecognizer {
 public:
  BaseRecognizer(void);
  virtual ~BaseRecognizer();

  // simple test for logger
  void printLog(void);

 public:
  // TODO: YTI, member functions and variables
};

extern int execute(int argc, char **argv);

} /* namespace FFR */

#endif /* FFR_INC_BASERECOGNIZER_H_ */
