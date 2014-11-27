#-------------------------------------------------
#
# Project created by QtCreator 2014-11-16T16:14:22
#
#-------------------------------------------------

QT       += core gui script


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
contains(QT_CONFIG, scripttools): QT += scripttools

CONFIG += c++11
TARGET = inquisitor
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++11 -stdlib=libc++ -mmacosx-version-min=10.7
LIBS += -stdlib=libc++ -mmacosx-version-min=10.7

SOURCES += main.cpp\
        mainwindow.cpp \
    cap.cpp \
    helpers.cpp

HEADERS  += mainwindow.h \
    cap.h \
    helpers.h

FORMS    += mainwindow.ui

OTHER_FILES +=

RESOURCES += \
    resources.qrc
