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
from numpy.linalg import norm
import py_ffr_util as ffr_util
from py_ffr_util import *
from datashape.coretypes import float32

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
    print("\t\t\t<- make_sets({0}) ->".format(ft))
    training_data = []
    training_labels = []
    prediction_data = []
    prediction_labels = []
    i = 0
    for fv in ffr_util.FeatureType[ft]:
        print("\t\t\t\t{} {}".format(i, fv))
        tr_data = []
        tr_labels = []
        pr_data = []
        pr_labels = []
        tr_data, tr_labels, pr_data, pr_labels = ffr_util.get_dataset(ft, fv)
        # print "\t\t\t\tmani_debug: ", type(tr_data), ", tr_data", tr_data
        training_data += tr_data
        training_labels += tr_labels
        prediction_data += pr_data
        prediction_labels += pr_labels
        i += 1
    return training_data, training_labels, prediction_data, prediction_labels

# --- HOG objects
# hog = cv2.HOGDescriptor() # not used


def get_hog_features(img):
    # FIXME, not working
    # h_features = hog.compute(img)
    # below code taken from opencv sample digits.py, it looks like HOG implementation
    gx = cv2.Sobel(img, cv2.CV_32F, 1, 0)
    gy = cv2.Sobel(img, cv2.CV_32F, 0, 1)
    mag, ang = cv2.cartToPolar(gx, gy)
    bin_n = 16
    bin = np.int32(bin_n * ang / (2 * np.pi))
    bin_cells = bin[:10, :10], bin[10:, :10], bin[:10, 10:], bin[10:, 10:]
    mag_cells = mag[:10, :10], mag[10:, :10], mag[:10, 10:], mag[10:, 10:]
    hists = [np.bincount(b.ravel(), m.ravel(), bin_n) for b, m in zip(bin_cells, mag_cells)]
    hist = np.hstack(hists)

    # transform to Hellinger kernel
    eps = 1e-7
    hist /= hist.sum() + eps
    hist = np.sqrt(hist)
    hist /= norm(hist) + eps
    return np.float32(hist)


# --- svm objects
svm = cv2.ml.SVM_create()
svm.setGamma(5.383)
svm.setC(2.67)
svm.setKernel(cv2.ml.SVM_LINEAR)
svm.setType(cv2.ml.SVM_C_SVC)


def train_svm(train_data, train_labels):  # train_data, labels
    print("\t\t\t<- training opencv SVM ->")
    # FIXME
    # modules/ml/src/svm.cpp:1629: error: (-5:Bad argument) in the case of classification problem
    svm.train(train_data, cv2.ml.ROW_SAMPLE, train_labels)


def test_svm(test_data):
    print("\t\t\t<- testing opencv SVM->")
    return svm.predict(test_data)[1].ravel()


def check_accuracy(prediction_labels, result_labels):  # predication_labels, result_labels
    print("\t\t\t<- check accuracy ->")
    mask = prediction_labels == result_labels
    correct = np.count_nonzero(mask)
    accuracy = correct * 100.0 / result_labels.size
    print("\t\t\t\t-> Prediction accuracy = %{0}.\n".format(accuracy))
    return accuracy


def main():
    """
    Main function - start of the program.
    """
    print("main() - Enter")

    for ft in ffr_util.FeatureType:
        # ---------------------- Iterate through each feature type  -----------
        print("\t<--- Checking feature type [{0}] - Enter --->".format(ft))
        maxRuns = 1
        runCount = 0
        predictionAccuracyList = []
        for runCount in range(0, maxRuns):
            print("\t\t<--- Run count=[{0}] --->".format(runCount))
            training_data, training_labels, prediction_data, prediction_labels = \
                make_sets(ft)
            # for each preproccessed face compute hog
            # print "tr_data: ", type(training_data), ", ", len(training_data)
            t_data = []
            for t_img in training_data:
                t_data.append(get_hog_features(t_img))
                # print "t_data: {}, {}, {}".format(type(t_data), len(t_data), t_data[0])
            # convert hog features data to numpy array            
            training_data = np.float32(t_data)                     
            # ---------------------- Training opencv SVM ----------------------
            train_svm(training_data, training_labels)
            
            # Save opencv SVM trained model.
            svm_model_name = "{0}{1}models{2}cv4_py_svm_{3}_model.yml".format(os.getenv("FFR_DATASET_PATH"),
                                                                         dirsep,
                                                                         dirsep,
                                                                         ft)
            svm.save(svm_model_name)
            print("\t\t\t<- Saving OpenCV SVM model to file=[{0}] ->".format(svm_model_name))

            # ------------------- Testing opencv SVM --------------------------
            p_data = []
            for p_img in prediction_data:
                p_data.append(get_hog_features(p_img))
            # convert hog features data to numpy array
            prediction_data = np.float32(p_data)       
            result_labels = test_svm(prediction_data)

            # ------------------- Check Accuracy ------------------------------
            prediction_accuracy = check_accuracy(
                prediction_labels, result_labels)
            predictionAccuracyList.append(prediction_accuracy)

        # ------------------ Get the mean accuracy of the N runs --------------
        print("\t-> mean prediction accuracy for {0} runs: {1:.4f}".format(
            maxRuns, sum(predictionAccuracyList) / len(predictionAccuracyList)))
    print("main() - Exit")


if __name__ == '__main__':
    main()
