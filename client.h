#ifndef CLIENT_H
#define CLIENT_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <string.h>

class Client
{
private:
    int CIN;
public:
    Client();
    Client(int);

    int getCIN();

    bool ajouter();
    QSqlQueryModel *afficher();
    bool modifier(int,int);
    bool supprimer(int);
};


#endif // CLIENT_H
