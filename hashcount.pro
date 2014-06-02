#-------------------------------------------------
#
# Project created by QtCreator 2014-04-20T13:42:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = hashcount
TEMPLATE = app


SOURCES += main.cpp \
    crc32.cpp \
    hashcount.cpp \
    selectingaction.cpp \
    hashviewwidget.cpp \
    md5.cpp \
    checkfilehashwidget.cpp \
    checkfileshasheswidget.cpp \
    sha1.cpp

HEADERS  += \
    crc32.h \
    hashcount.h \
    selectingaction.h \
    hashviewwidget.h \
    md5.h \
    algorithminterface.h \
    checkfilehashwidget.h \
    checkfileshasheswidget.h \
    sha1.h \
    enumTypes.h

FORMS    +=

OTHER_FILES += \
    icons/monkey_off_32x32.png

RESOURCES += \
    icons.qrc
