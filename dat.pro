
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
desfire/files/stdFile.cpp \
desfire/files/backupFile.cpp \
desfire/files/valueFile.cpp \
desfire/files/cRecordFile.cpp \
desfire/files/lRecordFile.cpp \
model/desfire_model.cpp

HEADERS  += mainwindow.h \
desfire/application.h \
desfire/card.h \
desfire/key.h \
desfire/defaultFile.h \
desfire/item.h \
desfire/file.h \
desfire/device.h \
desfire/files/stdFile.h \
desfire/files/backupFile.h \
desfire/files/valueFile.h \
desfire/files/cRecordFile.h \
desfire/files/lRecordFile.h \
model/desfire_model.h

FORMS    += mainwindow.ui

LIBS += -lnfc -lfreefare

QMAKE_CXXFLAGS += -std=c++0x

