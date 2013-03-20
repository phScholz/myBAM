#-------------------------------------------------
#
# Project created by QtCreator 2013-01-26T10:55:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = myBAM
TEMPLATE = app


SOURCES += main.cpp\
        bamwindow.cpp \
    bamcore.cpp \
    baminput.cpp \
    bamconst.cpp \
    qcustomplot.cpp \
    bameff.cpp \
    bamsource.cpp

HEADERS  += bamwindow.h \
    bamcore.h \
    baminput.h \
    bamconst.h \
    qcustomplot.h \
    bameff.h \
    bamsource.h

FORMS    += bamwindow.ui

RESOURCES += myBAM.qrc \
    myBAM.qrc
