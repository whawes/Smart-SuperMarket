#ifndef COMMANDE_H
#define COMMANDE_H

#include <QString>
#include <QSqlQueryModel>

class Commande
{  private:
    int Id_Co;
    QString Date_commande;
    QString Prestataire;
    QString Produit;
    int Quantite;
    bool Etat;

public:


    Commande();
    Commande(QString date,QString presta,QString prod,int qts);
    void setId_Co(int id);
    QString getDate_commande();
    void setDate_commande(QString date);
    QString getPrestataire();
    void setPrestataire(QString presta);
    QString getProduit();
    void setProduit(QString prod);
    int getQuantite();

    void setQuantite(int qts);
    bool getEtat();
    void setEatat(bool etat);
    bool ajouter_C();
    QSqlQueryModel * afficher_C();
    bool supprimer(QString pRESTATAIRE);
    bool Update(QString pres,QString date,QString presta,QString prod,int qts);
    QSqlQueryModel* rechercher(QString arg2);
};

#endif // COMMANDE_H
