#-------------------------------------------------
#
# Project created by QtCreator 2017-03-23T20:15:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ipmapper
TEMPLATE = app


SOURCES += main.cpp\
        maindialog.cpp \
    custom_widget/custom_scene.cpp \
    thread/cam_thread.cpp \
    thread/view_thread.cpp \
    imgproc/CCAMCalib.cpp \
    imgproc/utils.cpp

HEADERS  += maindialog.h \
    custom_widget/custom_scene.h \
    thread/cam_thread.h \
    thread/view_thread.h \
    imgproc/CCAMCalib.h \
    imgproc/utils.hpp

FORMS    += maindialog.ui

INCLUDEPATH += /usr/local/include

LIBS += -L/usr/local/lib \
    -lopencv_core \
    -lopencv_highgui \
    -lopencv_imgproc \
    -lopencv_imgcodecs \
    -lopencv_video \
    -lopencv_videoio \
    -lopencv_calib3d

