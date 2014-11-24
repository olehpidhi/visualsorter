#-------------------------------------------------
#
# Project created by QtCreator 2014-11-15T12:17:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TRLWO-1428
TEMPLATE = app
CONFIG += c++11

SOURCES += main.cc\
        mainwindow.cc \
    datamodel.cc \
    sortdrawdelegate.cc

HEADERS  += mainwindow.h \
    sortingalgorithms.h \
    datamodel.h \
    sortdrawdelegate.h

FORMS    += mainwindow.ui
