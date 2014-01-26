#-------------------------------------------------
#
# Project created by QtCreator 2014-01-08T18:10:01
#
#-------------------------------------------------

QT       += core gui opengl
LIBS += -LGLU -lglut

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = snake-nokia
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    glwidget.cpp \
    log.cpp \
    windowsetting.cpp

HEADERS  += mainwindow.h \
    glwidget.h \
    log.h \
    windowsetting.h

FORMS    += mainwindow.ui \
    windowsetting.ui
