#####################################################################
# Copyright (c) 2018 Mani Kumar <maniyoung.d2@gmail.com>
# -------------------------------------------------------------------
# Project     :  FacialFeaturesRecognizer
# Author      :  Mani Kumar
# License     :  GNU GPL v3
# Origin date :  08-Aug-2018
#
# Description :
# -------------
# This project is used to recognize features in face
# such as Age, Gender and Emotions.
# Based on OpenCV tutorial by Philipp Wagner <bytefish[at]gmx[dot]de>
#####################################################################

#####################################################################
# Setup the project's executable, headers, sources and dependencies
#####################################################################
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

#####################################################################
# Add gtest and gmock
# for detailed instructions read the article from:
# https://crascit.com/2015/07/25/cmake-gtest/
# The below code is borrowed from there.
#####################################################################
# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" .
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest-download" )
execute_process(COMMAND "${CMAKE_COMMAND}" --build .
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest-download" )

# Prevent GoogleTest from overriding our compiler/linker options
# when building with Visual Studio
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This adds
# the following targets: gtest, gtest_main, gmock
# and gmock_main
add_subdirectory("${CMAKE_BINARY_DIR}/googletest-src"
                 "${CMAKE_BINARY_DIR}/googletest-build")

# The gtest/gmock targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if(CMAKE_VERSION VERSION_LESS 2.8.11)
    include_directories("${gtest_SOURCE_DIR}/include"
                        "${gmock_SOURCE_DIR}/include")
endif()

# Now simply link your own targets against gtest, gmock,
# etc. as appropriate

# Use the below cmake command to generate the cmake eclipse project
# cmake -G"Eclipse CDT4 - Unix Makefiles"\
#       -DCMAKE_ECLIPSE_GENERATE_SOURCE_PROJECT=TRUE\
#       -DCMAKE_BUILD_TYPE=Debug\
#       -DCMAKE_CXX_FLAGS="-std=c++11"\
#       -DCMAKE_CXX_COMPILER_ARG1=-std=c++11
