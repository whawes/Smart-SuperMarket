#include "connexion.h"

Connexion::Connexion()
{
}

bool Connexion::ouvrirConnexion()
{
    bool test=false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("Source_Projet2A");
    db.setUserName("system");
    db.setPassword("0000");
    if(db.open())
        test=true;
    return test;
}

void Connexion::fermerConnexion()
{
    db.close();
}
