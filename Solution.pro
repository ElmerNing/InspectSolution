#-------------------------------------------------
#
# Project created by QtCreator 2012-11-14T15:21:06
#
#-------------------------------------------------

QT       -= gui

TARGET = Solution
TEMPLATE = lib
CONFIG += staticlib

DESTDIR += ./lib

INCLUDEPATH += ./\
    ./include/

PRECOMPILED_HEADER += stdafx.h

SOURCES += \
    src/solution.cpp \
    src/grouplaw.cpp \
    src/beamlaw.cpp \
    src/focalaw.cpp \
    src/gconfig.cpp \
    src/probe.cpp \
    src/wedge.cpp

HEADERS += \
    include/solution.h \
    stdafx.h \
    include/grouplaw.h \
    src/focalaw.h \
    src/gconfig.h \
    src/probe.h \
    src/wedge.h \
    include/wedge.h \
    include/probe.h \
    include/gconfig.h \
    include/focalaw.h \
    include/beamlaw.h
