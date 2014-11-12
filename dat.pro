
QT += core gui

TARGET = dat
TEMPLATE = app

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES +=  main.cpp\
mainwindow.cpp \
desfire/application.cpp \
desfire/card.cpp \
desfire/key.cpp \
desfire/defaultFile.cpp \
desfire/item.cpp \
desfire/file.cpp \
desfire/device.cpp \
desfire/files/std.cpp \
model/desfire_model.cpp

HEADERS  += mainwindow.h \
desfire/application.h \
desfire/card.h \
desfire/key.h \
desfire/defaultFile.h \
desfire/item.h \
desfire/file.h \
desfire/device.h \
desfire/files/std.h \
model/desfire_model.h

FORMS    += mainwindow.ui

LIBS += -lnfc -lfreefare

QMAKE_CXXFLAGS += -std=c++0x

