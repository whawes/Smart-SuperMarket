#include "caisse.h"
#include <QSqlQuery>
#include "connexion.h"
#include <QString>

Caisse::Caisse()
{
        ID=0;
        Nom="";
        Prenom="";
        CIN=0;
        Telephone=0;
        Fonction="";
        MotDePasse="";
}

Caisse::Caisse(int id, QString nom, QString prenom, int cin, int telephone, QString fonction, QString motdepasse)
{
        ID=id;
        Nom=nom;
        Prenom=prenom;
        CIN=cin;
        Telephone=telephone;
        Fonction=fonction;
        MotDePasse=motdepasse;
}

int Caisse::getID()
{
    return ID;
}

void Caisse::setID(int id)
{
    ID=id;
}

QString Caisse::getNom()
{
    return Nom;
}

void Caisse::setNom(QString nom)
{
    Nom=nom;
}

QString Caisse::getPrenom()
{
    return Prenom;
}

void Caisse::setPrenom(QString prenom)
{
    Prenom=prenom;
}

int Caisse::getCIN()
{
    return CIN;
}

void Caisse::setCIN(int cin)
{
    CIN=cin;
}

int Caisse::getTelephone()
{
    return Telephone;
}

void Caisse::setTelephone(int telephone)
{
    Telephone=telephone;
}

QString Caisse::getFonction()
{
    return Fonction;
}

QString Caisse::getMotDePasse()
{
    return MotDePasse;
}

QSqlQueryModel * Caisse::afficher(QString login, QString motdepasse)
{
    QString l=login;
    QString m=motdepasse;
    QString a="select ID,NOM,PRENOM,CIN,TELEPHONE from CAISSE WHERE (ID='";
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

bool Caisse:: ajouterCaissier()
{
    QSqlQuery query;
         query.prepare("INSERT INTO Caisse(ID,Prenom,Nom,CIN,Telephone,Fonction,MDP)Values(?,?,?,?,?,?,?)");
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
bool Caisse:: supprimerCaissier(int id)
{
    QSqlQuery query;
    query.prepare("Delete from CAISSE where Id=:id");
    query.addBindValue(id);
    return query.exec();
}
bool Caisse :: modifierCaissier()
{



        QSqlQuery query;
        query.prepare("update CAISSE set Nom='"+Nom+"',Prenom='"+Prenom+"',CIN=:CIN,Telephone=:Telephone,Fonction='"+Fonction+"',MDP='"+MotDePasse+"'  where ID=:ID");
        query.bindValue(":ID",ID);
        query.bindValue(":Prenom",Prenom);
        query.bindValue(":Nom",Nom);
        query.bindValue(":CIN",CIN);
        query.bindValue(":Telephone",Telephone);
        query.bindValue(":Fonction",Fonction);
        query.bindValue(":MDP",MotDePasse);
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
