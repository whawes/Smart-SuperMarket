#ifndef PRODUITS_H
#define PRODUITS_H
#include <QString>
#include<QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlQuery>
#include <QtSql/QSqlQueryModel>

class Produits
{
private:

    QString Id_Prod;
    QString Nom_Prod;
    QString Prix_Prod;
    QString Quantite_Prod;
    QString Poids_Prod;


public:
    Produits();
    Produits(QString id_prod,QString nom_prod,QString prix_prod,QString quantite_prod,QString poids_prod);
    Produits(QString id_prod,QString nom_prod,QString prix_prod,QString poids_prod);
    ~Produits();

    QString getId_Prod();
    void setId_Prod(QString id_prod);


    QString getNom_Prod();
    void setNom_prod(QString nom_prod);

    QString getPrix_Prod();
    void setPrix_Prod(QString prix_prod);

    QString getQuantite_Prod();
    void setQuantite_Prod(QString quantite_prod);

    QString getPoids_Prod();
    void setPoids_Prod(QString poids_prod);

    bool ajouter_Prod();
    QSqlQueryModel * afficher();
    bool supprimer(QString);
    QSqlQueryModel*  TriProduits();

};

#endif // PRODUITS_H
