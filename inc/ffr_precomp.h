/****************************************************************************\
 * Copyright (c) 2018 Mani Kumar <maniyoung.d2@gmail.com>
 * ---------------------------------------------------------------------------
 * Project     :  FacialFeaturesRecognizer
 * Author      :  Mani Kumar
 * License     :  GNU GPL v3
 * Origin date :  08-Aug-2018
 *
 * Filename    :  precomp.hpp
 * Description :  Precompiled header to store common error codes and constants
 \***************************************************************************/

#ifndef FFR_INC_PRECOMP_H_
#define FFR_INC_PRECOMP_H_

namespace FFR {

// PDF creation error codes.
enum ErrorCode {
  OK = 0,
  GenericError = -100,
  FileOpenError,
  FileWriteError,
  ImageReadError,
  ImageWriteError,
  FaceDetectError
};

}  // namesapce FFR

#endif /* FFR_INC_PRECOMP_H_ */
