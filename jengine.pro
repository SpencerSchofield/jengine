TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
	src/jengine_application.cpp \
	src/jengine_entry.cpp \
	src/jengine_file.cpp \
	src/jengine_globject.cpp \
	src/jengine_indexbuffer.cpp \
	src/jengine_renderer.cpp \
	src/jengine_script.cpp \
	src/jengine_shader.cpp \
	src/jengine_vertexarray.cpp \
	src/jengine_vertexattribute.cpp \
	src/jengine_vertexbuffer.cpp \
	src/test.cpp

HEADERS += \
	src/jengine.h \
	src/jengine_application.h \
	src/jengine_file.h \
	src/jengine_globject.h \
	src/jengine_indexbuffer.h \
	src/jengine_renderer.h \
	src/jengine_script.h \
	src/jengine_shader.h \
	src/jengine_vertexarray.h \
	src/jengine_vertexattribute.h \
	src/jengine_vertexbuffer.h \
	src/test.h

LIBS += \
	-lGL \
	-lGLEW \
	-lglfw

DISTFILES += \
	res/shaders/shader.frag \
	res/shaders/shader.vert
