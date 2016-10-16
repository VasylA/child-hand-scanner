QT += core widgets

CONFIG += c++11

TARGET = handscanner
TEMPLATE = app

HEADERS       = mainwindow.h \
                touchwidget.h

SOURCES       = main.cpp \
                mainwindow.cpp \
                touchwidget.cpp
