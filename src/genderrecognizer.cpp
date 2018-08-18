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

GenderRecognizer::GenderRecognizer()
    : _className(FUNC_NAME) {
  m_featureType = FFR::Gender;
  m_featureName = enum2str(m_featureType);
  m_result = GENDEDR_RESULT_MALE;
}

GenderRecognizer::~GenderRecognizer() {
  DEBUGLD("destructor called!\n");
}

FFR::String GenderRecognizer::getResult(/*const*/std::vector<float>& hog_fv) {
  //CvMat sample = cvCreateMat(1, 64, CV_32FC1);
  // TODO: not sure how to use this!!
  // Work around, create c++ mat and convert it to CvMat
  //cv::Mat hog_mat(m_HOGFeatures, true);

  CvMat sample = cvMat(1, 64, CV_32FC1, hog_fv.data());
  cvCreateData(&sample);
  float svm_res = 0.0f;
  svm_res = m_SVMobj.predict(&sample);
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
