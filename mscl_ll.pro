QT -= gui

TEMPLATE = lib
TARGET = mscl
DEFINES += MESCALERO_LIBRARY
CONFIG += c++17

win32-msvc:{
  ICCLibPath = libraries/lcms/win
  RAWLibPath = libraries/libraw/win
  LIBS += -llibraw
  
  #Static LibRaw defines
  DEFINES += LIBRAW_WIN32_DLLDEFS LIBRAW_NODLL
}

linux-g++:{
# ICCLibPath = libraries/lcms/linux
  RAWLibPath = libraries/libraw/linux
  LIBS += -lraw
}

LIBS += -llcms2

INCLUDEPATH += \
    libraries\lcms \
    libraries\libraw

QMAKE_LIBDIR += $$ICCLibPath $$RAWLibPath

SOURCES += \
    sources/mscl_ll.cpp  \
    sources/mscl_icc_littlecms.cpp \
    sources/mscl_raw_libraw.cpp 

HEADERS += \
    libraries/lcms/lcms2.h \
    libraries/libraw/libraw.h \
    libraries/libraw/libraw_alloc.h \
    libraries/libraw/libraw_const.h \
    libraries/libraw/libraw_datastream.h \
    libraries/libraw/libraw_internal.h \
    libraries/libraw/libraw_types.h \
    libraries/libraw/libraw_version.h \
    interface/lcms2_defines.h \
    interface/lcms2.h \
    interface/libraw_defines.h \
    interface/libraw.h \
    interface/mscl_defines.h \
    interface/mscl.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}

!isEmpty(target.path): INSTALLS += target

