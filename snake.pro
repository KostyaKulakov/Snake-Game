#-------------------------------------------------
#
# Project created by QtCreator 2014-01-08T18:10:01
#
#-------------------------------------------------

QT       += core gui opengl widgets multimedia sql
QTPLUGIN += QSQLMYSQL
LIBS += -LGLU -lglut

TARGET = snake-nokia
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11

INCLUDEPATH += src/ ui/ include/

SOURCES += src/main.cpp\
        src/mainwindow.cpp \
    src/glwidget.cpp \
    src/log.cpp \
    src/windowsetting.cpp \
    src/settings.cpp \
    src/snake.cpp \
    src/linksnake.cpp \
    src/records.cpp \
    src/database.cpp \
    src/registration.cpp

HEADERS  += include/mainwindow.h \
    include/glwidget.h \
    include/log.h \
    include/windowsetting.h \
    include/settings.h \
    include/snake.h \
    include/linksnake.h \
    include/records.h \
    include/database.h \
    include/recordstruct.h \
    include/registration.h

FORMS    += ui/mainwindow.ui \
    ui/windowsetting.ui \
    ui/windowrecords.ui \
    ui/windowregistration.ui
