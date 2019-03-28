#-------------------------------------------------
#
# Project created by QtCreator 2018-11-14T18:18:25
#
#-------------------------------------------------

QT       += core gui sql network multimedia printsupport serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Projet
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
    help.cpp \
    start.cpp \
    client.cpp \
    employee.cpp \
    connexion.cpp \
    afficherclient.cpp \
    emplacement.cpp \
    afficheremplacement.cpp \
    commande.cpp \
    facture.cpp \
    fournisseur.cpp \
    Ligne_Commande.cpp \
    produit.cpp \
    rayon.cpp \
    smtp.cpp \
    prodtrier.cpp \
    arduino.cpp \
    absence.cpp \
    date_abs.cpp \
    ajoutcaissier.cpp \
    consultercaissier.cpp \
    modifiercaissier.cpp \
    supprimcaissier.cpp \
    caisse.cpp \
    produits.cpp \
    authentificationclient.cpp \
    pan.cpp \
    verifachat.cpp \
    admin.cpp

HEADERS += \
        mainwindow.h \
    help.h \
    start.h \
    client.h \
    employee.h \
    identification.h \
    connexion.h \
    afficherclient.h \
    emplacement.h \
    afficheremplacement.h \
    commande.h \
    facture.h \
    fournisseur.h \
    Ligne_commande.h \
    bib.h \
    produit.h \
    rayon.h \
    smtp.h \
    prodtrier.h \
    arduino.h \
    absence.h \
    date_abs.h \
    ajoutcaissier.h \
    consultercaissier.h \
    modifiercaissier.h \
    supprimcaissier.h \
    caisse.h \
    produits.h \
    authentificationclient.h \
    pan.h \
    verifachat.h \
    admin.h

FORMS += \
        mainwindow.ui \
    help.ui \
    start.ui \
    afficherclient.ui \
    afficheremplacement.ui \
    produit.ui \
    rayon.ui \
    prodtrier.ui \
    date_abs.ui \
    ajoutcaissier.ui \
    consultercaissier.ui \
    modifiercaissier.ui \
    supprimcaissier.ui \
    pan.ui \
    authentificationclient.ui \
    authentificationclient.ui \
    pan.ui \
    verifachat.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

SUBDIRS += \
    caissier.pro
