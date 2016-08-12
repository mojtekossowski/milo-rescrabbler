QT += core
QT -= gui

CONFIG += c++11

TARGET = milo-rescrabbler
CONFIG += console
CONFIG -= app_bundle

DESTDIR = $$OUT_PWD/../bin

dictionary.path = $${DESTDIR}/assets/
dictionary.files = assets/words

INSTALLS += dictionary

TEMPLATE = app

SOURCES += main.cpp \
    dictionaryword.cpp \
    dictionary.cpp \
    lettersstack.cpp

HEADERS += \
    dictionaryword.h \
    dictionary.h \
    lettersstack.h \
    exceptions.h
