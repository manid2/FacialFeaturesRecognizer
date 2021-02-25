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
#=============================================================================

#=============================================================================
# Setup the project's executable, headers, sources and dependencies
#=============================================================================
cmake_minimum_required(VERSION 3.0)
set (CMAKE_CXX_STANDARD 11)

project(FacialFeaturesRecognizer)
get_filename_component(MODULE_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

#-- target for exe
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc/)
file(GLOB module_srcs ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
set(SRCS main.cpp ${module_srcs})

# debug macros
#add_definitions(-DDUMMY_DATA)

#string(TOLOWER ${MODULE_NAME} MODULE_NAME)
find_package( OpenCV REQUIRED )
set(EXE_NAME exe_${MODULE_NAME})
add_executable(${EXE_NAME} ${SRCS})
target_link_libraries(${EXE_NAME}  ${OpenCV_LIBS})

#-- target for text exe
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

#-- target for doc
#--------------------------------------------------------------------
# below code taken from:
# https://vicrucann.github.io/tutorials/quick-cmake-doxygen/
#--------------------------------------------------------------------
# build docs by default
option(BUILD_DOC "Build documentation" ON)
find_package(Doxygen)
if (DOXYGEN_FOUND)
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/doc/${CMAKE_PROJECT_NAME}.doxyfile)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    # request to configure the file
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")

    # note the option ALL which allows to build the docs together with the application
    add_custom_target( doc_doxygen ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM )
else (DOXYGEN_FOUND)
  message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)

#-- add utils
add_subdirectory(util)

# Use the below cmake command to generate the cmake eclipse project
# cmake -G"Eclipse CDT4 - Unix Makefiles"\
#       -DCMAKE_ECLIPSE_GENERATE_SOURCE_PROJECT=TRUE\
#       -DCMAKE_BUILD_TYPE=Debug\
#       -DCMAKE_CXX_FLAGS="-std=c++11"\
#       -DCMAKE_CXX_COMPILER_ARG1=-std=c++11
