/****************************************************************************\
 * Copyright (c) 2018 Mani Kumar <maniyoung.d2@gmail.com>
 * ---------------------------------------------------------------------------
 * Project     :  FacialFeaturesRecognizer
 * Author      :  Mani Kumar
 * License     :  GNU GPL v3
 * Origin date :  08-Aug-2018
 *
 * Filename    :  emotionrecognizer.h
 * Description :  Concrete class for emotion recognition
 \***************************************************************************/

#ifndef FFR_INC_EMOTIONRECOGNIZER_H_
#define FFR_INC_EMOTIONRECOGNIZER_H_

#include <featuresrecognizer.h>

namespace FFR {

class EmotionRecognizer : public FeaturesRecognizer {
 public:
  const FFR::String _className;
  EmotionRecognizer();
  virtual ~EmotionRecognizer();

 public:
  virtual FFR::String getResult(/*const*/std::vector<float>& hog_fv) override;
};

} /* namespace FFR */

#endif /* FFR_INC_EMOTIONRECOGNIZER_H_ */
