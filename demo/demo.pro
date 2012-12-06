#-------------------------------------------------
#
# Project created by QtCreator 2012-11-14T16:21:01
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = demo
CONFIG   += console
CONFIG   -= app_bundle

#LIBS need to be configure again
LIBS += -lD:\Proj\Solution\InspectSolution\lib\Solution

INCLUDEPATH += ./\
    ../include

PRECOMPILED_HEADER += stdafx.h

TEMPLATE = app


SOURCES += main.cpp

HEADERS += \
    stdafx.h
