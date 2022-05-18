TEMPLATE = app

TARGET = GLUTview

DESTDIR = ./

# add dependencies of this project here

CONFIG += inventor glut opengl
win32::CONFIG += console

include ($(MLAB_MeVis_ThirdParty)/Configuration/MeVis_ThirdParty.pri)
# make sure that MeVis_Foundation.pri is included last!
include ($(MLAB_MeVis_Foundation)/Configuration/MeVis_Foundation.pri)

OBJECTS_DIR = obj

SOURCES += \
    ivmain.cpp \
    ivscene.cpp
