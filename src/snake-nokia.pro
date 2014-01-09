#-------------------------------------------------
#
# Project created by QtCreator 2014-01-08T18:10:01
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = snake-nokia
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    glwidget.cpp

HEADERS  += mainwindow.h \
    glwidget.h

FORMS    += mainwindow.ui
