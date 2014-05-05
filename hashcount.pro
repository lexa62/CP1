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
    driver.cpp \
    md5.cpp

HEADERS  += \
    crc32.h \
    hashcount.h \
    selectingaction.h \
    hashviewwidget.h \
    md5.h

FORMS    +=
