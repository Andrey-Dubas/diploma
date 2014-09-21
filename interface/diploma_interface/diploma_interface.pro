#-------------------------------------------------
#
# Project created by QtCreator 2014-08-25T20:14:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = diploma_interface
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ../../FlightReviewPanel/flightpanel.cpp \
    ../../FlightReviewPanel/cflightvisualiser.cpp \
    ccontrolledtarget.cpp \
    ../../FlightReviewPanel/GeometryStructures.cpp \
    cmissle.cpp

HEADERS  += mainwindow.h \
    ../../FlightReviewPanel/flightpanel.h \
    ../../FlightReviewPanel/cflightvisualiser.h \
    ccontrolledtarget.h \
    ../../FlightReviewPanel/GeometryStructures.h \
    cmissle.h \
    isignalapplier.h

FORMS    += mainwindow.ui

QMAKE_CXXFLAGS = -std=c++11

#INCLUDEPATH += ../../FlightReviewPanel/
#INCLUDEPATH += ../../diploma/
