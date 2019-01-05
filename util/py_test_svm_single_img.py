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
import glob
import random
import numpy as np
from numpy.linalg import norm
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
def get_hog_features(img):
    # FIXME, not working
    #h_features = hog.compute(img)
    # below code taken from opencv sample digits.py, it looks like HOG implementation
    gx = cv2.Sobel(img, cv2.CV_32F, 1, 0)
    gy = cv2.Sobel(img, cv2.CV_32F, 0, 1)
    mag, ang = cv2.cartToPolar(gx, gy)
    bin_n = 16
    bin = np.int32(bin_n*ang/(2*np.pi))
    bin_cells = bin[:10,:10], bin[10:,:10], bin[:10,10:], bin[10:,10:]
    mag_cells = mag[:10,:10], mag[10:,:10], mag[:10,10:], mag[10:,10:]
    hists = [np.bincount(b.ravel(), m.ravel(), bin_n) for b, m in zip(bin_cells, mag_cells)]
    hist = np.hstack(hists)

    # transform to Hellinger kernel
    eps = 1e-7
    hist /= hist.sum() + eps
    hist = np.sqrt(hist)
    hist /= norm(hist) + eps
    return np.float32(hist)


# Set the classifier as a opencv svm with SVM_LINEAR kernel
maxRuns = 1
runCount = 0
svm = cv2.SVM()
hog = cv2.HOGDescriptor() # TODO: test with the built in function
feature_type = "Emotion" # TODO: make it a list to test every feature for a single image
face_cascade = cv2.CascadeClassifier('haarcascade_frontalface_default.xml')

print("-> Loading opencv SVM")
svm_model_name = ".{0}models{1}cv2_svm_{2}_model.yml".format(dirsep,
                                                             dirsep,
                                                             feature_type)
svm.load(svm_model_name) # TODO: setup  svm model filename
print("-> Loaded opencv SVM=[{}]".format(svm_model_name))


for runCount in range(0, maxRuns):
    # Get a sample for prediction
    fileName = input("Enter file name: ")
    if fileName == "quit" or fileName == "q":
        print("Quitting the application!")
        break
    else:
        print("File name is: {}".format(fileName))
    # Get landmark features from the image.
    img_gray = cv2.imread(fileName, cv2.CV_LOAD_IMAGE_GRAYSCALE)
    img_histeq = cv2.equalizeHist(img_gray)
    faces = face_cascade.detectMultiScale(img_histeq, 1.1, 3)
    for f in faces:
        x, y, w, h = [v for v in f]
        crop_face = img_histeq[y:y + h, x:x + w]
        c_face_resize = cv2.resize(crop_face, (50, 50))
        hog_fv = get_hog_features(c_face_resize)
        #print "hog_fv.shape: ", hog_fv.shape
        result = svm.predict(hog_fv)
        print("result={}-{}".format(result, ffr_util.FeatureType[feature_type][int(result)]))
