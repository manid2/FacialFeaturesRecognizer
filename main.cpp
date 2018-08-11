/****************************************************************************\
 * Copyright (c) 2018 Mani Kumar <maniyoung.d2@gmail.com>
 * ---------------------------------------------------------------------------
 * Project     :  FacialFeaturesRecognizer
 * Author      :  Mani Kumar
 * License     :  GNU GPL v3
 * Origin date :  08-Aug-2018
 *
 * Filename    :  main.cpp
 * Description :  Entry point into the project's executable.
 \***************************************************************************/

/****************************************************************************\
 * This project is used to recognize features in face such as Age, Gender and
 * Emotions.
 \***************************************************************************/

#include <iostream>
#include <baserecognizer.h>

using namespace std;
using namespace FFR;

int main(int argc, char **argv) {
  return execute(argc, argv);
}  // end
