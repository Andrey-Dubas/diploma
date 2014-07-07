#-------------------------------------------------
#
# Project created by QtCreator 2014-05-04T21:58:12
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = diploma_tests
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

LIBS += -L/home/andy/basecamp/googletest -lgtest



INCLUDEPATH += $${PWD}/../diploma


SOURCES += main.cpp \
    matrix_test.cpp \

HEADERS += \
    matrix_test.h

QMAKE_CXXFLAGS += -pthread --std=c++11
