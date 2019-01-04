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

#include <GenderRecognizer.h>

namespace FFR {

GenderRecognizer::GenderRecognizer()
    : _className(FUNC_NAME) {
  m_featureType = FFR::Gender;
  m_featureName = enum2str(m_featureType);
  m_result = GENDEDR_RESULT_MALE;
}

GenderRecognizer::~GenderRecognizer() {
  DEBUGLD("destructor called!\n");
}

FFR::String GenderRecognizer::getResult(const cv::Mat& ml_pred_data) {
  int svm_res = 0;
  cv::Mat responses_mat;
  m_pSVM->predict(ml_pred_data, responses_mat);
  svm_res = responses_mat.at<int>(0);
  switch (svm_res) {
    case 0:
      m_result = GENDEDR_RESULT_MALE;
      break;
    case 1:
      m_result = GENDEDR_RESULT_FEMALE;
      break;
    default:
      m_result = GENDEDR_RESULT_MALE;
      DEBUGLW("default case, svm_res=[%d]\n", svm_res);
      break;
  }
  return m_result;
}

} /* namespace FFR */
