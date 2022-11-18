QT -= gui

TEMPLATE = lib
TARGET = mscl
DEFINES += MESCALERO_LIBRARY
CONFIG += c++17

win32-msvc:{
  ICCLibPath = $$PWD/libraries/lcms/win
  RAWLibPath = $$PWD/libraries/libraw/win
  LIBS += -llibraw
  
  #Static LibRaw defines
  DEFINES += LIBRAW_WIN32_DLLDEFS LIBRAW_NODLL
}

linux-g++:{
  ICCLibPath = $$PWD/libraries/lcms/linux
  RAWLibPath = $$PWD/libraries/libraw/linux
  LIBS += -lraw

  VERSION = 0.8.0
}

LIBS += -llcms2

INCLUDEPATH += \
    $$PWD/libraries/lcms \
    $$PWD/libraries/libraw

QMAKE_LIBDIR += $$ICCLibPath $$RAWLibPath

SOURCES += \
    $$PWD/sources/mscl_ll.cpp  \
    $$PWD/sources/mscl_icc_littlecms.cpp \
    $$PWD/sources/mscl_raw_libraw.cpp

HEADERS += \
    $$PWD/libraries/lcms/lcms2.h \
    $$PWD/libraries/libraw/libraw.h \
    $$PWD/libraries/libraw/libraw_alloc.h \
    $$PWD/libraries/libraw/libraw_const.h \
    $$PWD/libraries/libraw/libraw_datastream.h \
    $$PWD/libraries/libraw/libraw_internal.h \
    $$PWD/libraries/libraw/libraw_types.h \
    $$PWD/libraries/libraw/libraw_version.h \
    $$PWD/interface/lcms2_defines.h \
    $$PWD/interface/lcms2.h \
    $$PWD/interface/libraw_defines.h \
    $$PWD/interface/libraw.h \
    $$PWD/interface/mscl_defines.h \
    $$PWD/interface/mscl.h

# Default rules for deployment.
#unix {
#    target.path = /usr/lib
#}
#!isEmpty(target.path): INSTALLS += target

