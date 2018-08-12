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
        tr_data = []
        tr_labels = []
        pr_data = []
        pr_labels = []
        tr_data, tr_labels, pr_data, pr_labels = ffr_util.get_dataset(ft, fv)
        #print "\t\t\t\tmani_debug: ", type(tr_data), ", tr_data", tr_data
        training_data += tr_data
        training_labels += tr_labels
        prediction_data += pr_data
        prediction_labels += pr_labels
        i += 1
    return training_data, training_labels, prediction_data, prediction_labels


# --- HOG objects
hog = cv2.HOGDescriptor()


def get_hog_features(img):
    h_features = hog.compute(img)
    return h_features


# --- svm objects
svm = cv2.SVM()
svm_params = dict(kernel_type=cv2.SVM_LINEAR,
                  svm_type=cv2.SVM_C_SVC,
                  C=2.67,
                  gamma=5.383)


def train_svm(train_data, train_labels):  # train_data, labels
    print "\t\t\t<- training opencv SVM ->"
    svm.train(train_data, train_labels, params=svm_params)


def test_svm(test_data):
    print "\t\t\t<- testing opencv SVM->"
    results = svm.predict_all(test_data).reshape((-1,))
    return results


def check_accuracy(predication_labels, result_labels):  # predication_labels, result_labels
    print "\t\t\t<- check accuracy ->"
    mask = predication_labels == result_labels
    correct = np.count_nonzero(mask)
    accuracy = correct * 100.0 / results.size
    print "\t\t\t\t-> Prediction accuracy = %{0}.\n".format(accuracy)
    return accuracy


def main():
    """
    Main function - start of the program.
    """
    print "main() - Enter"
    maxRuns = 1
    runCount = 0
    predictionAccuracyList = [0] * maxRuns

    for ft in ffr_util.FeatureType:
        # ---------------------- Iterate through each feature type  -----------
        print "\t<--- Checking feature type [{0}] - Enter --->".format(ft)

        for runCount in range(0, maxRuns):
            print "\t\t<--- Run count=[{0}] --->".format(runCount)
            training_data, training_labels, prediction_data, prediction_labels = \
                make_sets(ft)
            # for each preproccessed face compute hog
            training_data = [get_hog_features(p_face)
                             for p_face in training_data]
            # convert hog features data to numpy array            
            training_data = np.asarray(training_data, dtype=np.float32)
            training_labels = np.asarray(training_labels, dtype=np.float32)
            # ---------------------- Training opencv SVM ----------------------
            #train_svm(training_data, training_labels)
            print "\t\t\t<- training opencv SVM ->"
            svm.train(training_data, training_labels, params=svm_params)

            # Save opencv SVM trained model.
            svm_model_name = ".{0}models{1}cv2_svm_{2}_model.yml".format(dirsep,
                                                                         dirsep, ft)
            # TODO: svm.save(svm_model_name)
            print "\t\t\t<- Saving OpenCV SVM model to file=[{0}] ->".format(svm_model_name)

            # ------------------- Testing opencv SVM --------------------------
            prediction_data = np.float32(prediction_data)
            prediction_data = [get_hog_features(
                p_face) for p_face in prediction_data]
            result_labels = test_svm(prediction_data)

            # ------------------- Check Accuracy ------------------------------
            prediction_accuracy = check_accuracy(
                predication_labels, result_labels)
            predictionAccuracyList.append(prediction_accuracy)

        # ------------------ Get the mean accuracy of the N runs --------------
        print "\t-> mean prediction accuracy for {0} runs: {1:.4f}".format(
            maxRuns, sum(predictionAccuracyList) / len(predictionAccuracyList))
    print "main() - Exit"


if __name__ == '__main__':
    main()
