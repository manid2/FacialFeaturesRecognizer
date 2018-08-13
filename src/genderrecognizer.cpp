/****************************************************************************\
 * Copyright (c) 2018 Mani Kumar <maniyoung.d2@gmail.com>
 * ---------------------------------------------------------------------------
 * Project     :  FacialFeaturesRecognizer
 * Author      :  Mani Kumar
 * License     :  GNU GPL v3
 * Origin date :  08-Aug-2018
 *
 * Filename    :  genderrecognizer.h
 * Description :  Concrete class for gender recognition
 \***************************************************************************/

#include <genderrecognizer.h>

namespace FFR {

bool GenderRecognizer::isSVMLoaded = false;

GenderRecognizer::GenderRecognizer()
    : _className(FUNC_NAME) {
  m_recognizerName = TO_STR(Gender);
  m_result = GENDEDR_RESULT_MALE;
}

GenderRecognizer::~GenderRecognizer() {
  DEBUGLD("destructor called!\n");
}

FFR::String GenderRecognizer::getResult() {
  // TODO: YTI recognition logic
  return m_result;
}

} /* namespace FFR */
