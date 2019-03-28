#ifndef NOTIFICATION_H
#define NOTIFICATION_H
#include <QSystemTrayIcon>
#include "commande.h"
#include "facture.h"
#include "fournisseur.h"

class Notification
{
private:
    bool Etat;
    bool Testing;
    QSystemTrayIcon *mSystemTrayIcon;
public:
    Notification();
    bool getEtat();

    bool getTesting();
    void aff_Notif();

};

#endif // NOTIFICATION_H
