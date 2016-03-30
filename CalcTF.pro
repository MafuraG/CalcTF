#-------------------------------------------------
#
# Project created by QtCreator 2016-03-18T09:50:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CalcTF
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Polynomial.cpp \
    PolynomialRootFinder.cpp \
    tfdialog.cpp \
    transferfunction.cpp \
    controlsystem.cpp \
    errorstrings.cpp

HEADERS  += mainwindow.h \
    Polynomial.h \
    PolynomialRootFinder.h \
    tfdialog.h \
    transferfunction.h \
    controlsystem.h \
    errorstrings.h

FORMS    += mainwindow.ui \
    tfdialog.ui

RESOURCES += \
    calctfres.qrc
