TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_CXXFLAGS += -lX11 -lpthreads -larmadillo -llapack -lblas
LIBS = -L/usr/lib/x86_64-linux-gnu -lm -lpthread -lX11 -larmadillo -llapack -lblas -O3
SOURCES += main.cpp \
    rectanglemodel.cpp \
    imagemodel.cpp

HEADERS += \
    rectanglemodel.h \
    imagemodel.h

