#-------------------------------------------------
#
# Project created by QtCreator 2014-05-09T16:45:00
#
#-------------------------------------------------

QT       += core gui
QT       += opengl
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Grafix
TEMPLATE = app
CONFIG += c++11

INCLUDEPATH += "../libCGE/include" \
"../libCGE/include/filters"

DEFINES += LIBCGE4QT_LIB=1

CONFIG(debug, debug|release) {
    DEFINES += DEBUG=1 _DEBUG=1
    unix {
#        LIBS += ../libCGE/lib/libCGE4QTlog.a
    }

    win32 {
        LIBS += ../libCGE/lib/libCGE4QTlog.lib
    }
} else {
    DEFINES += NDEBUG=1 _NDEBUG=1
    unix {
        LIBS += ../libCGE/lib/libCGE4QT.a
    }

    win32 {
        LIBS += ../libCGE/lib/libCGE4QT.lib
    }
}

RESOURCES += mainwindow.qrc

SOURCES += main.cpp\
        GrafixMainWindow.cpp \
    editor/editorMain.cpp \
    collage/collageMain.cpp \
    batch/batchMain.cpp


HEADERS  += GrafixMainWindow.h \
    editor/editorMain.h \
    collage/collageMain.h \
    batch/batchMain.h \
    main.h


FORMS    += mainwindow.ui \
    editor/editorWindow.ui

