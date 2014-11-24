#-------------------------------------------------
#
# Project created by QtCreator 2014-11-16T16:14:22
#
#-------------------------------------------------

QT       += core gui
QT+=script

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = inquisitor
TEMPLATE = app

 contains(QT_CONFIG, scripttools): QT += scripttools
SOURCES += main.cpp\
        mainwindow.cpp \
    cap.cpp \
    helpers.cpp \
    appiumengine.cpp \
    eventtimer.cpp

HEADERS  += mainwindow.h \
    cap.h \
    helpers.h \
    appiumengine.h \
    eventtimer.h

FORMS    += mainwindow.ui

OTHER_FILES += \
    caps_meta.json \
    webdriver.js
