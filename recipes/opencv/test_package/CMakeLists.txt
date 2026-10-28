cmake_minimum_required(VERSION 3.31)
project(test_package CXX)

find_package(OpenCV REQUIRED)

add_executable(test_package test_package.cpp)
target_link_libraries(
    test_package
    OpenCV::opencv_core
    OpenCV::opencv_imgproc
    OpenCV::opencv_imgcodecs
    OpenCV::opencv_objdetect
    OpenCV::opencv_features
    OpenCV::opencv_dnn
    OpenCV::opencv_photo
    OpenCV::opencv_video
    OpenCV::opencv_geometry
    OpenCV::opencv_calib
    OpenCV::opencv_videoio
    OpenCV::opencv_highgui)
