#ifndef FACTURE_H
#define FACTURE_H

#include <QString>
#include <QSqlQueryModel>





class Facture
{ private:

    QString Date_Achat ;
    int Prix_unitaire;
    int Quantite;
    int Etat;



public:
    Facture();
    Facture(QString date,int prix, int qts);



   QString getDate_Achat();
   void setDate_Achat(QString date);
   int getPrix_unitaire();
   void setPrix_unitaire(int prix);
   int getQuantite();
   void setQuantite(int qts);
   int getEtat();
   void setEtat(int etat);
   bool Ajouter();
   QSqlQueryModel *afficher();
   bool supprimer(QString dd);
   bool Modifier(QString dd,QString date,int prix,int qtsA);
   QSqlQueryModel* rechercher(QString arg);
   float Calculer_Total();

};

#endif // FACTURE_H
