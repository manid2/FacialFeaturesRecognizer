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
  //CvMat sample = cvCreateMat(1, 64, CV_32FC1); // TODO: not sure how to use this!!
  // Work around, create c++ mat and convert it to CvMat
  //cv::Mat hog_mat(m_HOGFeatures, true);
  CvMat sample = cvMat(1, 64, CV_32FC1, &m_HOGFeatures[0]);
  cvCreateData(&sample);

  //CvMat sample = hog_mat;  // cvMat(1, 64, CV_32FC1, &m_HOGFeatures[0]);

  /*// NOTE: not able to understand below code from `letter_recog.cpp` opencv sample
   for (int j = ntrain_samples; j < nsamples_all; j++) {
   float *s = data->data.fl + j * var_count;

   for (int i = 0; i < var_count; i++) {
   sample.data.fl[(j - ntrain_samples) * var_count + i] = s[i];
   }
   true_results[j - ntrain_samples] = responses->data.fl[j];
   }*/

  float svm_res = 0.0f;
  // FIXME seg fault,
  // OpenCV Error: Bad argument (The sample is not a valid vector)
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
