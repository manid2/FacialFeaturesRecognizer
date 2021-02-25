cmake_minimum_required(VERSION 3.0)

#-- train_hog target
find_package(OpenCV REQUIRED)
add_executable(train_hog example_cpp_train_HOG.cpp example_cpp_train_HOG.h)
target_link_libraries(train_hog ${OpenCV_LIBS})
