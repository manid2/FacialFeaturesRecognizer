/****************************************************************************\
 * Copyright (c) 2018 Mani Kumar <maniyoung.d2@gmail.com>
 * ---------------------------------------------------------------------------
 * Project     :  FacialFeaturesRecognizer
 * Author      :  Mani Kumar
 * License     :  GNU GPL v3
 * Origin date :  08-Aug-2018
 *
 * Filename    :  test_baserecognizer.cpp
 * Description :  Test code for facial features recognizer base class
 \***************************************************************************/

#include "test_precomp.hpp"

/// Test code source headers
#include <baserecognizer.h>

/// declare using namespaces
using namespace cv;
using namespace std;
using namespace FFR;
using namespace test_FFR;

/****************************************************************************\
 * Using anonymous namespace to isolate the code in this
 * file from the code in other files i.e. to make the tests independent
 * and its results reliable.
 \***************************************************************************/
namespace {

/****************************************************************************\
 * This enumeration is unique to this test code,
 * it is intended to assign an id to the test units
 * i.e. the functions and the code flow of the class.
 * Convention: enum name is same as the function/unit under test
 \***************************************************************************/
enum eTestUnit {
  fSimpleRun = 0,
  readImage,
  readImageInLoop
};

/****************************************************************************\
 * Test wrapper class declarations
 * TODO: YTI, Convert this wrapper class to Google Test Fixture.
 \***************************************************************************/
class test_BaseRecognizer : public cvtest::BaseTest {
 public:
  /// Test units declarations
  bool test_readImage(void);
  bool test_readImageInLoop(void);

 public:
  const std::string _className;
  // ctor
  test_BaseRecognizer(void);
  // dtor
  virtual ~test_BaseRecognizer();
  // simple run - to test the simple execution of the test
  void test_fSimpleRun(void);
  // run - entry point into the test
  void run(int test_id = 0);

 private:
  bool m_DebugMode;
  std::stringstream m_ss;
  std::string m_paramFilePath;
  cv::FileStorage m_fsParams;

  /// Class Under Test - CUT
  cv::Ptr<FFR::BaseRecognizer> m_pBaseRecognizer;

  /// Helper methods for the test
  int read_params(const std::string& /*fileName*/);
  //bool validate_test_results(void) const;
};

/****************************************************************************\
 * Test wrapper class definitions
 * TODO: YTI, Convert this wrapper class to Google Test Fixture.
 \***************************************************************************/
test_BaseRecognizer::test_BaseRecognizer(void)
    : _className(FUNC_NAME),
      m_DebugMode(false),
      m_paramFilePath(ts->get_data_path() + INPUT_PARAMS_FILE) {
  DEBUGLW(", m_paramFilePath = %s\n", m_paramFilePath.c_str());
}

test_BaseRecognizer::~test_BaseRecognizer() {
  // do nothing
}

void test_BaseRecognizer::test_fSimpleRun(void) {
  ts->printf(cvtest::TS::LOG,
             "test_BaseRecognizer::simple_run(), !!!HelloWorld!!!\n");
  DEBUGLW("!!!HelloWorld!!!\n");
}

int test_BaseRecognizer::read_params(const std::string& /*fileName*/) {
  DEBUGLD("enter\n");
  stringstream ss;
  m_fsParams.open(m_paramFilePath, cv::FileStorage::READ);
  if (false == m_fsParams.isOpened()) {
    ss << "File: [" << m_paramFilePath << "], failed to open!"
       << "program exits!" << endl;
    ts->printf(cvtest::TS::LOG, "test_BaseRecognizer::read_params(), ERR: %s\n",
               ss.str().c_str());
    return -1;
  }

  /// Read params here
  m_DebugMode =
      ((string) m_fsParams[ENABLE_DEBUG_MODE] == "true" ? true : false);
  DEBUGLD("exit\n");
  return 0;
}

void test_BaseRecognizer::run(int test_id) {
  ts->printf(cvtest::TS::LOG, "test_BaseRecognizer::run() - start\n");

  bool bSuccess = true;
  do  // for common error handling
  {
    /// initialization code
    m_pBaseRecognizer = new FFR::BaseRecognizer();
    m_pBaseRecognizer->init();

    if (0 == read_params("")) {
      ts->printf(cvtest::TS::LOG,
                 "test_BaseRecognizer run() - read_params() successful!\n");
#ifndef TEST_ID_CASE
#define TEST_ID_CASE(id)\
  case id:\
      bSuccess = test_##id();\
        break;
#endif
      /// Select test unit code here
      switch (test_id) {
        TEST_ID_CASE(readImage)
        TEST_ID_CASE(readImageInLoop)
        case fSimpleRun:
        default:
          test_fSimpleRun();
          break;
      }
#undef TEST_ID_CASE
    } else {
      m_ss << " - read_params() failed!";
      bSuccess = false;
      break;
    }
  } while (0);

  if (!bSuccess) {
    FAIL()<< cv_format(" run(), ERR: %s\n", m_ss.str().c_str());
    return;
  }
  ts->printf(cvtest::TS::LOG, "test_BaseRecognizer::run() - stop\n");
}

/***************************************************************************\
 * Test Units functions definitions
 \***************************************************************************/
// Test unit 0, testing this class itself via a simple run
TEST(test_BaseRecognizer, simple_run) {
  test_BaseRecognizer test;
  test.safe_run();
}

// Test unit 1, checking the single image recognition
bool test_BaseRecognizer::test_readImage(void) {
  DEBUGLD(", enter\n");
  bool bSuccess = true;
  stringstream ss;

  do  // for common error handling
  {
    ErrorCode err = FFR::OK;  // 0 - Success, non-zero - Error

    std::string img_fileName;
    m_fsParams[IMAGE_I] >> img_fileName;
    DEBUGLD("reading image from [%s]\n", img_fileName.c_str());

    cv::Mat img;  // = cv::imread("lena.jpg");
    m_pBaseRecognizer->readImageFromFile(img_fileName, img);
    std::string out_fileName("lena_processed.jpg");
    cv::imwrite(out_fileName, img);
    DEBUGLD("writing out image file [%s]\n", out_fileName.c_str());

    if (FFR::OK != err) {
      bSuccess = false;
      m_ss.str("");
      m_ss << " not successful!";
      DEBUGLE(", %s\n", m_ss.str().c_str());
      break;
    }
  } while (0);

  DEBUGLD(", exit\n");
  return bSuccess;
}

TEST(test_BaseRecognizer, readImage) {
  test_BaseRecognizer test;
  test.safe_run(static_cast<int>(readImage));
}

// Test unit 2, checking the single image recognition in loop,
// simulating the testing recognition in video case
bool test_BaseRecognizer::test_readImageInLoop(void) {
  DEBUGLD("enter\n");
  bool bSuccess = true;
  stringstream ss;

  do  // for common error handling
  {
    ErrorCode err = FFR::OK;  // 0 - Success, non-zero - Error

    std::string imgs_folderName(ts->get_data_path() + INPUT_FOLDER + DIR_SEP);
    std::vector<string> allFiles(getAllFilesFromFolder(imgs_folderName));

    for (auto file : allFiles) {
      std::string in_fileName = imgs_folderName + file;
      DEBUGLD("reading image from [%s]\n", in_fileName.c_str());

      cv::Mat img;  // = cv::imread("lena.jpg");
      m_pBaseRecognizer->readImageFromFile(in_fileName, img);

      std::string out_fileName = ts->get_data_path() + OUTPUT_FOLDER + DIR_SEP;
      out_fileName += file;
      cv::imwrite(out_fileName, img);
      DEBUGLD("writing out image file [%s]\n", out_fileName.c_str());
    }

    if (FFR::OK != err) {
      bSuccess = false;
      m_ss.str("");
      m_ss << " not successful!";
      DEBUGLE(", %s\n", m_ss.str().c_str());
      break;
    }
  } while (0);

  DEBUGLD("exit\n");
  return bSuccess;
}

TEST(test_BaseRecognizer, readImageInLoop) {
  test_BaseRecognizer test;
  test.safe_run(static_cast<int>(readImageInLoop));
}

}  // namespace
