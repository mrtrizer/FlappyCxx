INCLUDEPATH  += $$PWD

HEADERS += \
    $$PWD/gworld.h \
    $$PWD/gctrl.h \
    $$PWD/gobj.h \
    $$PWD/gobjrect.h \
    $$PWD/gobjcircle.h \
    $$PWD/gview.h \
    $$PWD/gvisializer.h \
    $$PWD/gobjcontainer.h

SOURCES += \
    $$PWD/gworld.cpp \
    $$PWD/gctrl.cpp \
    $$PWD/gobj.cpp \
    $$PWD/gobjrect.cpp \
    $$PWD/gobjcircle.cpp \
    $$PWD/main.cpp \
    $$PWD/gview.cpp \
    $$PWD/gvisializer.cpp \
    $$PWD/gobjcontainer.cpp

QMAKE_CXXFLAGS += -std=c++11
