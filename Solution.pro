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
    src/wedge.cpp \
    src/solutionmodule.cpp \
    src/serialize.cpp \
    src/scsolution.cpp \
    src/scgrouplaw.cpp \
    src/enummap.cpp

HEADERS += \
    include/solution.h \
    stdafx.h \
    include/grouplaw.h \
    include/wedge.h \
    include/probe.h \
    include/gconfig.h \
    include/focalaw.h \
    include/beamlaw.h \
    include/solutionmodule.h \
    include/serialize.h \
    include/scsolution.h \
    include/scgrouplaw.h \
    include/qrange.h \
    include/qobjvector.h \
    include/globaltype.h
