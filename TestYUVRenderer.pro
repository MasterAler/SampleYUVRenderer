#-------------------------------------------------
#
# Project created by QtCreator 2018-08-03T11:51:33
#
#-------------------------------------------------

QT       += core gui widgets opengl

TARGET = TestYUVRenderer
TEMPLATE = app

CONFIG += c++11


SOURCES += main.cpp\
        TestWidget.cpp \
    OpenGLDisplay.cpp

HEADERS  += TestWidget.h \
    OpenGLDisplay.h

FORMS    += TestWidget.ui

DESTDIR = $$PWD/bin
