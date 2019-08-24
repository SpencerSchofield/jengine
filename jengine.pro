TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
	src/jengine_entry.cpp \
	src/jengine_vertexattribute.cpp \
	src/jengine_vertexbuffer.cpp \
	src/test.cpp

HEADERS += \
	src/jengine.h \
	src/jengine_application.h \
	src/jengine_vertexattribute.h \
	src/jengine_vertexbuffer.h \
	src/test.h

LIBS += \
	-lGL
	-lGLEW
