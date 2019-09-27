TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
	src/input/jengine_input.cpp \
	src/input/jengine_keyboard.cpp \
	src/input/jengine_mouse.cpp \
	src/jengine_application.cpp \
	src/jengine_camera.cpp \
	src/jengine_entry.cpp \
	src/jengine_file.cpp \
	src/jengine_indexbuffer.cpp \
	src/jengine_logging.cpp \
	src/jengine_model.cpp \
	src/jengine_renderer.cpp \
	src/jengine_script.cpp \
	src/jengine_shader.cpp \
	src/jengine_vertexarray.cpp \
	src/jengine_vertexattribute.cpp \
	src/jengine_vertexbuffer.cpp \
	src/test.cpp

HEADERS += \
	src/input/jengine_input.h \
	src/input/jengine_keyboard.h \
	src/input/jengine_mouse.h \
	src/jengine.h \
	src/jengine_application.h \
	src/jengine_camera.h \
	src/jengine_define.h \
	src/jengine_file.h \
	src/jengine_globject.h \
	src/jengine_indexbuffer.h \
	src/jengine_logging.h \
	src/jengine_model.h \
	src/jengine_renderer.h \
	src/jengine_script.h \
	src/jengine_shader.h \
	src/jengine_vertexarray.h \
	src/jengine_vertexattribute.h \
	src/jengine_vertexbuffer.h \
	src/script/jengine_ast.h \
	src/script/jengine_interpreter.h \
	src/script/jengine_lexer.h \
	src/script/jengine_parser.h \
	src/script/jengine_symbol.h \
	src/script/jengine_tokens.h \
	src/test.h

LIBS += \
	-lGL \
	-lGLEW \
	-lglfw

DISTFILES += \
	res/models/cube.mtl \
	res/models/cube.obj \
	res/notes \
	res/scripts/ex1.jua \
	res/shaders/shader.frag \
	res/shaders/shader.vert

CONFIG += precompile_header
PRECOMPILED_HEADER = src/pch.h
HEADERS += src/pch.h


QMAKE_CXXFLAGS_DEBUG += -DJENGINE_DEBUG

QMAKE_CXXFLAGS_RELEASE += -DJENGINE_RELEASE
QMAKE_CXXFLAGS_RELEASE -= -O
QMAKE_CXXFLAGS_RELEASE -= -O1
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE *= -O3

QMAKE_CXXFLAGS += -Werror
