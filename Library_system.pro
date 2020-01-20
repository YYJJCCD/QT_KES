#-------------------------------------------------
#
# Project created by QtCreator 2019-11-17T11:28:30
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Library_system
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    add_dialog.cpp \
    add_book.cpp \
    success.cpp \
    show_dialog.cpp \
    add_cd.cpp \
    add_picture.cpp \
    qmysqlquerymodel.cpp \
    man_dialog.cpp \
    check_dialog.cpp \
    check_del_dialog.cpp

HEADERS += \
        mainwindow.h \
    add_dialog.h \
    add_book.h \
    success.h \
    show_dialog.h \
    add_cd.h \
    add_picture.h \
    qmysqlquerymodel.h \
    man_dialog.h \
    check_dialog.h \
    check_del_dialog.h

FORMS += \
        mainwindow.ui \
    add_dialog.ui \
    add_book.ui \
    success.ui \
    show_dialog.ui \
    add_cd.ui \
    add_picture.ui \
    man_dialog.ui \
    check_dialog.ui \
    check_del_dialog.ui

RESOURCES +=








