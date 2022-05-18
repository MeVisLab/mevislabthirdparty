# ---------------- ivfix profile -------------------

TEMPLATE = app

TARGET = ivfix

DESTDIR = ../../../../../bin

# add dependencies of this project here

CONFIG += console inventor
macx:CONFIG -= app_bundle

win32::QMAKE_CXXFLAGS += /TP

win32::DEFINES += WIN32
win32::DEFINES -= UNICODE

# include settings of required libraries
include( $(MEVIS_THIRDPARTY_LIB)/Configuration/MeVis_ThirdParty.pri )

HEADERS += \
  IfAssert.h \
  IfBuilder.h \
  IfCollector.h \
  IfCondenser.h \
  IfFixer.h \
  IfFlattener.h \
  IfHasher.h \
  IfHolder.h \
  IfMerger.h \
  IfReplacer.h \
  IfReporter.h \
  IfShape.h \
  IfShapeList.h \
  IfSorter.h \
  IfStripper.h \
  IfTypes.h \
  IfWeeder.h

SOURCES += \
  IfBuilder.cpp \
  IfCollector.cpp \
  IfCondenser.cpp \
  IfFixer.cpp \
  IfFlattener.cpp \
  IfHasher.cpp \
  IfHolder.cpp \
  IfMerger.cpp \
  IfReplacer.cpp \
  IfReporter.cpp \
  IfShape.cpp \
  IfShapeList.cpp \
  IfSorter.cpp \
  IfStripper.cpp \
  IfTypes.cpp \
  IfWeeder.cpp \
  ivfix.cpp

