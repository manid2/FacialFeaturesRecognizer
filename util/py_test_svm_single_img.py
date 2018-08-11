"""
@introduction:
------------------------------------------------------------------------------
    Introduction
    ============

    This module is used to load and test the OpenCV SVM model.

    SVM is short for Support Vector Machine, a Machine Learning algorithm
    used to classify data but can also be used for regression. I am using it
    to classify the different states [classes in ML terms] of human face.
------------------------------------------------------------------------------

@usage:
------------------------------------------------------------------------------
    Usage
    =====

    Run the module as a command line option for python interpreter.
    -> python py_test_svm_single_img.py
------------------------------------------------------------------------------

@purpose:
------------------------------------------------------------------------------
    To test the models trained by py_train_save_svm_model.py script.
------------------------------------------------------------------------------

@based_on:
------------------------------------------------------------------------------
    <a href="https://github.com/manid2/Python_OpenCV_Emotion_Detection">
       Python_OpenCV_Emotion_Detection
    </a>
------------------------------------------------------------------------------

@applications:
------------------------------------------------------------------------------
    NA
------------------------------------------------------------------------------
"""

# ---------------------------------------------------------------------------
# Imports
# ---------------------------------------------------------------------------
import os
import cv2
import numpy as np

# ---------------------------------------------------------------------------
# Module info
# ---------------------------------------------------------------------------
__author__ = "Mani Kumar"
__version__ = "1.0, 12-Aug-2018"
__license__ = "GNU GPL v3"
__copyright__ = "Copyright (c) Mani Kumar - 2018"

# ---------------------------------------------------------------------------
# Module constants
# ---------------------------------------------------------------------------
dirsep = os.sep  # directory path separator
curdir = os.curdir  # Relative current directory i.e. '.'
cwdpath = os.getcwd()  # current working directory full path name

# Age
AgeList = ["child [5-10]", "teen [11-20]", "adult [21-40]", "old [40+]"]
# Emotions
EmotionList = ["anger", "contempt", "happy", "neutral", "sad", "surprise"]
# Gender
GenderList = ["male", "female"]

# ---------------------------------------------------------------------------
# Functions
# ---------------------------------------------------------------------------
import py_ffr_util

# Set the classifier as a opencv svm with SVM_LINEAR kernel
maxRuns = 100
runCount = 0
svm = cv2.SVM()
predictionAccuracyList = [0] * maxRuns

for runCount in range(0, maxRuns):
    # Get a sample for prediction
    fileName = raw_input("Enter file name: ")
    if fileName == "quit" or fileName == "q":
        print "Quitting the application!"
        break
    else:
        print "File name is: {}".format(fileName)
    # Get landmark features from the image.
    image = cv2.imread(fileName)
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    # TODO: YTI, hog features generation here

    print "\n#################### Loading opencv SVM ####################\n"
    # Load opencv SVM trained model.
    svm.load("TODO") # TODO: setup  svm model filename
    
    print "Loading opencv SVM model from file - Completed."
    print "\n#################### Testing opencv SVM ####################\n"
    # result = svm.predict(npArrTestData)
    print "Testing opencv SVM linear {0} - Completed.".format(runCount)
    print "\n#################### Result ####################\n"
    # print "result: emotionsList[{0}] = {1}".format(result,
    #                                               emotionsList[int(result)])
    predictionAccuracyList.append(result)
    print "---------------------------------------------------------------"

# Get the mean accuracy of the i runs
print "Mean value of predict accuracy in {0} runs: {1:.4f}".format(
    maxRuns, np.mean(predictionAccuracyList))
# sum(predictionAccuracyList) / len(predictionAccuracyList)
