#include "employee.h"
#include <QSqlQuery>

Employee::Employee()
{
    ID=0;
    Nom="";
    Prenom="";
    CIN=0;
    Telephone=0;
    Fonction="";
    MotDePasse="";
}

Employee::Employee(int id, QString nom, QString prenom, int cin, int telephone, QString fonction, QString motdepasse)
{
    ID=id;
    Nom=nom;
    Prenom=prenom;
    CIN=cin;
    Telephone=telephone;
    Fonction=fonction;
    MotDePasse=motdepasse;
}

int Employee::getID()
{
    return ID;
}

void Employee::setID(int id)
{
    ID=id;
}

QString Employee::getNom()
{
    return Nom;
}

void Employee::setNom(QString nom)
{
    Nom=nom;
}

QString Employee::getPrenom()
{
    return Prenom;
}

void Employee::setPrenom(QString prenom)
{
    Prenom=prenom;
}

int Employee::getCIN()
{
    return CIN;
}

void Employee::setCIN(int cin)
{
    CIN=cin;
}

int Employee::getTelephone()
{
    return Telephone;
}

void Employee::setTelephone(int telephone)
{
    Telephone=telephone;
}

QString Employee::getFonction()
{
    return Fonction;
}

QString Employee::getMotDePasse()
{
    return MotDePasse;
}

QSqlQueryModel * Employee::afficher(QString login, QString motdepasse)
{
    QString l=login;
    QString m=motdepasse;
    QString a="select ID,NOM,PRENOM,CIN,TELEPHONE from EMPLOYEE WHERE (ID='";
    QString b="') AND (MOTDEPASSE='";
    QString c="')";
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery(a+l+b+m+c);
    model->setHeaderData(0, Qt::Vertical, QObject::tr("ID"));
    model->setHeaderData(0, Qt::Vertical, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Vertical, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Vertical, QObject::tr("CIN"));
    model->setHeaderData(4, Qt::Vertical, QObject::tr("TELEPHONE"));
    return model;
}

bool Employee:: ajouterEmploye()
{
    QSqlQuery query;
         query.prepare("INSERT INTO Employee(ID,nom,prenom,CIN,Telephone,Fonction,MotDePasse)Values(?,?,?,?,?,?,?)");
         query.addBindValue(ID);
         query.addBindValue(Prenom);
         query.addBindValue(Nom);
         query.addBindValue(CIN);
         query.addBindValue(Telephone);
         query.addBindValue(Fonction);
         query.addBindValue(MotDePasse);
         if(query.exec())
             return true;
         else
             return false;
}
bool Employee:: supprimerEmploye(int id)
{
    QSqlQuery query;
    query.prepare("Delete from Employee where Id=:id");
    query.addBindValue(id);
    return query.exec();
}
bool Employee :: modifierEmploye()
{



        QSqlQuery query;
        query.prepare("update employee set Nom=:Nom+,Prenom=:Prenom,CIN=:CIN,Telephone=:Telephone,Fonction=:Fonction,MotDePasse=:MotDePasse  where ID=:ID");
        query.bindValue(":ID",ID);
        query.bindValue(":Prenom",Prenom);
        query.bindValue(":Nom",Nom);
        query.bindValue(":CIN",CIN);
        query.bindValue(":Telephone",Telephone);
        query.bindValue(":Fonction",Fonction);
        query.bindValue(":MotDePasse",MotDePasse);
        if(!query.exec())
        {
                //QMessageBox::critical(this,tr("Connection Lost"),tr("Failed to connect to the database"));
            return true;
        }
        else
        {
           // QMessageBox::information(this,tr("Successful"),tr("Personne a été modifiée "));
             return false;
         }
}
QSqlQueryModel * Employee :: afficherEmploye()
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from Employee");

        return model;
}
