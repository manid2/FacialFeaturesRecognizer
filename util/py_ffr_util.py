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
import cv2
import glob
import numpy as np

def get_images(folderName):
    image_list = glob.glob(folderName)
    image_list.sort()
    images = [cv2.imread(img,0) for img in image_list]    
    return images

def detect_faces(img_list):    
    face_cascade = cv2.CascadeClassifier('haarcascade_frontalface_default.xml')
    face_locations = []
    for img in img_list:
        face_locations.append(face_cascade.detectMultiScale(img, 1.1, 3))
    return face_locations

def get_testing_faces(inputFolderName, outputFolderName):    
    images = get_images(inputFolderName)
    face_locations = detect_faces(images)
    testing_faces = []    
    for i in range(len(images)):
        img = images[i]
        temp = face_locations[i]
        [y,x,h,w] = temp[0]
        img_cropped = img[ x:x+w, y:y+h]
        img_resize = cv2.resize(img_cropped, (50,50))
        testing_faces.append(img_resize)
    return testing_faces


