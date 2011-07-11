#-------------------------------------------------
#
# Project created by QtCreator 2011-07-06T12:08:32
#
#-------------------------------------------------

QT       += core gui

TARGET = opencc-gui
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    aboutdialog.cpp \
    convertfiledialog.cpp \
    converter.cpp \
    fileselector.cpp \
    charsetdetector.cpp \
    textreader.cpp

HEADERS  += mainwindow.h \
    opencc.h \
    opencc_types.h \
    aboutdialog.h \
    convertfiledialog.h \
    converter.h \
    fileselector.h \
    uchardet.h \
    charsetdetector.h \
    textreader.h

FORMS    += mainwindow.ui \
    aboutdialog.ui \
    convertfiledialog.ui

TRANSLATIONS += ../l10n/zhs.ts \
    ../l10n/zht.ts

OTHER_FILES +=
