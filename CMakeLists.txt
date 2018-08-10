#=============================================================================
# Copyright (c) 2018 Mani Kumar <maniyoung.d2@gmail.com>
#-----------------------------------------------------------------------------
# Project     :  FacialFeaturesRecognizer
# Author      :  Mani Kumar
# License     :  GNU GPL v3
# Origin date :  08-Aug-2018
#
# Description :
#--------------
# This project is used to recognize features in face
# such as Age, Gender and Emotions.
# Based on OpenCV tutorial by Philipp Wagner <bytefish[at]gmx[dot]de>
#=============================================================================

#=============================================================================
# Setup the project's executable, headers, sources and dependencies
#=============================================================================
cmake_minimum_required(VERSION 2.8)
set (CMAKE_CXX_STANDARD 11)

project(FacialFeaturesRecognizer)
get_filename_component(MODULE_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc/)
file(GLOB module_srcs ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
set(SRCS main.cpp ${module_srcs})

# debug macros
#add_definitions(-DDUMMY_DATA)

string(TOLOWER ${MODULE_NAME} MODULE_NAME)
find_package( OpenCV REQUIRED )
add_executable(${MODULE_NAME} ${SRCS})
target_link_libraries(${MODULE_NAME}  ${OpenCV_LIBS})

# includes gtest or opencv ts module for testing
enable_testing()
file(GLOB module_test_srcs ${CMAKE_CURRENT_SOURCE_DIR}/test/*.cpp)
set(TEST_EXE "test_${MODULE_NAME}")

#find_package(GTest REQUIRED)
#include_directories(${GTEST_INCLUDE_DIRS})
find_package( OpenCV REQUIRED )
add_executable(${TEST_EXE} ${module_test_srcs} ${module_srcs})
#target_link_libraries(${TEST_EXE} gmock_main gtest_main)
target_link_libraries(${TEST_EXE} ${OpenCV_LIBS})
add_test(NAME ${TEST_EXE} COMMAND ${MODULE_NAME})

# Use the below cmake command to generate the cmake eclipse project
# cmake -G"Eclipse CDT4 - Unix Makefiles"\
#       -DCMAKE_ECLIPSE_GENERATE_SOURCE_PROJECT=TRUE\
#       -DCMAKE_BUILD_TYPE=Debug\
#       -DCMAKE_CXX_FLAGS="-std=c++11"\
#       -DCMAKE_CXX_COMPILER_ARG1=-std=c++11
