/****************************************************************************\
 * Copyright (c) 2018 Mani Kumar <maniyoung.d2@gmail.com>
 * ---------------------------------------------------------------------------
 * Project     :  FacialFeaturesRecognizer
 * Author      :  Mani Kumar
 * License     :  GNU GPL v3
 * Origin date :  08-Aug-2018
 *
 * Filename    :  featuresrecognizer.cpp
 * Description :  Abstract base class for facial features recognition
 \***************************************************************************/

#include <featuresrecognizer.h>

#include <agerecognizer.h>
#include <emotionrecognizer.h>
#include <genderrecognizer.h>

namespace FFR {

FeaturesRecognizer::FeaturesRecognizer()
    : _className(FUNC_NAME) {
  // TODO Auto-generated constructor stub

}

FeaturesRecognizer::~FeaturesRecognizer() {
  // TODO Auto-generated destructor stub
}

FeaturesRecognizer* getRecognizer(FFR::Feature f) {
#ifdef WITH_CLASS_NAME
  const FFR::String _className(FUNC_NAME);
#else
  const FFR::String _className("-");
#endif

  FeaturesRecognizer* fr = NULL;
  switch (f) {
    case FFR::Age:
      fr = new AgeRecognizer();
      break;
    case FFR::Emotion:
      fr = new EmotionRecognizer();
      break;
    case FFR::Gender:
      fr = new GenderRecognizer();
      break;
    default:
      fr = NULL;
      DEBUGLE("");
      break;
  }
  return fr;
}

} /* namespace FFR */
