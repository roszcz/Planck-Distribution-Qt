#-------------------------------------------------
#
# Project created by QtCreator 2014-09-10T21:11:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = PlanckDist
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp\
        mainwindow.cpp \
        qcustomplot.cpp \
        generator.cpp

HEADERS  += mainwindow.h \
        qcustomplot.h \
        generator.h

FORMS    += mainwindow.ui

CONFIG += mobility
MOBILITY = 

