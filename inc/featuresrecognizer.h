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

namespace FFR {

/**
 * Abstract base class to get the features result.
 */
class FeaturesRecognizer {
 public:
  const FFR::String _className;
  FeaturesRecognizer();
  virtual ~FeaturesRecognizer();

 protected:
  FFR::String m_result;

 public:
  // TODO: getResult must receive HOG fv as input arg
  virtual FFR::String getResult(void)=0;
};

extern FeaturesRecognizer* getRecognizer(FFR::Feature);

} /* namespace FFR */

#endif /* FFR_INC_FEATURESRECOGNIZER_H_ */
