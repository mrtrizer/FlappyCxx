QT += core testlib
QT -= gui

TARGET = test
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

LIBS += -lGL -lglut -lGLEW -lGLU

include("../../src/FlappyCxx.pri")

QMAKE_CXXFLAGS += -std=gnu++11

SOURCES += main.cpp

HEADERS +=

