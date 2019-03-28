#ifndef PAN_H
#define PAN_H



#include <QString>
#include<QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlQuery>
#include <QtSql/QSqlQueryModel>
#include <QString>
#include "produits.h"
#include<vector>
class Pan
{
private:
    QString Num_Panier;
    QString Addition;
    QString Total_Poids;
    Produits *tab;
    QString Nom_Prod;
     QString Prix_Prod;
      QString Quantite_Prod;
      QString  Poids_Prod;
      QString Id_Prod;


public:
    Pan();
    Pan(QString id_prod,QString quantite_prod);
    Pan(QString num_panier,QString addition,QString total_poids,QString prix_prod,QString poids_prod,QString quantite_prod,QString id_prod,QString nom_prod);
   // Pan(QString num_panier,QString addition,QString total_poids,QString nom_prod,QString prix_prod,QString quantite_prod,QString poids_prod,QString id_prod);
    Pan(QString nom_prod,QString prix_prod,QString quantite_prod,QString poids_prod,QString id_prod);
    ~Pan();

   QString getNum_Panier();
    void setNum_Panier(QString num_panier);


    QString getAddition();
     void setAddition(QString addition);


     QString getTotal_Poids();
      void setTotal_Poids(QString total_poids);

      QString getNom_Prod();
       void setNom_Prod(QString nom_prod);


       QString getPrix_Prod();
        void setPrix_Prod(QString prix_prod);


        QString getQuantite_Prod();
         void setQuantite_Prod(QString quantite_prod);


         QString getId_Prod();
          void setId_Prod(QString id_prod);

          QString getPoids_Prod();
          void setPoids_Prod(QString poids_prod);



      QSqlQueryModel * afficher();
      bool ajouter_Panier();
      bool supprimerPannier(QString id);
      bool modifierPanier();
      bool Verfier(QString id);
      int Somme_Poids();
      int Somme_Prix();






};




#endif // PAN_H
