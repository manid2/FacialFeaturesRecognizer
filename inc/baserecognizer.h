/****************************************************************************\
 * Copyright (c) 2018 Mani Kumar <maniyoung.d2@gmail.com>
 * ---------------------------------------------------------------------------
 * Project     :  FacialFeaturesRecognizer
 * Author      :  Mani Kumar
 * License     :  GNU GPL v3
 * Origin date :  08-Aug-2018
 *
 * Filename    :  baserecognizer.h
 * Description :  Base class for facial features recognizer.
 \***************************************************************************/

#ifndef FFR_INC_BASERECOGNIZER_H_
#define FFR_INC_BASERECOGNIZER_H_

#include <ffr_precomp.h>
#include <logger.h>

#include <featuresrecognizer.h>

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <set>
#include <utility>

namespace FFR {

typedef std::set<FFR::Feature> FeaturesSet;
//typedef std::set<FFR::String> ResultsSet;

//! to avoid feature-result mismatch issue, we use a pair
typedef std::pair<FFR::Feature, FFR::String> ResultPair;
//! set of feature-result per face
typedef std::set<ResultPair> ResultsPairSet;
//! results per image, equals no of faces in the image
typedef std::vector<ResultsPairSet> ResultsVec;

/**
 * Class to interact with the FeaturesRecognizer and with the UI.
 * It handles the pre-processing of the input image for feature vector
 * generation and displaying the result on the UI
 */
class BaseRecognizer {
 public:
  const FFR::String _className;
  BaseRecognizer(void);
  virtual ~BaseRecognizer();

  // simple test for logger
  void printLog(void);

  // setters and getters
 public:
  void setFeaturesToRecognize(FeaturesSet f) {
    m_features = f;
  }
  ResultsVec getRecognitionResults(void) const {
    return m_resultsVec;
  }

 public:
  //! processes video from file
  ErrorCode readVideoFromFile(const std::string& vidFileName = "test.m4v");
  //! processes video from cam with id
  ErrorCode readVideoFromCam(const int id = 0);

  // for unit testing and future use
  ErrorCode readImageFromFile(const FFR::String& fileName, cv::Mat& img_o);
  ErrorCode init(void);
  ErrorCode loadClassifier(const FFR::String& fileName);
  ErrorCode initRecognizers(void);

 private:
  FeaturesSet m_features;
  int m_fontFace;
  double m_fontScale;
  cv::Scalar m_fontColor;
  int m_lineType;

  std::vector<FFR::FeaturesRecognizer*> m_ffrVec;
  ResultsVec m_resultsVec;

  // object detectors and ml objects
  // using HOG default values as it is used in the training SVM models
  cv::HOGDescriptor m_HOGDescriptor;

 private:
  cv::CascadeClassifier m_faceCascade;
  ErrorCode readImage(cv::Mat& img);
  ErrorCode readVideo(cv::VideoCapture& cap);
  ErrorCode detectFace(cv::Mat& frame, std::vector<cv::Rect>& faces,
                       cv::Mat& frame_gray);
  ErrorCode recognizeFeatures(const FeaturesSet& features, ResultsVec& results,
                              cv::Mat& frame_gray,
                              std::vector<cv::Rect>& faces);
  ErrorCode drawResults(cv::Mat& frame, const std::vector<cv::Rect>& faces,
                        const FeaturesSet& features, const ResultsVec& results);
  ErrorCode computeHOG(const cv::Mat& img, std::vector<float>& hog_features);
};

extern int execute(int argc, char **argv);

} /* namespace FFR */

#endif /* FFR_INC_BASERECOGNIZER_H_ */
