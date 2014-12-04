#-------------------------------------------------
#
# Project created by QtCreator 2014-11-16T16:14:22
#
#-------------------------------------------------

QT       += core gui qml


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


CONFIG += c++11
TARGET = inquisitor
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++11 -stdlib=libc++ -mmacosx-version-min=10.7
LIBS += -stdlib=libc++ -mmacosx-version-min=10.7

SOURCES += main.cpp\
        mainwindow.cpp \
    cap.cpp \
    helpers.cpp \
    appiumengine.cpp \
    eventtimer.cpp \
    serverform.cpp \
    xmlhttprequest.cpp

HEADERS  += mainwindow.h \
    cap.h \
    helpers.h \
    appiumengine.h \
    eventtimer.h \
    serverform.h \
    xmlhttprequest.h

FORMS    += mainwindow.ui \
    serverform.ui

OTHER_FILES +=

RESOURCES += \
    resources.qrc
