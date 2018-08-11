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
def get_images(feature_t, feature_v):
    """
    Get all files list, randomly shuffle it and split into 80/20.
    -> 80% for training data
    -> 20% for testing data

    @params:
       feature_t : str => feature type, i.e. Age, Emotion or Gender.
       feature_v : str => feature value, i.e. anger, sad, child, teen etc.
    @return:
       training, prediction : list of str => list of the file names
                              i.e. images for the feature.
    """
    print "\n get_files({0}) - Enter".format(emotion)
    files = glob.glob("..{0}dataset{1}{2}{3}*".format(dirsep, dirsep,
                                                      emotion, dirsep))
    random.shuffle(files)
    training = files[:int(len(files) * 0.8)]  # get first 80% of file list
    prediction = files[-int(len(files) * 0.2):]  # get last 20% of file list
    print "\n get_files({0}) - Exit".format(emotion)
    return training, prediction

def detect_faces(img_list):    
    face_cascade = cv2.CascadeClassifier('../data/haarcascade_frontalface_default.xml')
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

def get_hog(face_img):
    # TODO: YTI, hog fv generation
    return hog

def make_sets():
    print "\n make_sets() - Enter"
    training_data = []
    training_labels = []
    prediction_data = []
    prediction_labels = []    

    for emotion in emotionsList:
        training, prediction = get_files(emotion)
        for item in training:
            image = cv2.imread(item)  # read image
            gray = cv2.cvtColor(# convert to grayscale
                        image, cv2.COLOR_BGR2GRAY)
            clahe_image = claheObject.apply(gray)
            landmarkVectorList = get_landmarks(clahe_image)
            if landmarkVectorList == "No face detected!":
                pass
            else:
                training_data.append(landmarkVectorList)
                training_labels.append(emotionsList.index(emotion))
        for item in prediction:
            image = cv2.imread(item)
            gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
            clahe_image = claheObject.apply(gray)
            landmarkVectorList = get_landmarks(clahe_image)
            if landmarkVectorList == "No face detected!":
                pass
            else:
                prediction_data.append(landmarkVectorList)
                prediction_labels.append(emotionsList.index(emotion))

    print "\n make_sets() - Exit"
    return training_data, training_labels, prediction_data, prediction_labels


def main():
    """
    Main function - start of the program.
    """
    print "\n main() - Enter"
    svm = cv2.SVM()
    svm_params = dict(kernel_type=cv2.SVM_LINEAR,
                      svm_type=cv2.SVM_C_SVC,
                      C=2.67,
                      gamma=5.383)
    maxRuns = 1
    runCount = 0
    predictionAccuracyList = [0] * maxRuns

    for runCount in range(0, maxRuns):
        print "\n\t\t<--- Making sets {0} --->".format(runCount)
        training_data, training_labels, prediction_data, prediction_labels = \
            make_sets()
        # ---------------------- Training opencv SVM ----------------------
        print "\n################## Training opencv SVM ##################\n"
        # Training data must be float32 matrix for the opencv svm.
        npArrTrainData = np.float32(training_data)
        npArrTrainLabels = np.float32(training_labels)
        print "npArrTrainData.shape = {0}.".format(npArrTrainData.shape)
        print "npArrTrainLabels.shape = {0}.".format(npArrTrainLabels.shape)
        print "Training opencv SVM linear {0} - Started.".format(runCount)
        svm.train(npArrTrainData, npArrTrainLabels, params=svm_params)
        print "Training opencv SVM linear {0} - Completed.".format(runCount)

        # Save opencv SVM trained model.
        svm.save("..{0}input{1}cv2_svm_6_states.yml".format(dirsep,
                                                            dirsep))
        print "\nSaving opencv SVM model to file - Completed."

        # ------------------- Testing opencv SVM --------------------------
        print "\n################## Testing opencv SVM ###################\n"
        # Testing data must be float32 matrix for the opencv svm.
        npArrTestData = np.float32(prediction_data)
        npArrTestLabels = np.float32(prediction_labels)
        print "npArrTestData.shape = {0}.".format(npArrTestData.shape)
        print "npArrTestLabels.shape = {0}.".format(npArrTestLabels.shape)
        print "Testing opencv SVM linear {0} - Started.".format(runCount)
        results = svm.predict_all(npArrTestData).reshape((-1,))
        print "Testing opencv SVM linear {0} - Completed.".format(runCount)
        print "\n\t-> type(npArrTestLabels) = {}".format(
                                                  type(npArrTestLabels))
        print "\t-> type(npArrTestLabels[0]) = {}".format(
                                                  type(npArrTestLabels[0]))
        print "\t-> npArrTestLabels.size = {}".format(npArrTestLabels.size)
        print "\n\t-> type(results) = {}".format(type(results))
        print "\t-> type(results[0]) = {}".format(type(results[0]))
        print "\t-> results.size = {}, results.shape = {}".format(
                                                results.size, results.shape)
        # ------------------- Check Accuracy ---------------------------------
        print "\n################## Check Accuracy #######################\n"
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
    # Get the mean accuracy of the i runs
    print "Mean value of predict accuracy in {0} runs: {1:.4f}".format(
        maxRuns, sum(predictionAccuracyList) / len(predictionAccuracyList))
    print "\n main() - Exit"


if __name__ == '__main__':
    main()
