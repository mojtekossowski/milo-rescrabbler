QT += core
QT -= gui

CONFIG += c++11

TARGET = anagramy
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    dictionaryword.cpp \
    dictionary.cpp

HEADERS += \
    dictionaryword.h \
    dictionary.h
