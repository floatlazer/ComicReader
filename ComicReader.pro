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
    comicreaderActions.cpp \
    imageprocess.cpp

HEADERS += \
        comicreader.h \
        page.h \
        pageloader.h \
        decompress.h \
    imageprocess.h

FORMS += \
        comicreader.ui

RESOURCES += \
    res.qrc

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/./release/ -lunarr
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/./debug/ -lunarr
else:unix: LIBS += -L$$PWD/./ -lunarr

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/./release/libunarr.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/./debug/libunarr.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/./release/unarr.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/./debug/unarr.lib
else:unix: PRE_TARGETDEPS += $$PWD/./libunarr.a
