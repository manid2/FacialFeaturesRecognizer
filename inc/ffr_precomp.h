/****************************************************************************\
 * Copyright (c) 2018 Mani Kumar <maniyoung.d2@gmail.com>
 * ---------------------------------------------------------------------------
 * Project     :  FacialFeaturesRecognizer
 * Author      :  Mani Kumar
 * License     :  GNU GPL v3
 * Origin date :  08-Aug-2018
 *
 * Filename    :  ffr_precomp.h
 * Description :  Precompiled header to store common error codes and constants
 \***************************************************************************/

#ifndef FFR_INC_FFR_PRECOMP_H_
#define FFR_INC_FFR_PRECOMP_H_

#include <string>

namespace FFR {

#define TO_STR(e) #e

//! Error codes.
enum ErrorCode {
  OK = 0,
  GenericError = -100,
  FileOpenError,
  FileWriteError,
  ImageReadError,
  ImageWriteError,
  FaceDetectError
};

//! Feature types
enum Feature {
  Feature_Undefined = -1,
  Age = 0,
  Emotion,
  Gender
};

static std::string enum2str(Feature f) {
  std::string en;

#define CASE(fe)\
  case fe:\
     en = TO_STR(fe);\
     break;

  switch (f) {
    CASE(Age)
    CASE(Emotion)
    CASE(Gender)
  }
#undef CASE
//#undef TO_STR

  return en;
}

// NOTE: the below macros must match the integer values used in
// training the SVM models
#define AGE_RESULT_CHILD         ("child [5-10]")
#define AGE_RESULT_TEEN          ("teen [11-20]")
#define AGE_RESULT_ADULT         ("adult [21-40]")
#define AGE_RESULT_OLD           ("old [40+]")

#define EMOTION_RESULT_ANGER     ("anger")
#define EMOTION_RESULT_CONTEMPT  ("contempt")
#define EMOTION_RESULT_HAPPY     ("happy")
#define EMOTION_RESULT_NEUTRAL   ("neutral")
#define EMOTION_RESULT_SAD       ("sad")
#define EMOTION_RESULT_SURPRISE  ("surprise")

#define GENDEDR_RESULT_MALE      ("male")
#define GENDEDR_RESULT_FEMALE    ("female")

}  // namesapce FFR

#endif /* FFR_INC_FFR_PRECOMP_H_ */
