/****************************************************************************\
 * Copyright (c) 2018 Mani Kumar <maniyoung.d2@gmail.com>
 * ---------------------------------------------------------------------------
 * Project     :  FacialFeaturesRecognizer
 * Author      :  Mani Kumar
 * License     :  GNU GPL v3
 * Origin date :  08-Aug-2018
 *
 * Filename    :  test_precomp.h
 * Description :  Pre-compiled header for test code.
 \***************************************************************************/

#ifndef FFR_TEST_PRECOMP_H_
#define FFR_TEST_PRECOMP_H_

// C headers

// C++ headers
#include <fstream>

// OpenCV testing system headers
#include "opencv2/ts/ts.hpp"
#include "opencv2/highgui/highgui.hpp"

// utility headers
#include <logger.h>

#ifndef cv_format
#define cv_format(fmt, ...) \
    cv::format(fmt, ##__VA_ARGS__)
#endif

// Constants
static const FFR::String ENABLE_DEBUG_MODE("ENABLE_DEBUG_MODE");
static const std::string DIR_SEP("/");  // TODO: make it OS independent
static const std::string INPUT_PARAMS_FILE("input_params.yml");
static const std::string INPUT_FOLDER("data_in");
static const std::string OUTPUT_FOLDER("data_out");
static const std::string TMP_FOLDER("tmp");

static const std::string IMAGE_I("IMAGE_I");

#endif // FFR_TEST_PRECOMP_H_
