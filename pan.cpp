#include "pan.h"
#include "ui_pan.h"
#include <QSqlQuery>
#include "connexion.h"
//#include "espacecaissier.h"
#include <QMessageBox>
#include<QtSql/QSqlQueryModel>
#include<QDebug>
#include <QSqlRecord>




Pan::Pan()
{
    Num_Panier="";
    Addition="";
    Total_Poids="";
    Id_Prod="";
    Nom_Prod="";
    Prix_Prod="";
    Quantite_Prod="";
    Poids_Prod="";

}


Pan::Pan(QString num_panier,QString addition,QString total_poids,QString prix_prod,QString poids_prod,QString quantite_prod,QString id_prod,QString nom_prod)
{

  Num_Panier=num_panier;
  Addition=addition;
  Total_Poids=total_poids;
  Id_Prod=id_prod;
  Nom_Prod=nom_prod;
  Prix_Prod=prix_prod;
  Quantite_Prod=quantite_prod;
  Poids_Prod=poids_prod;

}
//p(vprods[row].getNom_Prod(),vprods[row].getPrix_Prod(),"1",vprods[row].getPoids_Prod(),vprods[row].getId_Prod()
Pan::Pan(QString nom_prod,QString prix_prod,QString quantite_prod,QString poids_prod,QString id_prod)
{
    Id_Prod=id_prod;
    Nom_Prod=nom_prod;
    Prix_Prod=prix_prod;
    Quantite_Prod=quantite_prod;
    Poids_Prod=poids_prod;
}
Pan::Pan(QString id_prod,QString quantite_prod)
{
  Id_Prod=id_prod;
  Quantite_Prod=quantite_prod;
}

Pan::~Pan()
{}

QString Pan::getNum_Panier()
{
    return Num_Panier;
}
void Pan::setNum_Panier(QString num_panier)
{
    Num_Panier=num_panier;
}

QString Pan::getQuantite_Prod()
{
    return Quantite_Prod;
}
 void Pan::setQuantite_Prod(QString quantite_prod)
 {
     Quantite_Prod=quantite_prod;
 }

QString Pan::getAddition()
{
    return Addition;
}
void Pan::setAddition(QString addition)
{
    Addition=addition;
}


QString Pan::getNom_Prod()
{
    return Nom_Prod;
}
void Pan::setNom_Prod(QString nom_prod)
{
    Nom_Prod=nom_prod;
}


QString Pan::getPrix_Prod()
{
    return Prix_Prod;
}
void Pan::setPrix_Prod(QString prix_prod)
{
    Prix_Prod=prix_prod;
}


QString Pan::getPoids_Prod()
{
    return Poids_Prod;
}
void Pan::setPoids_Prod(QString poids_prod)
{
    Poids_Prod=poids_prod;
}



QString Pan::getTotal_Poids()
{
    return Total_Poids;
}
void Pan::setTotal_Poids(QString total_poids)
{
    Total_Poids=total_poids;
}
QString Pan::getId_Prod()
{
    return Id_Prod;
}
void Pan::setId_Prod(QString id_Prod)
{
    Id_Prod=id_Prod;
}


/*bool Produits:: ajouter_Produit()
{
    QSqlQuery query;
         query.prepare("INSERT INTO Pan(ID_Produit,Prix_Produit,Nom_Produit,Poids_Produit)Values(?,?,?,?)");
         query.addBindValue(ID_Produit);
         query.addBindValue(Prix_Produit);
         query.addBindValue(Nom_Produit);
         query.addBindValue(Poids_Produit);
         if(query.exec())
             return true;
         else
             return false;
}
*/

bool Pan::ajouter_Panier()
{
    QSqlQuery query;
       query.prepare("INSERT INTO Pan (nom_produit , prix_produit , quantite_produit , poids_produit,id_produit) Values(?,?, ?,?,? )");
  //p(vprods[row].getNom_Prod(),vprods[row].getPrix_Prod(),"1",vprods[row].getPoids_Prod(),vprods[row].getId_Prod()

       query.addBindValue( Nom_Prod);
       query.addBindValue(Prix_Prod);
       query.addBindValue( Quantite_Prod);
       query.addBindValue(Poids_Prod);
       query.addBindValue(Id_Prod);


       if(query.exec())
           return  true;
       return  false;



}

bool Pan:: supprimerPannier(QString id)
{
    QSqlQuery query;
       query.prepare("Delete from Pan where id_produit=:id");
       query.addBindValue(id);
       return query.exec();
}




bool Pan::modifierPanier()
{
    QSqlQuery qry;
           qry.prepare("update Pan set Quantite_produit='"+Quantite_Prod+"' where Id_produit='"+Id_Prod+"' ");


           if(qry.exec())
           {
               //QMessageBox::information(this,tr("Successful"),tr("Poubelle ajoutée avec succés ??"));
              return true;
           }
           else
           {
               //QMessageBox::critical(this,tr("Failed"),tr("L'operation d'ajout est échouée ??"));
               return false;
           }
}

bool Pan::Verfier(QString id)
{
    QSqlQuery qry;
    qry.exec("select * from Pan");
    while(qry.next())
    {

        qDebug()<<qry.value(7);
       if(id==qry.value(7).toString())
       {
       return  true;
       }
     }
    return  false;
}
int Pan::Somme_Poids()
{

    int  s=0;
    QSqlQueryModel *qry=new QSqlQueryModel();
    qry->setQuery("select * from Pan");
    for(int i=0;i<qry->rowCount();i++)
    {
        s+=qry->record(i).value("POIDS_PRODUIT").toInt();

    }

     qDebug()<<s;
    return  s;

}

int Pan::Somme_Prix()
{
    int somme=0;
    QSqlQueryModel *qry=new QSqlQueryModel();
    qry->setQuery("select * from Pan");
    for(int i=0;i<qry->rowCount();i++)
    {
        somme+=qry->record(i).value("PRIX_PRODUIT").toInt();
    }
    qDebug()<<somme;

    return somme;
}

