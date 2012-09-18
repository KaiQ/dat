# -------------------------------------------------
# Project created by QtCreator 2011-02-28T12:39:14
# -------------------------------------------------
TARGET = dat
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    dialog.cpp \
    key.cpp \
    application.cpp \
    file.cpp \
    standartfile.cpp \
    backupfile.cpp \
    valuefile.cpp \
    lrecordfile.cpp \
    crecordfile.cpp \
    stdbackupwidget.cpp \
    valuewidget.cpp \
    lcrecordwidget.cpp
HEADERS += mainwindow.h \
    dialog.h \
    key.h \
    application.h \
    file.h \
    standartfile.h \
    backupfile.h \
    valuefile.h \
    lrecordfile.h \
    crecordfile.h \
    stdbackupwidget.h \
    valuewidget.h \
    lcrecordwidget.h
FORMS += mainwindow.ui \
    dialog.ui \
    dialog.ui \
    key.ui \
    application.ui \
    file.ui \
    stdbackupwidget.ui \
    valuewidget.ui \
    lcrecordwidget.ui


unix:!macx:!symbian: LIBS += -lfreefare -lnfc
