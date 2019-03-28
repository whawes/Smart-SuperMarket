#include "fournisseur.h"
#include <QSqlQueryModel>
#include <QSizePolicy>
#include <QTableWidget>
Fournisseur::Fournisseur()
{
 Nom="";
 Telephone=0;
 Adresse="";
}
Fournisseur::Fournisseur(QString nom,int tel,QString ad){

    Nom=nom;
    Telephone=tel;
    Adresse=ad;
}

QString Fournisseur::getNom(){
    return Nom;
}
void Fournisseur::setNom(QString nom){
    Nom=nom;
}
int Fournisseur::getTelephone(){
    return Telephone;
}
void Fournisseur::setTelephone(int tel){
    Telephone=tel;
}
QString Fournisseur::getAdresse(){
    return Adresse;
}
void Fournisseur::setAdresse(QString ad){
    Adresse=ad;
}

bool Fournisseur::ajouter_F()
{
QSqlQuery query;

query.prepare("INSERT INTO FOURNISSEUR (NOM,TELEPHONE,ADRESSE) "
                    "VALUES (:Nom, :Telephone, :Adresse)");
query.bindValue(":Nom", Nom );
query.bindValue(":Telephone", Telephone );
query.bindValue(":Adresse", Adresse );
return query.exec();
}

QSqlQueryModel * Fournisseur::afficher_fourniseur()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from FOURNISSEUR");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("NOM"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("TELEPHONE"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("ADRESSE"));

    return model;
}

bool Fournisseur::supprimer(QString nomS)
{
QSqlQuery query;
QString res= nomS;
query.prepare("Delete from FOURNISSEUR where NOM = :Nom ");
query.bindValue(":Nom", res);
return    query.exec();
}
bool Fournisseur::Update(QString name,QString Nom, QString adresse,int tel){
    QSqlQuery query;

    QString res=name;
    query.prepare("update FOURNISSEUR set  Nom =:Nom ,ADRESSE =:Adresse,TELEPHONE =:Telephone where NOM = :name");
    query.bindValue(":name",res);

    query.bindValue(":Nom", Nom);

      query.bindValue(":Adresse", adresse);

    query.bindValue(":Telephone", tel);

    return query.exec();
}

QSqlQueryModel* Fournisseur :: rechercher(QString arg1)
{
        QSqlQueryModel *model=new QSqlQueryModel();
        model->setQuery("select * from fournisseur where Nom like '%"+arg1+"%' or adresse like '%"+arg1+"%' or telephone like '%"+arg1+"%'");
        return model;

}

