QT += core testlib
QT -= gui

TARGET = test
CONFIG += console
CONFIG -= app_bundle
CONFIG += testcase

TEMPLATE = app

LIBS += -lffi

include("../src/FlappyCxx.pri")

QMAKE_CXXFLAGS += -std=gnu++11

SOURCES += main.cpp
HEADERS += \
    test_gobjcontainer.h \
    test_tools.h \
    test_gobj.h

