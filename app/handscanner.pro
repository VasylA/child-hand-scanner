QT += widgets multimedia

CONFIG += c++11

TARGET = handscanner

HEADERS = mainwindow.h \
          startwidget.h \
          scanwidget.h \
          accessgrantedwidget.h \
          accessdeniedwidget.h \
          gpio_class.h \
          testpointscontroller.h

SOURCES = main.cpp \
          mainwindow.cpp \
          startwidget.cpp \
          scanwidget.cpp \
          accessgrantedwidget.cpp \
          accessdeniedwidget.cpp \
          gpio_class.cpp \
          testpointscontroller.cpp

RESOURCES += \
    resource.qrc
