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
  // TODO: YTI recognition logic
  return m_result;
}

} /* namespace FFR */
