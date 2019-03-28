#include "commande.h"
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

Commande::Commande()
{
   Date_commande="";
     Prestataire="";
    Produit="";
    Quantite=0;
    Etat=false;

}
Commande::Commande(QString date,QString presta,QString prod,int qts){

    Date_commande=date;
   Prestataire=presta;
   Produit=prod;
   Quantite=qts;

}

QString Commande::getDate_commande(){
    return Date_commande;
}
void Commande::setDate_commande(QString date){
    Date_commande=date;
}
QString Commande::getPrestataire(){
    return Prestataire;
}
void Commande::setPrestataire(QString presta){
    Prestataire=presta;
}
QString Commande::getProduit(){
    return Produit;
}
void Commande::setProduit(QString prod){
    Produit=prod;
}
int Commande::getQuantite(){
    return Quantite;
}
void Commande::setQuantite(int qts){
    Quantite=qts;
}
bool Commande::ajouter_C()
{
QSqlQuery query;


//int Id_Co=model->rowCount()+1;
query.prepare("INSERT INTO COMMANDE(DATE_COMMANDE,PRESTATAIRE,PRODUIT,QUANTITE) "
                    "VALUES (:Date_commande, :Prestataire, :Produit, :Quantite)");
query.bindValue(":Date_commande", Date_commande );
query.bindValue(":Prestataire", Prestataire );
query.bindValue(":Produit", Produit );
query.bindValue(":Quantite", Quantite );

return    query.exec();
}
QSqlQueryModel * Commande::afficher_C()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from COMMANDE");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("DATE_COMMANDE"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("PRESTATAIRE"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRODUIT"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("QUANTITE"));

    return model;
}

bool Commande::supprimer(QString pRESTATAIRE)
{
QSqlQuery query;
QString res= pRESTATAIRE;
query.prepare("Delete from COMMANDE where PRESTATAIRE = :Prestataire ");
query.bindValue(":Prestataire", res);
return    query.exec();
}
bool Commande::Update(QString pres,QString date,QString presta,QString prod,int qts){
    QSqlQuery query;
    QString res=pres;

    query.prepare("update COMMANDE set DATE_COMMANDE =:date, PRESTATAIRE =:presta, PRODUIT =:prod, QUANTITE =:qts where PRESTATAIRE = :pres");
    query.bindValue(":pres",res);



    query.bindValue(":date", date);

      query.bindValue(":presta", presta);
    query.bindValue(":prod", prod);
    query.bindValue(":qts", qts);

    return query.exec();
}
QSqlQueryModel* Commande :: rechercher(QString arg2)
{
        QSqlQueryModel *model=new QSqlQueryModel();
        model->setQuery("select * from Commande where Date_Commande like '%"+arg2+"%' or Prestataire like '%"+arg2+"%' or Produit like '%"+arg2+"%' or Quantite like '%"+arg2+"%'");
        return model;

}
