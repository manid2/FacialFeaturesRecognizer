# FacialFeaturesRecognizer

Recognizes facial features such as `Age`, `Gender` and `Emotion`, using `HOG`\
and `SVM` alogrithms. Has working sample of `OpenCV 2.4.13r7`'s HOG computation\
and SVM prediction code in C++ (which is not available in internet easily).

## TODO

+ Profile the code and measure perf. 
+ Optimize the code for perf.
+ Handle false positives from `haarcascade` face detector.
+ Improve the dataset, re-train, research or experiment with different algorithms
+ Research alternative ML libraries such as `dlib` for performance improvement.
