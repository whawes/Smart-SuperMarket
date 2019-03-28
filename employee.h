#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include <QString>
#include <QSqlQueryModel>

class Employee
{
protected:
    int ID;
    QString Nom;
    QString Prenom;
    int CIN;
    int Telephone;
    QString Fonction;
    QString MotDePasse;
public:
    Employee();
    Employee(int,QString,QString,int,int,QString,QString);

    int getID();
    void setID(int);

    QString getNom();
    void setNom(QString);

    QString getPrenom();
    void setPrenom(QString);

    int getCIN();
    void setCIN(int);

    int getTelephone();
    void setTelephone(int);


    QString getFonction();
    QString getMotDePasse();
    QSqlQueryModel *afficher(QString login, QString motdepasse);
    QSqlQueryModel *afficherEmploye();
    bool ajouterEmploye();
    bool supprimerEmploye(int id);
    bool modifierEmploye();
};

#endif // EMPLOYEE_H
