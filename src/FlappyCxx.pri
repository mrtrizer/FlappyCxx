INCLUDEPATH  += $$PWD

HEADERS += \
    $$PWD/core/gctrl.h \
    $$PWD/core/gobj.h \
    $$PWD/shapes/gobjrect.h \
    $$PWD/shapes/gobjcircle.h \
    $$PWD/gl/gltools.h \
    $$PWD/core/gobjcamera.h \
    $$PWD/core/gcollider.h \
    $$PWD/bird.h \
    $$PWD/gl/gworldmodel.h \
    $$PWD/core/gview.h \
    $$PWD/tube.h \
    $$PWD/core/gpos.h \
    $$PWD/core/gobjpointer.h \
    $$PWD/button.h \
    $$PWD/core/gcontext.h \
    $$PWD/gl/glshaderprogram.h \
    $$PWD/gl/glattribarray.h \
    $$PWD/core/gtools.h \
    $$PWD/gl/gltexture.h \
    $$PWD/core/gviewfactory.h \
    $$PWD/core/gpresenter.h \
    $$PWD/shapes/gdecor.h \
    $$PWD/floor.h \
    $$PWD/coin.h \
    $$PWD/ctrl.h \
    $$PWD/menu.h \
    $$PWD/slider.h \
    $$PWD/world.h \
    $$PWD/gl/glviewfactory.h \
    $$PWD/gl/glworldview.h \
    $$PWD/gl/glviewshape.h \
    $$PWD/gl/glviewsprite.h \
    $$PWD/core/gworldview.h


SOURCES += \
    $$PWD/core/gctrl.cpp \
    $$PWD/core/gobj.cpp \
    $$PWD/gl/gltools.cpp \
    $$PWD/core/gobjcamera.cpp \
    $$PWD/core/gcollider.cpp \
    $$PWD/core/gworldmodel.cpp \
    $$PWD/core/gpos.cpp \
    $$PWD/bird.cpp \
    $$PWD/button.cpp \
    $$PWD/gl/glshaderprogram.cpp \
    $$PWD/gl/glattribarray.cpp \
    $$PWD/core/gtools.cpp \
    $$PWD/gl/gltexture.cpp \
    $$PWD/core/gpresenter.cpp \
    $$PWD/floor.cpp \
    $$PWD/coin.cpp \
    $$PWD/ctrl.cpp \
    $$PWD/menu.cpp \
    $$PWD/world.cpp \
    $$PWD/gl/glviewfactory.cpp \
    $$PWD/gl/glworldview.cpp \
    $$PWD/gl/glviewshape.cpp \
    $$PWD/gl/glviewsprite.cpp \
    $$PWD/core/gworldview.cpp

LIBS += -lGL -lglut -lGLEW -lGLU
