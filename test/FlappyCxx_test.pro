QT += core testlib
QT -= gui

TARGET = test
CONFIG += console
CONFIG -= app_bundle
CONFIG += testcase

TEMPLATE = app

include("../src/FlappyCxx.pri")

QMAKE_CXXFLAGS += -std=c++1y

DEFINES += VIEW_TYPE=GL

SOURCES += main.cpp
HEADERS += \
    test_gobj.h

