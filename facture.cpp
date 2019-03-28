#include "facture.h"
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

Facture::Facture()
{

Date_Achat="";
Prix_unitaire=0;
Quantite=0;

}
Facture::Facture(QString date,int prix, int qts){

    Date_Achat=date;
    Prix_unitaire=prix;
    Quantite=qts;
}

QString Facture::getDate_Achat(){
    return Date_Achat;
}
void Facture::setDate_Achat(QString date){
    Date_Achat=date;
}
int Facture::getPrix_unitaire(){
    return Prix_unitaire;
}
void Facture::setPrix_unitaire(int prix){
    Prix_unitaire=prix;
}
int Facture::getQuantite(){
    return Quantite;
}
void Facture::setQuantite(int qts){
    Quantite=qts;
}
int Facture::getEtat(){
    return Etat;
}
void Facture::setEtat(int etat){
    Etat=etat;
}

bool Facture::Ajouter()
{
QSqlQuery query;

query.prepare("INSERT INTO FACTURE (DATE_ACHAT, PRIX_UNITAIRE, QUANTITE) "
                    "VALUES (:Date_Achat, :Prix_unitaire, :Quantite)");
query.bindValue(":Date_Achat", Date_Achat);
query.bindValue(":Prix_unitaire", Prix_unitaire);
query.bindValue(":Quantite", Quantite);

return    query.exec();
}

QSqlQueryModel * Facture::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from FACTURE");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("DATE_ACHAT"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("PRIX_UNITAIRE"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("QUANTITE"));
    return model;
}

bool Facture::supprimer(QString dd)
{
QSqlQuery query;
QString res = dd;
query.prepare("Delete from FACTURE where DATE_ACHAT = :Date_Achat ");
query.bindValue(":Date_Achat", res);
return    query.exec();
}

bool Facture::Modifier(QString dd,QString date,int prix,int qtsA)
{
    QSqlQuery query;
    QString  res= dd;

    query.prepare("update FACTURE set DATE_ACHAT =:date, PRIX_UNITAIRE =:PRIX_UNITAIRE, QUANTITE =:Quantite where DATE_ACHAT = :dd");
    query.bindValue(":dd",res);



    query.bindValue(":date", date);




    query.bindValue(":PRIX_UNITAIRE", prix);
    query.bindValue(":Quantite", qtsA);

    return query.exec();
}
QSqlQueryModel* Facture :: rechercher(QString arg)
{
        QSqlQueryModel *model=new QSqlQueryModel();
        model->setQuery("select * from Facture where Date_Achat like '%"+arg+"%' or Prix_Unitaire like '%"+arg+"%' or QUantite like '%"+arg+"%'");
        return model;

}
