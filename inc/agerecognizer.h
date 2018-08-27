/****************************************************************************\
 * Copyright (c) 2018 Mani Kumar <maniyoung.d2@gmail.com>
 * ---------------------------------------------------------------------------
 * Project     :  FacialFeaturesRecognizer
 * Author      :  Mani Kumar
 * License     :  GNU GPL v3
 * Origin date :  08-Aug-2018
 *
 * Filename    :  agerecognizer.h
 * Description :  Concrete class for age recognition
 \***************************************************************************/

#ifndef FFR_INC_AGERECOGNIZER_H_
#define FFR_INC_AGERECOGNIZER_H_

#include <featuresrecognizer.h>

namespace FFR {

/**
 * Recognizes Age in the face
 */
class AgeRecognizer : public FeaturesRecognizer {
 public:
  const FFR::String _className;
  AgeRecognizer();
  virtual ~AgeRecognizer();

 public:
  virtual FFR::String getResult(/*const*/std::vector<float>& hog_fv) override;
};

} /* namespace FFR */

#endif /* FFR_INC_AGERECOGNIZER_H_ */
