#-------------------------------------------------
#
# Project created by QtCreator 2014-11-16T16:14:22
#
#-------------------------------------------------

QT       += core gui websockets


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


CONFIG += c++11
TARGET = inquisitor
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++11 -stdlib=libc++ -mmacosx-version-min=10.7
LIBS += -stdlib=libc++ -mmacosx-version-min=10.7 -lcurl
INCLUDEPATH += /usr/local/include

SOURCES += main.cpp\
        mainwindow.cpp \
    cap.cpp \
    helpers.cpp \
    serverform.cpp \
    deviceform.cpp \
    debugdock.cpp \
    appiumclient.cpp \
    inspector.cpp \
    seleniumpp/capabilities.cpp \
    seleniumpp/cookie.cpp \
    seleniumpp/element.cpp \
    seleniumpp/http.cpp \
    seleniumpp/jsonengine.cpp \
    seleniumpp/log.cpp \
    seleniumpp/restio.cpp \
    seleniumpp/seleniumanswer.cpp \
    seleniumpp/session.cpp \
    seleniumpp/utils.cpp \
    seleniumpp/webdriver.cpp

HEADERS  += mainwindow.h \
    cap.h \
    helpers.h \
    serverform.h \
    deviceform.h \
    debugdock.h \
    appiumclient.h \
    inspector.h \
    seleniumpp/assoc.hpp \
    seleniumpp/capabilities.hpp \
    seleniumpp/cookie.hpp \
    seleniumpp/element.hpp \
    seleniumpp/exceptions.hpp \
    seleniumpp/globals.hpp \
    seleniumpp/http.hpp \
    seleniumpp/jsonengine.hpp \
    seleniumpp/log.hpp \
    seleniumpp/restio.hpp \
    seleniumpp/seleniumanswer.hpp \
    seleniumpp/session.hpp \
    seleniumpp/utils.hpp \
    seleniumpp/webdriver.hpp

FORMS    += mainwindow.ui \
    serverform.ui \
    deviceform.ui \
    inspector.ui

OTHER_FILES +=

RESOURCES += \
    resources.qrc

DISTFILES +=
