#-------------------------------------------------
#
# Project created by QtCreator 2017-12-13T13:55:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = prob1
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    crypt_aes.cpp \
    crypt_des.cpp \
    crypt_host.cpp

HEADERS  += mainwindow.h \
    base_chiper.h \
    crypt_aes.h \
    crypt_des.h \
    crypt_host.h

FORMS    += mainwindow.ui

LIBS += -lgcrypt
