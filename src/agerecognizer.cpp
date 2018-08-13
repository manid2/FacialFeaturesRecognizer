/****************************************************************************\
 * Copyright (c) 2018 Mani Kumar <maniyoung.d2@gmail.com>
 * ---------------------------------------------------------------------------
 * Project     :  FacialFeaturesRecognizer
 * Author      :  Mani Kumar
 * License     :  GNU GPL v3
 * Origin date :  08-Aug-2018
 *
 * Filename    :  agerecognizer.cpp
 * Description :  Concrete class for age recognition
 \***************************************************************************/

#include <agerecognizer.h>

namespace FFR {

bool AgeRecognizer::isSVMLoaded = false;

AgeRecognizer::AgeRecognizer()
    : _className(FUNC_NAME) {
  m_recognizerName = TO_STR(Age);
  m_result = AGE_RESULT_ADULT;
}

AgeRecognizer::~AgeRecognizer() {
  DEBUGLD("destructor called!");
}

FFR::String AgeRecognizer::getResult() {
  // TODO: YTI recognition logic
  return m_result;
}

} /* namespace FFR */
