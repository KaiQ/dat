
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
            model/desfire_model.cpp \
            widgets/stdfilewidget.cpp \
            widgets/valuefilewidget.cpp \
            widgets/lrecordfilewidget.cpp \
            widgets/cardwidget.cpp \
            widgets/applicationwidget.cpp \
            widgets/filewidget.cpp \
    GUI/createapplication.cpp \
    GUI/keysettings.cpp


HEADERS  += mainwindow.h \
            desfire/application.h \
            desfire/card.h \
            desfire/key.h \
            desfire/item.h \
            desfire/desfireFile.h \
            desfire/device.h \
            model/desfire_model.h \
            widgets/stdfilewidget.h \
            widgets/backupfilewidget.h \
            widgets/valuefilewidget.h \
            widgets/lrecordfilewidget.h \
            widgets/crecordfilewidget.h \
            widgets/cardwidget.h \
            widgets/applicationwidget.h \
            widgets/filewidget.h \
            interface/fileinterface.h \
    GUI/createapplication.h \
    GUI/keysettings.h

FORMS    += GUI/mainwindow.ui \
            GUI/stdfilewidget.ui \
            GUI/backupfilewidget.ui \
            GUI/valuefilewidget.ui \
            GUI/lrecordfilewidget.ui \
            GUI/crecordfilewidget.ui \
            GUI/cardwidget.ui \
            GUI/applicationwidget.ui \
            GUI/filewidget.ui \
    GUI/createapplication.ui \
    GUI/keysettings.ui

LIBS += -lnfc -lfreefare

QMAKE_CXXFLAGS += -std=c++0x -O3

