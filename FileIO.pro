#-------------------------------------------------
#
# Project created by QtCreator 2014-05-08T15:08:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FileIO
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    read_write_datfile.cpp

HEADERS  += mainwindow.h \
    read_write_globals.h

FORMS    += mainwindow.ui
