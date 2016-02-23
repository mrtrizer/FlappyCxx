INCLUDEPATH  += $$PWD

HEADERS += \
    $$PWD/core/gctrl.h \
    $$PWD/core/gobj.h \
    $$PWD/shapes/gobjrect.h \
    $$PWD/shapes/gobjcircle.h \
    $$PWD/core/gltools.h \
    $$PWD/core/gobjcamera.h \
    $$PWD/core/gcollider.h \
    $$PWD/bird.h \
    $$PWD/core/gviewshape.h \
    $$PWD/core/gworldview.h \
    $$PWD/core/gworldmodel.h \
    $$PWD/core/gview.h \
    $$PWD/flappyworld.h \
    $$PWD/tube.h \
    $$PWD/core/gpos.h \
    $$PWD/flappyctrl.h \
    $$PWD/flappymenu.h \
    $$PWD/core/gobjpointer.h \
    $$PWD/flappyslider.h \
    $$PWD/button.h \
    $$PWD/core/gcontext.h \
    $$PWD/core/glshaderprogram.h \
    $$PWD/core/glattribarray.h \
    $$PWD/core/gtools.h


SOURCES += \
    $$PWD/core/gctrl.cpp \
    $$PWD/core/gobj.cpp \
    $$PWD/core/gltools.cpp \
    $$PWD/core/gobjcamera.cpp \
    $$PWD/core/gcollider.cpp \
    $$PWD/core/gviewshape.cpp \
    $$PWD/core/gworldmodel.cpp \
    $$PWD/core/gworldview.cpp \
    $$PWD/core/gpos.cpp \
    $$PWD/flappymenu.cpp \
    $$PWD/flappyworld.cpp \
    $$PWD/flappyctrl.cpp \
    $$PWD/bird.cpp \
    $$PWD/button.cpp \
    $$PWD/core/glshaderprogram.cpp \
    $$PWD/core/glattribarray.cpp \
    $$PWD/core/gtools.cpp

LIBS += -lGL -lglut -lGLEW -lGLU
