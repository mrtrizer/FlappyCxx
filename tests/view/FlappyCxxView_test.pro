QT += core testlib
QT -= gui

TARGET = test
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

include("../../src/FlappyCxx.pri")

QMAKE_CXXFLAGS += -std=gnu++11

SOURCES += main.cpp

DEFINES += VIEW_TYPE=GL

HEADERS +=

