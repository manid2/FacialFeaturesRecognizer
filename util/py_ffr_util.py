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
    -> python py_ffr_util.py
------------------------------------------------------------------------------

@purpose:
------------------------------------------------------------------------------
    To perform pre-processing tasks and automate repetitive tasks. 
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
import numpy as np

# ---------------------------------------------------------------------------
# Module constants
# ---------------------------------------------------------------------------
dirsep = os.sep  # directory path separator
curdir = os.curdir  # Relative current directory i.e. '.'
cwdpath = os.getcwd()  # current working directory full path name

# Age
AgeList = ["adult", "child", "old", "teen"]
AgeListNo = ["adult [20-40]", "child [5-10]", "old [40+]", "teen [10-20]"]
# Emotions
EmotionList = ["anger", "contempt", "happy", "neutral", "sad", "surprise"]
# Gender
GenderList = ["male", "female"]

FeatureType = {"Age" : AgeList, "Emotion" : EmotionList, "Gender": GenderList}


# ---------------------------------------------------------------------------
# Functions
# ---------------------------------------------------------------------------
def get_images(folderName):
    image_list = glob.glob(folderName)
    image_list.sort()
    images = [cv2.imread(img, cv2.CV_LOAD_IMAGE_GRAYSCALE) for img in image_list]    
    return images


def detect_faces(img_list):    
    face_cascade = cv2.CascadeClassifier('haarcascade_frontalface_default.xml')
    face_locations = []
    for img in img_list:
        face_locations.append(face_cascade.detectMultiScale(img, 1.1, 3))
    return face_locations


def get_preprocessed_faces(inputFolderName):    
    images = get_images(inputFolderName)
    face_locations = detect_faces(images)
    preprocessed_faces = []    
    for i in range(len(images)):
        img = images[i]
        temp = face_locations[i]
        [y, x, h, w] = temp[0]
        img_face = img[ x:x + w, y:y + h]
        img_histeq = cv2.equalizeHist(img_face)
        img_resize = cv2.resize(img_histeq, (50, 50))
        preprocessed_faces.append(img_resize)
    return preprocessed_faces


def get_dataset(ft, fv):
    """
    Gets the dataset for training and prediction for the feature type and
    the feature value.The dataset is randomly shuffled and split into 80/20.
    -> 80% for training data
    -> 20% for testing data

    @params:
       ft : str => feature type, i.e. Age, Emotion or Gender.
       fv : str => feature value, i.e. anger, sad, child, teen etc.
    @return:
       training, prediction : list of str => list of images for training
                            and prediction
    """
    print "\n get_datasets({0}, {1}) - Enter".format(ft, fv)
    folderName = ".{0}FFR_dataset{1}{2}{3}{4}{5}*".format(dirsep,
                                                               dirsep,
                                                               ft,
                                                               dirsep,
                                                               fv,
                                                               dirsep)
    p_faces = get_preprocessed_faces(folderName)
    random.shuffle(p_faces)
    training = p_faces[:int(len(p_faces) * 0.8)]  # get first 80% of file list
    prediction = p_faces[-int(len(p_faces) * 0.2):]  # get last 20% of file list
    print "\n get_datasets({0}, {1}) - Enter".format(ft, fv)
    return training, prediction
