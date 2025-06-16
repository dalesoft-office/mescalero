QT -= gui

TEMPLATE = lib
TARGET = mscl
DEFINES += MESCALERO_LIBRARY
CONFIG += c++17
VERSION = 0.22.0

win32-msvc {
  ICCLibPath = $$PWD/libraries/lcms/win
  RAWLibPath = $$PWD/libraries/libraw/win
  TRACELibPath = $$PWD/libraries/potrace/win
  LIBS += -llibraw
  
  #Static LibRaw defines
  DEFINES += LIBRAW_WIN32_DLLDEFS LIBRAW_NODLL

  #To avoid warning LNK4098 that LIBCMT conflicts
  #See more at https://learn.microsoft.com/en-us/cpp/error-messages/tool-errors/linker-tools-warning-lnk4098
  QMAKE_LFLAGS += /NODEFAULTLIB:libcmt.lib /NODEFAULTLIB:libcmtd.lib /NODEFAULTLIB:msvcrtd.lib

  #To avoid warning 4286 that xmlFree is wrong imported
  QMAKE_LFLAGS += /ignore:4286
}

linux-g++ {
  ICCLibPath = $$PWD/libraries/lcms/linux
  RAWLibPath = $$PWD/libraries/libraw/linux
  TRACELibPath = $$PWD/libraries/potrace/linux
  LIBS += -lraw
}

macx-clang {
  ICCLibPath = $$PWD/libraries/lcms/macos
  RAWLibPath = $$PWD/libraries/libraw/macos
  TRACELibPath = $$PWD/libraries/potrace/macos
  LIBS += -llibraw

  build_platform = macosx

  QMAKE_APPLE_DEVICE_ARCHS=arm64
  QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.12
}

LIBS += -llcms2 -lpotrace

INCLUDEPATH += $$PWD/interface

QMAKE_LIBDIR += $$ICCLibPath $$RAWLibPath $$TRACELibPath

SOURCES += \
    $$PWD/sources/mscl_ll.cpp  \
    $$PWD/sources/mscl_icc_littlecms.cpp \
    $$PWD/sources/mscl_raw_libraw.cpp \
    $$PWD/sources/mscl_trace_potrace.cpp

HEADERS += \
    $$PWD/libraries/lcms/lcms2.h \
    $$PWD/libraries/libraw/libraw.h \
    $$PWD/libraries/libraw/libraw_alloc.h \
    $$PWD/libraries/libraw/libraw_const.h \
    $$PWD/libraries/libraw/libraw_datastream.h \
    $$PWD/libraries/libraw/libraw_internal.h \
    $$PWD/libraries/libraw/libraw_types.h \
    $$PWD/libraries/libraw/libraw_version.h \
    $$PWD/libraries/potrace/potracelib.h \
    $$PWD/proxies/lcms2_defines.h \
    $$PWD/proxies/lcms2.h \
    $$PWD/proxies/libraw_defines.h \
    $$PWD/proxies/libraw.h \
    $$PWD/interface/mscl_defines.h \
    $$PWD/interface/mscl.h
