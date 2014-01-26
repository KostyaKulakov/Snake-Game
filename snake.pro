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

INCLUDEPATH += src/ ui/ header/

SOURCES += src/main.cpp\
        src/mainwindow.cpp \
    src/glwidget.cpp \
    src/log.cpp \
    src/windowsetting.cpp \
    src/settings.cpp

HEADERS  += header/mainwindow.h \
    header/glwidget.h \
    header/log.h \
    header/windowsetting.h \
    header/settings.h

FORMS    += ui/mainwindow.ui \
    ui/windowsetting.ui
