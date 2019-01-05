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
import random
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
GenderList =  ["male", "female"]

FeatureType =  { "Gender": GenderList, "Age": AgeList, "Emotion": EmotionList}  


# ---------------------------------------------------------------------------
# Functions
# ---------------------------------------------------------------------------
def get_images(folderName):
    #print "\t\t\t\t-> get_images({}) - enter".format(folderName)
    file_list = glob.glob(folderName)
    file_list = [os.path.abspath(f) for f in file_list]
    file_list.sort()
    images = []
    for file in file_list:
        #print "\t\t\t\t\t-> file=[{}]".format(file)
        img_gray = cv2.imread(file, cv2.CV_LOAD_IMAGE_GRAYSCALE)
        #print "\t\t\t\t\t-> img_gray={}".format(img_gray.shape)
        images.append(img_gray)    
    #print "\t\t\t\t\t-> file_list[49]={}".format(file_list[49])
    #print "\t\t\t\t\t-> image[49]={}".format(images[49].shape)
    return images


def get_cropped_faces(img_list):
    #print "\t\t\t\t-> get_cropped_faces(), len(img_list)=[{0}] - enter".format(len(img_list))
    face_cascade = cv2.CascadeClassifier('haarcascade_frontalface_default.xml')
    cropped_faces = []
    for img in img_list:
        faces = face_cascade.detectMultiScale(img, 1.1, 3)
        #print "\t\t\t\t\t-> faces={}, img.shape={}".format(len(faces), img.shape) 
        for f in faces:
            #print "\t\t\t\t\t-> f={}".format(f)
            x, y, w, h = [v for v in f]
            crop_face = img[y:y + h, x:x + w]
            cropped_faces.append(crop_face)
    #cv2.imwrite("mani_debug_cropped_face.jpg", cropped_faces[0])
    return cropped_faces


def get_preprocessed_faces(inFolderName):
    #print "\t\t\t\t-> get_preprocessed_faces({0}) - enter".format(inFolderName)
    cropped_faces = get_cropped_faces(get_images(inFolderName))
    preprocessed_faces = []
    for c_face in cropped_faces:
        img_histeq = cv2.equalizeHist(c_face)
        img_resize = cv2.resize(img_histeq, (50, 50))
        preprocessed_faces.append(img_resize)
    #cv2.imwrite("mani_debug_preproc_face.jpg", preprocessed_faces[0])
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
    #print "\t\t\t\t-> get_datasets({0}, {1}) - enter".format(ft, fv)
    folderName = "{0}{1}FFR_dataset{2}{3}{4}{5}{6}".format(os.getenv("FFR_DATASET_PATH"),
                                                          dirsep,
                                                          dirsep,
                                                          ft,
                                                          dirsep,
                                                          fv,
                                                          dirsep)
    p_faces = get_preprocessed_faces(folderName)
    random.shuffle(p_faces)
    # get first 80% of file list
    training_data = p_faces[:int(len(p_faces) * 0.8)]
    # get last 20% of file list
    prediction_data = p_faces[-int(len(p_faces) * 0.2):]
    training_labels = [FeatureType[ft].index(fv)] * len(training_data)
    prediction_labels = [FeatureType[ft].index(fv)] * len(prediction_data)
    # convert to int array for cv4
    training_labels = np.array(training_labels, dtype=int)
    prediction_labels = np.array(prediction_labels, dtype=int)
    
    #print "\n get_datasets({0}, {1}) - exit".format(ft, fv)
    return training_data, training_labels, prediction_data, prediction_labels
