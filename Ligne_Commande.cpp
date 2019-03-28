#include "Ligne_commande.h"
#include "mainwindow.h"

Notification::Notification()
{
Etat=false;
Testing=false;
mSystemTrayIcon = new QSystemTrayIcon();
}
bool Notification::getEtat(){
    return Etat;
}
bool Notification::getTesting(){
    return Testing;
}



