
QT += core gui

TARGET = dat
TEMPLATE = app

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES +=  main.cpp\
            mainwindow.cpp \
            desfire/application.cpp \
            desfire/card.cpp \
            desfire/key.cpp \
            desfire/item.cpp \
            desfire/desfireFile.cpp \
            desfire/device.cpp \
            desfire/files/stdFile.cpp \
            desfire/files/backupFile.cpp \
            desfire/files/valueFile.cpp \
            desfire/files/cRecordFile.cpp \
            desfire/files/lRecordFile.cpp \
            model/desfire_model.cpp \
            widgets/stdfilewidget.cpp \
            widgets/backupfilewidget.cpp \
            widgets/valuefilewidget.cpp \
            widgets/lrecordfilewidget.cpp \
            widgets/crecordfilewidget.cpp \
            widgets/cardwidget.cpp \
            widgets/applicationwidget.cpp


HEADERS  += mainwindow.h \
            desfire/application.h \
            desfire/card.h \
            desfire/key.h \
            desfire/item.h \
            desfire/desfireFile.h \
            desfire/device.h \
            desfire/files/stdFile.h \
            desfire/files/backupFile.h \
            desfire/files/valueFile.h \
            desfire/files/cRecordFile.h \
            desfire/files/lRecordFile.h \
            model/desfire_model.h \
            widgets/stdfilewidget.h \
            widgets/backupfilewidget.h \
            widgets/valuefilewidget.h \
            widgets/lrecordfilewidget.h \
            widgets/crecordfilewidget.h \
            widgets/cardwidget.h \
            widgets/applicationwidget.h

FORMS    += GUI/mainwindow.ui \
            GUI/stdfilewidget.ui \
            GUI/backupfilewidget.ui \
            GUI/valuefilewidget.ui \
            GUI/lrecordfilewidget.ui \
            GUI/crecordfilewidget.ui \
            GUI/cardwidget.ui \
            GUI/applicationwidget.ui

LIBS += -lnfc -lfreefare

QMAKE_CXXFLAGS += -std=c++0x -O3

