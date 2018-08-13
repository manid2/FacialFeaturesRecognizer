/****************************************************************************\
 * Copyright (c) 2018 Mani Kumar <maniyoung.d2@gmail.com>
 * ---------------------------------------------------------------------------
 * Project     :  FacialFeaturesRecognizer
 * Author      :  Mani Kumar
 * License     :  GNU GPL v3
 * Origin date :  08-Aug-2018
 *
 * Filename    :  genderrecognizer.h
 * Description :  Concrete class for gender recognition
 \***************************************************************************/

#ifndef FFR_INC_GENDERRECOGNIZER_H_
#define FFR_INC_GENDERRECOGNIZER_H_

#include <featuresrecognizer.h>

namespace FFR {

class GenderRecognizer : public FeaturesRecognizer {
 public:
  const FFR::String _className;
  GenderRecognizer();
  virtual ~GenderRecognizer();

 public:
  virtual FFR::String getResult(void) override;

 private:
  static bool isSVMLoaded;
};

} /* namespace FFR */

#endif /* FFR_INC_GENDERRECOGNIZER_H_ */
