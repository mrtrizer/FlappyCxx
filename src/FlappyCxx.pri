INCLUDEPATH  += $$PWD

HEADERS += \
    $$PWD/gworld.h \
    $$PWD/gctrl.h \
    $$PWD/gobj.h \
    $$PWD/gobjrect.h \
    $$PWD/gobjcircle.h \
    $$PWD/gview.h \
    $$PWD/gvisializer.h \
    $$PWD/gobjcontainer.h \
    $$PWD/tools.h \
    $$PWD/shader.h \
    $$PWD/attribarray.h \
    $$PWD/gltools.h \
    $$PWD/gobjcamera.h


SOURCES += \
    $$PWD/gworld.cpp \
    $$PWD/gctrl.cpp \
    $$PWD/gobj.cpp \
    $$PWD/gobjrect.cpp \
    $$PWD/gobjcircle.cpp \
    $$PWD/gview.cpp \
    $$PWD/gvisializer.cpp \
    $$PWD/gobjcontainer.cpp \
    $$PWD/tools.cpp \
    $$PWD/shader.cpp \
    $$PWD/attribarray.cpp \
    $$PWD/gltools.cpp \
    $$PWD/gobjcamera.cpp

QMAKE_CXXFLAGS += -std=c++1y
LIBS += -lGL -lglut -lGLEW -lGLU
