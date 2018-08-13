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

#include <emotionrecognizer.h>

namespace FFR {

bool EmotionRecognizer::isSVMLoaded = false;

EmotionRecognizer::EmotionRecognizer()
    : _className(FUNC_NAME) {
  m_recognizerName = TO_STR(Emotion);
  m_result = EMOTION_RESULT_NEUTRAL;
}

EmotionRecognizer::~EmotionRecognizer() {
  DEBUGLD("destructor called!\n");
}

FFR::String EmotionRecognizer::getResult() {
  CvMat sample = cvMat(1, 64, CV_32FC1, &m_HOGFeatures[0]);
  cvCreateData(&sample);
  float svm_res = 0.0f;

  svm_res = m_SVMobj.predict(&sample);

  // TODO: need to refactor to make robust
  switch ((int) svm_res) {
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
      DEBUGLW("default case, svm_res=[%lf]\n", svm_res);
      break;
  }

  return m_result;
}

} /* namespace FFR */
