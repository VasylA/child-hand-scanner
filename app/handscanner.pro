QT += widgets

CONFIG += c++11

TARGET = handscanner

HEADERS = mainwindow.h \
          startwidget.h \
          scanwidget.h \
          accessgrantedwidget.h \
          accessdeniedwidget.h

SOURCES = main.cpp \
          mainwindow.cpp \
          startwidget.cpp \
          scanwidget.cpp \
          accessgrantedwidget.cpp \
          accessdeniedwidget.cpp
