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
  m_SVMParams.kernel_type = CvSVM::LINEAR;
  m_SVMParams.svm_type = CvSVM::C_SVC;
  m_SVMParams.C = 2.67;
  m_SVMParams.gamma = 5.383;

  // setting default values
  m_recognizerName = "[None]";
}

FeaturesRecognizer::~FeaturesRecognizer() {
  DEBUGLD("destructor called!\n");
}

bool FeaturesRecognizer::loadSVM(const FFR::String& /*fn*/) {
  bool success = true;

  do {  // for common error handling

    cv::String fn("");  //= cwd;
    fn += cv::format("cv2_svm_%s_model.yml", m_recognizerName.c_str());
    // below code taken from letter_recog.cpp opencv 2.4 sample
    // and `sv_count` condition from OpenCV Q&A forum
    m_SVMobj.load(fn.c_str());
    int sv_count = m_SVMobj.get_support_vector_count();
    int var_count = m_SVMobj.get_var_count();
    if (!var_count || !sv_count) {
      DEBUGLE(
          "Could not read the classifier [%s], " "var_count=[%d], sv_count=[%d]\n",
          fn.c_str(), var_count, sv_count);
      success = false;
      break;
    }
    DEBUGLD("The classifier [%s] is loaded, var_count=[%d], sv_count=[%d]\n",
            fn.c_str(), var_count, sv_count);
  } while (0);
  return success;
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
