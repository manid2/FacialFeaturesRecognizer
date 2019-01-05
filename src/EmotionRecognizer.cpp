/****************************************************************************\
 * Copyright (c) 2018 Mani Kumar <maniyoung.d2@gmail.com>
 * ---------------------------------------------------------------------------
 * Project     :  FacialFeaturesRecognizer
 * Author      :  Mani Kumar
 * License     :  GNU GPL v3
 * Origin date :  08-Aug-2018
 *
 * Filename    :  emotionrecognizer.cpp
 * Description :  Concrete class for emotion recognition
 \***************************************************************************/

#include <EmotionRecognizer.h>

namespace FFR {

EmotionRecognizer::EmotionRecognizer()
    : _className(FUNC_NAME) {
  m_featureType = FFR::Emotion;
  m_featureName = enum2str(m_featureType);
  m_result = EMOTION_RESULT_NEUTRAL;
}

EmotionRecognizer::~EmotionRecognizer() {
  DEBUGLD("destructor called!\n");
}

FFR::String EmotionRecognizer::getResult(const cv::Mat& ml_pred_data) {
  int svm_res = 0;
  cv::Mat responses_mat;
  m_pSVM->predict(ml_pred_data, responses_mat);
  svm_res = responses_mat.at<int>(0);
  switch (svm_res) {
    case 0:
      m_result = EMOTION_RESULT_ANGER;
      break;
    case 1:
      m_result = EMOTION_RESULT_CONTEMPT;
      break;
    case 2:
      m_result = EMOTION_RESULT_HAPPY;
      break;
    case 3:
      m_result = EMOTION_RESULT_NEUTRAL;
      break;
    case 4:
      m_result = EMOTION_RESULT_SAD;
      break;
    case 5:
      m_result = EMOTION_RESULT_SAD;
      break;
    default:
      m_result = EMOTION_RESULT_NEUTRAL;
      //DEBUGLW("default case, svm_res=[%d]\n", svm_res);
      break;
  }
  return m_result;
}

} /* namespace FFR */
