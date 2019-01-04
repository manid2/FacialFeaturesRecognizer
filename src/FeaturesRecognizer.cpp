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

#include <AgeRecognizer.h>
#include <EmotionRecognizer.h>
#include <FeaturesRecognizer.h>
#include <GenderRecognizer.h>

using namespace cv::ml;

namespace FFR {

FeaturesRecognizer::FeaturesRecognizer()
    : _className(FUNC_NAME) {
  m_pSVM = SVM::create();
  m_pSVM->setKernel(SVM::LINEAR);
  m_pSVM->setType(SVM::C_SVC);  // n-class classification
  m_pSVM->setC(2.67);
  m_pSVM->setGamma(5.383);

  // setting default values
  m_featureType = FFR::Feature_Undefined;
  m_featureName = "[None]";
}

FeaturesRecognizer::~FeaturesRecognizer() {
  DEBUGLD("destructor called!\n");
}

bool FeaturesRecognizer::loadSVM(const FFR::String& /*fn*/) {
  bool success = true;
  do {  // for common error handling
    cv::String fn("");  //= cwd;
    fn += cv::format("%s/models/cv4_svm_%s_model.yml",
                     getenv(FFR_DATA_PATH),
                     m_featureName.c_str());
    m_pSVM->load(fn);
    int var_count = m_pSVM->getVarCount();
    if (!var_count /*|| !sv_count*/) {
      DEBUGLE("Could not read the classifier [%s], " "var_count=[%d]\n",
              fn.c_str(), var_count/*, sv_count*/);
      success = false;
      break;
    }
    DEBUGLD("The classifier [%s] is loaded, var_count=[%d]\n",
            fn.c_str(), var_count/*, sv_count*/);
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
