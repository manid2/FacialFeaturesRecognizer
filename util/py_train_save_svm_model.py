"""
@introduction:
------------------------------------------------------------------------------
    Introduction
    ============

    This module is used to train and save the OpenCV SVM model.

    SVM is short for Support Vector Machine, a Machine Learning algorithm
    used to classify data but can also be used for regression. I am using it
    to classify the different states [classes in ML terms] of human face.
------------------------------------------------------------------------------

@usage:
------------------------------------------------------------------------------
    Usage
    =====

    Run the module as a command line option for python interpreter.
    -> python py_train_save_svm_model.py
------------------------------------------------------------------------------

@purpose:
------------------------------------------------------------------------------
    To train a SVM model for Machine Learning, Computer Vision applications
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
import glob
import random
import numpy as np
import py_ffr_util as ffr_util
from py_ffr_util import *

# ---------------------------------------------------------------------------
# Module info
# ---------------------------------------------------------------------------
__author__ = "Mani Kumar"
__version__ = "1.0, 12-Aug-2018"
__license__ = "GNU GPL v3"
__copyright__ = "Copyright (c) Mani Kumar - 2018"

# ---------------------------------------------------------------------------
# Functions
# ---------------------------------------------------------------------------
def get_hog(face_img):
    # TODO: YTI, hog fv generation
    return hog


def make_sets(ft):
    """
    make sets for a feature type
    @params:
       ft : str => feature type, i.e. Age, Emotion or Gender.
    @return:
       training, prediction : list of str => list of images for training
                            and prediction
    """
    print "\t\t\t<- make_sets({0}) ->".format(ft)
    training_data = []
    training_labels = []
    prediction_data = []
    prediction_labels = []
    i = 0
    for fv in ffr_util.FeatureType[ft]:
        print "\t\t\t\t{} {}".format(i, fv)
        i += 1
        # TODO: YTI, get dataset for this
    return training_data, training_labels, prediction_data, prediction_labels


# --- svm objects
svm = cv2.SVM()
svm_params = dict(kernel_type=cv2.SVM_LINEAR,
                      svm_type=cv2.SVM_C_SVC,
                      C=2.67,
                      gamma=5.383)


def train_svm(): # train_data, labels, params
    # TODO: YTI
    print "\t\t\t<- training opencv SVM ->"
    """
    # TODO: YTI, training SVM
    print "Training opencv SVM linear {0} - Started.".format(runCount)
    svm.train(npArrTrainData, npArrTrainLabels, params=svm_params)
    print "Training opencv SVM linear {0} - Completed.".format(runCount)
    """

def test_svm(): # test_data
    # TODO: YTI
    print "\t\t\t<- testing opencv SVM->"
    """
    # TODO: YTI, Testing SVM
    print "Testing opencv SVM linear {0} - Started.".format(runCount)
    results = svm.predict_all(npArrTestData).reshape((-1,))
    print "Testing opencv SVM linear {0} - Completed.".format(runCount)
    """

def check_accuracy():
    # TODO, YTI
    print "\t\t\t<- check accuracy ->"
    """
    mask = results == npArrTestLabels
    correct = np.count_nonzero(mask)
    print "\t-> type(mask) = {}".format(type(mask))
    print "\t-> type(mask[0]) = {}".format(type(mask[0]))
    print "\t-> mask.size = {}, mask.shape = {}".format(mask.size,
                                                        mask.shape)
    pred_accur = correct * 100.0 / results.size
    print "\nPrediction accuracy = %{0}.\n".format(pred_accur)
    print "--------------------------------------------------------------"
    predictionAccuracyList[runCount] = pred_accur
    # predictionAccuracyList.append(pred_accur)
    """


def main():
    """
    Main function - start of the program.
    """
    print "main() - Enter"
    maxRuns = 10
    runCount = 0
    predictionAccuracyList = [0] * maxRuns

    for ft in ffr_util.FeatureType:
        # ---------------------- Iterate through each feature type  ----------------------
        print "\t<--- Checking feature type [{0}] - Enter --->".format(ft)

        for runCount in range(0, maxRuns):
            print "\t\t<--- Run count=[{0}] --->".format(runCount)
            training_data, training_labels, prediction_data, prediction_labels = \
                make_sets(ft)
            # ---------------------- Training opencv SVM ----------------------
            train_svm() # TODO: YTI

            # Save opencv SVM trained model.
            svm_model_name = ".{0}data{1}cv2_svm_{2}_model.yml".format(dirsep,
                                                                dirsep, ft)
            # TODO: svm.save(svm_model_name)
            print "\t\t\t<- Saving OpenCV SVM model to file=[{0}] ->".format(svm_model_name)

            # ------------------- Testing opencv SVM --------------------------
            test_svm()  # TODO: YTI

            # ------------------- Check Accuracy ---------------------------------
            check_accuracy() # TODO: YTI

        # ------------------ Get the mean accuracy of the N runs --------------
        #print "Mean value of predict accuracy in {0} runs: {1:.4f}".format(
        #maxRuns, sum(predictionAccuracyList) / len(predictionAccuracyList))
    print "main() - Exit"

if __name__ == '__main__':
    main()
