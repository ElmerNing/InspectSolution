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

QMAKE_CXXFLAGS += -std=c++0x

SOURCES += \
    src/wedge.cpp \
    src/stripchartdata.cpp \
    src/solution_sc.cpp \
    src/serialize.cpp \
    src/probe.cpp \
    src/material.cpp \
    src/inspectdata.cpp \
    src/grouplaw_sc.cpp \
    src/grouplaw.cpp \
    src/groupdata.cpp \
    src/gconfig.cpp \
    src/datadevice.cpp \
    src/blockdata.cpp \
    src/beamlaw_sc.cpp \
    src/beamlaw.cpp \
    src/beamdata.cpp

HEADERS += \
    stdafx.h \
    include/wedge.h \
    include/stripchartdata.h \
    include/solution_sc.h \
    include/serialize.h \
    include/qrange.h \
    include/probe.h \
    include/material.h \
    include/inspectdata.h \
    include/grouplaw_sc.h \
    include/grouplaw.h \
    include/groupdata.h \
    include/globaltype.h \
    include/gconfig.h \
    include/datadevice.h \
    include/blockdata.h \
    include/beamlaw_sc.h \
    include/beamlaw.h \
    include/beamdata.h
