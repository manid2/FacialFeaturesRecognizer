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
#include "opencv2/core/core_c.h"

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
  FFR::Feature getFeatureType(void) const {
    return m_featureType;
  }
  FFR::String getFeatureName(void) const {
    return m_featureName;
  }

 protected:
  FFR::Feature m_featureType;
  FFR::String m_featureName;
  FFR::String m_result;

  CvSVM m_SVMobj;
  CvSVMParams m_SVMParams;  // doesnt have cv namespace

 public:
  virtual FFR::String getResult(/*const*/std::vector<float>& hog_fv)=0;
  virtual bool loadSVM(const FFR::String& filename = "");
};

extern FeaturesRecognizer* getRecognizer(FFR::Feature);

} /* namespace FFR */

#endif /* FFR_INC_FEATURESRECOGNIZER_H_ */
