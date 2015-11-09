#-------------------------------------------------
#
# Project created by QtCreator 2011-07-06T12:08:32
#
#-------------------------------------------------

QT       += core widgets

TARGET = opencc-gui
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    aboutdialog.cpp \
    converter.cpp \
    fileselector.cpp \
    charsetdetector.cpp \
    textreader.cpp \
    texteditor.cpp \
    convertfiledialog.cpp

HEADERS  += mainwindow.h \
    opencc.h \
    opencc_types.h \
    aboutdialog.h \
    convertfiledialog.h \
    converter.h \
    fileselector.h \
    uchardet.h \
    charsetdetector.h \
    textreader.h \
    texteditor.h

FORMS    += mainwindow.ui \
    aboutdialog.ui \
    convertfiledialog.ui

TRANSLATIONS += ../l10n/zhs.ts \
    ../l10n/zht.ts

OTHER_FILES +=

RESOURCES += \
    icon.qrc

ICON = res/opencc.icns

QMAKE_INFO_PLIST = res/opencc.plist

RC_FILE = win.rc
