#-------------------------------------------------
#
# Project created by QtCreator 2018-11-04T17:12:32
#
#-------------------------------------------------

QT       += core gui
QT += sql printsupport
QT +=serialport
QT +=core gui serialport


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = caissier
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
    connexion.cpp \
    mainwindow.cpp \
    authentificationcaissier.cpp \
    espacecaissier.cpp \
    caisse.cpp \
    produits.cpp \
    authentificationclient.cpp \
    espaceclient.cpp \
    pan.cpp \
    consulterpanier.cpp \
    verifachat.cpp \
    prodtrier.cpp \
    arduino.cpp \
    ajoutcaissier.cpp \
    espacecrud.cpp \
    modifiercaissier.cpp \
    supprimcaissier.cpp \
    consultercaissier.cpp

HEADERS += \
    connexion.h \
    mainwindow.h \
    authentificationcaissier.h \
    espacecaissier.h \
    caisse.h \
    produits.h \
    authentificationclient.h \
    espaceclient.h \
    pan.h \
    consulterpanier.h \
    verifachat.h \
    prodtrier.h \
    arduino.h \
    ajoutcaissier.h \
    espacecrud.h \
    modifiercaissier.h \
    supprimcaissier.h \
    consultercaissier.h

FORMS += \
    mainwindow.ui \
    authentificationcaissier.ui \
    espacecaissier.ui \
    authentificationclient.ui \
    espaceclient.ui \
    pan.ui \
    consulterpanier.ui \
    verifachat.ui \
    prodtrier.ui \
    ajoutcaissier.ui \
    espacecrud.ui \
    modifiercaissier.ui \
    supprimcaissier.ui \
    consultercaissier.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
