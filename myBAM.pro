#-------------------------------------------------
#
# Project created by QtCreator 2013-01-26T10:55:15
#
#-------------------------------------------------

QT       += core gui

TARGET = ./bin/myBAM
TEMPLATE = app


SOURCES += ./src/main.cpp\
        ./src/bamwindow.cpp \
    ./src/bamcore.cpp \
    ./src/baminput.cpp \
    ./src/bamconst.cpp \
    ./src/bameff.cpp \
    ./src/bamsource.cpp \
    ./src/bamclover.cpp \
    ./src/creatorwindow.cpp \
    ./src/resultdialog.cpp

HEADERS  += ./src/bamwindow.h \
    ./src/bamcore.h \
    ./src/baminput.h \
    ./src/bamconst.h \
    ./src/bameff.h \
    ./src/bamsource.h \
    ./src/bamclover.h \
    ./src/creatorwindow.h \
    ./src/resultdialog.h

FORMS    += ./src/bamwindow.ui \
    ./src/creatorwindow.ui \
    ./src/resultdialog.ui

RESOURCES += ./src/myBAM.qrc \
    ./src/myBAM.qrc

OBJECTS_DIR =./obj
UI_DIR = ./ui
MOC_DIR= ./moc
