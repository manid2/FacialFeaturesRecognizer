/****************************************************************************\
 * Copyright (c) 2018 Mani Kumar <maniyoung.d2@gmail.com>
 * ---------------------------------------------------------------------------
 * Project     :  FacialFeaturesRecognizer
 * Author      :  Mani Kumar
 * License     :  GNU GPL v3
 * Origin date :  08-Aug-2018
 *
 * Filename    :  featuresrecognizer.h
 * Description :  Abstract base class for facial features recognition
 \***************************************************************************/

#ifndef FFR_INC_FEATURESRECOGNIZER_H_
#define FFR_INC_FEATURESRECOGNIZER_H_

#include <ffr_precomp.h>
#include <logger.h>

#include "opencv2/ml/ml.hpp"

namespace FFR {

/**
 * Abstract base class to get the features result.
 */
class FeaturesRecognizer {
 public:
  const FFR::String _className;
  FeaturesRecognizer();
  virtual ~FeaturesRecognizer();

  // setters n getters
  void setHOGFeatures(const std::vector<float>& h) {
    m_HOGFeatures = h;
  }

 protected:
  FFR::String m_recognizerName;
  FFR::String m_result;
  std::vector<float> m_HOGFeatures;

  // TODO: refactor code to avoid load SVM model only once
  CvSVM m_SVMobj;
  CvSVMParams m_SVMParams;  // doesnt have cv namespace

 public:
  // TODO: getResult must receive HOG fv as input arg
  virtual FFR::String getResult(void)=0;
  virtual bool loadSVM(const FFR::String& filename = "");
};

extern FeaturesRecognizer* getRecognizer(FFR::Feature);

} /* namespace FFR */

#endif /* FFR_INC_FEATURESRECOGNIZER_H_ */
