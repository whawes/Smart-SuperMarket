#ifndef ADMIN_H
#define ADMIN_H
#include "employee.h"
#include <QString>
#include <QSqlQueryModel>
#include <QDebug>
class Admin:public Employee
{
private:
    QString Autorite;
public:
    Admin();
    Admin(int id,QString nom,QString prenom,int cin,int telephone,QString fonction,QString motDePasse,QString autorite);
    QString getAutorite();
    void setAutorite(QString);
    bool ajouterEmploye();
    bool supprimerEmploye(int id);
    QSqlQueryModel *afficherEmploye();
    bool modifierEmploye();

};

#endif // ADMIN_H
