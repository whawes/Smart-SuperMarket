#include "produits.h"
#include "QString"
#include <QSqlQuery>
#include "connexion.h"

Produits::Produits()
{
    Id_Prod="";
    Nom_Prod="";
    Prix_Prod="";
    Quantite_Prod="";
    Poids_Prod="";

}

Produits::Produits(QString id_prod,QString nom_prod,QString prix_prod,QString quantite_prod,QString poids_prod)
{
    Id_Prod=id_prod;
    Nom_Prod=nom_prod;
    Prix_Prod=prix_prod;
    Quantite_Prod=quantite_prod;
    Poids_Prod=poids_prod;
}

Produits::Produits(QString id_prod,QString nom_prod,QString prix_prod,QString poids_prod)
{
    Id_Prod=id_prod;
    Nom_Prod=nom_prod;
    Prix_Prod=prix_prod;

    Poids_Prod=poids_prod;
}


Produits::~Produits()
{}

QString Produits::getId_Prod()
{
    return Id_Prod;
}
void Produits::setId_Prod(QString id_prod)
{
    Id_Prod=id_prod;
}



QString Produits::getNom_Prod()
{
    return Nom_Prod;
}
void Produits::setNom_prod(QString nom_prod)
{
    Nom_Prod=nom_prod;
}

QString Produits::getPrix_Prod()
{
    return Prix_Prod;
}
void Produits::setPrix_Prod(QString prix_prod)
{
    Prix_Prod=prix_prod;
}

QString Produits::getQuantite_Prod()
{
    return Quantite_Prod;
}
void Produits::setQuantite_Prod(QString quantite_prod)
{
    Quantite_Prod=quantite_prod;
}

QString Produits::getPoids_Prod()
{
    return Poids_Prod;
}
void Produits::setPoids_Prod(QString poids_prod)
{
    Poids_Prod=poids_prod;
}

bool Produits::ajouter_Prod()
{
    QSqlQuery query;
       //query.prepare("INSERT INTO Produits (nom_prod , prix_prod , quantite_prod , poids_prod) Values(?,?, ?,? )");

       query.addBindValue( Nom_Prod);
       query.addBindValue(Prix_Prod);
       query.addBindValue( Quantite_Prod);
       query.addBindValue(Poids_Prod);


       if(query.exec())
           return  true;
       return  false;

}
bool Produits::supprimer(QString nom)
{
    QSqlQuery query;
    query.prepare("Delete from Produits where NOM_PRODUIT=:nom");
    query.addBindValue(nom);
    return query.exec();

}


QSqlQueryModel*  Produits::TriProduits()
{
        QSqlQueryModel* model =new QSqlQueryModel();
         QSqlQuery  *q  = new QSqlQuery();
         q->prepare("SELECT * FROM Produits order by Prix_produit asc");
         q->exec();
         model->setQuery(*q);
         return model ;
}
