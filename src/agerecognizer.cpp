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

AgeRecognizer::AgeRecognizer()
    : _className(FUNC_NAME) {
  m_result = AGE_RESULT_ADULT;
}

AgeRecognizer::~AgeRecognizer() {
  // TODO Auto-generated destructor stub
}

FFR::String AgeRecognizer::getResult() {
  // TODO: YTI recognition logic
  return m_result;
}

} /* namespace FFR */
