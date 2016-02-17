INCLUDEPATH  += $$PWD

HEADERS += \
    $$PWD/gctrl.h \
    $$PWD/gobj.h \
    $$PWD/gobjrect.h \
    $$PWD/gobjcircle.h \
    $$PWD/tools.h \
    $$PWD/shader.h \
    $$PWD/attribarray.h \
    $$PWD/gltools.h \
    $$PWD/gobjcamera.h \
    $$PWD/gcollider.h \
    $$PWD/bird.h \
    $$PWD/gviewshape.h \
    $$PWD/gworldview.h \
    $$PWD/gworldmodel.h \
    $$PWD/gview.h


SOURCES += \
    $$PWD/gctrl.cpp \
    $$PWD/gobj.cpp \
    $$PWD/tools.cpp \
    $$PWD/shader.cpp \
    $$PWD/attribarray.cpp \
    $$PWD/gltools.cpp \
    $$PWD/gobjcamera.cpp \
    $$PWD/gcollider.cpp \
    $$PWD/bird.cpp \
    $$PWD/gviewshape.cpp \
    $$PWD/gworldmodel.cpp \
    $$PWD/gworldview.cpp

QMAKE_CXXFLAGS += -std=c++1y
LIBS += -lGL -lglut -lGLEW -lGLU
