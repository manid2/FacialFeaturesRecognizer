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
  CvMat sample = cvMat(1, 64, CV_32FC1, &m_HOGFeatures[0]);
  float svm_res = 0.0f;
  // FIXME seg fault,
  // OpenCV Error: Bad argument (The SVM should be trained first) in CvSVM::predict,
  // svm_res =  m_SVMobj.predict(&sample);

  // TODO: need to refactor to make robust
  switch ((int) svm_res) {
    case 0:
      m_result = GENDEDR_RESULT_MALE;
      break;
    case 1:
      m_result = GENDEDR_RESULT_FEMALE;
      break;
    default:
      m_result = GENDEDR_RESULT_MALE;
      DEBUGLW("default case, svm_res=[%lf]\n", svm_res);
      break;
  }

  return m_result;
}

} /* namespace FFR */
