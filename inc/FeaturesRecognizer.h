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

#include "opencv2/ml.hpp"

namespace FFR {

/**
 * Abstract base class to get the recognition results.
 *
 * To add a new feature to recognize on the face create a new class as a
 * derived class of this abstract class and override getResult() pure virtual
 * method to get the recognition.
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

  //cv::Ptr<cv::ml::SVM> m_pSVM;
  /* Using the base class for all ML algorithms in OpenCV 4.0.
     REASON: 
     * A bug was observed in svm.load() when using the specific class
     SVM is used.
     * The specific class save-load tests are not present in 
     `opencv_test_ml` code.
    */
  cv::Ptr<cv::ml::StatModel> m_pSVM;

 public:
  /**
   * The derived concrete classes implementing the specific feature
   * recognition must override this method to give recognition results
   * to the base recognizer which interacts with the UI.
   */
  virtual FFR::String getResult(const cv::Mat& ml_pred_data)=0;
  // loads SVM model
  bool loadSVM(const FFR::String& filename = "");
};

//! Gives the feature recognizer object, simpler than using factory pattern.
extern FeaturesRecognizer* getRecognizer(FFR::Feature);

} /* namespace FFR */

#endif /* FFR_INC_FEATURESRECOGNIZER_H_ */
