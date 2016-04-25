#-------------------------------------------------
#
# Project created by QtCreator 2016-03-18T09:50:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

QT += webenginewidgets webchannel

TARGET = CalcTF
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Polynomial.cpp \
    PolynomialRootFinder.cpp \
    tfdialog.cpp \
    transferfunction.cpp \
    controlsystem.cpp \
    errorstrings.cpp \
    outputdialog.cpp \
    root.cpp \
    roottablemodel.cpp \
    jshelper.cpp \
    plotdialog.cpp \
    qcustomplot.cpp \
    customgraph.cpp \
    rootlocusgraph.cpp \
    rootlocus.cpp

HEADERS  += mainwindow.h \
    Polynomial.h \
    PolynomialRootFinder.h \
    tfdialog.h \
    transferfunction.h \
    controlsystem.h \
    errorstrings.h \
    outputdialog.h \
    root.h \
    roottablemodel.h \
    jshelper.h \
    plotdialog.h \
    qcustomplot.h \
    customgraph.h \
    rootlocusgraph.h \
    rootlocus.h

FORMS    += mainwindow.ui \
    tfdialog.ui \
    outputdialog.ui \
    plotdialog.ui

RESOURCES += \
    calctfres.qrc

DISTFILES += \
    screen.html
