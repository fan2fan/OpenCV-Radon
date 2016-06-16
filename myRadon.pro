QT += core
QT -= gui

TARGET = myRadon
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

INCLUDEPATH +=D:\opencv\OpenCV\opencv_use\include_use\
                              D:\opencv\OpenCV\opencv_use\include_use\opencv\
                               D:\opencv\OpenCV\opencv_use\include_use\opencv2\
                                D:\opencv\OpenCV\opencv_use\include_use\myHeader\

LIBS +=D:\opencv\OpenCV\opencv_use\lib\libopencv_core300.dll.a\
D:\opencv\OpenCV\opencv_use\lib\libopencv_highgui300.dll.a\
D:\opencv\OpenCV\opencv_use\lib\libopencv_imgcodecs300.dll.a\
D:\opencv\OpenCV\opencv_use\lib\libopencv_imgproc300.dll.a\
