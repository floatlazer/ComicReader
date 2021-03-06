#-------------------------------------------------
#
# Project created by QtCreator 2017-12-20T11:15:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ComicReader
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        comicreader.cpp \
        page.cpp \
        pageloader.cpp \
        decompress.cpp \
    comicreaderActions.cpp

HEADERS += \
        comicreader.h \
        page.h \
        pageloader.h \
        decompress.h

FORMS += \
        comicreader.ui

RESOURCES += \
    res.qrc


unix|win32: LIBS += -L$$PWD/unarr/build/release/ -lunarr

INCLUDEPATH += $$PWD/unarr
DEPENDPATH += $$PWD/unarr

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/unarr/build/release/unarr.lib
else:unix|win32-g++: PRE_TARGETDEPS += $$PWD/unarr/build/release/libunarr.a
