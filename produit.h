#ifndef PRODUIT_H
#define PRODUIT_H

#include <QWidget>
#include "bib.h"
#include <QSqlQueryModel>

namespace Ui {
class Produit;
}

class Produit : public QWidget
{
    Q_OBJECT

public:
    explicit Produit(QWidget *parent = nullptr);
    ~Produit();
    int getNumero();
    void setNumero(int numero);
    int getQuantite();
    void setQuantite(int quantite);
    double getPrix();
    void setPrix(double prix);
    double getPoids();
    void setPoids(double poids);
    QString getNom();
    void setNom(QString nom);
    QString getMarque();
    void setMarque(QString marque);
    QString getType();
    void setType(QString type);
    QString getLocalisation();
    void setLocalisation(QString localisation);
    void Ajouter_Produit(int Numero,int Quantite ,double Prix,double Poids ,QString Nom,QString Marque,QString Type ,QString Localisation);
    void Modifier_Produit(int Numero,int Quantite ,double Prix,double Poids ,QString Nom,QString Marque,QString Type ,QString Localisation);
    void Afficher_Produit();
    void Supprimer_Produit();
    void Rechercher_Produit();
    void tri_Produit_d();
    void tri_Produit_c();
    QSqlQueryModel*  TriProduits();

private slots:

    void on_ajouter_2_clicked();

    void on_supprimer_clicked();

    void on_AfficherP_itemClicked(QTableWidgetItem *i);

    void on_modifier_clicked();

    void on_chercher_clicked();

    void on_tricroissant_clicked();

    void on_tridecroissant_clicked();

private:
    Ui::Produit *ui;
    int Numero;
    int Quantite;
    double Prix;
    double Poids;
    QString Nom;
    QString Marque;
    QString Type;
    QString Localisation;
    QSystemTrayIcon *mSystemTrayIcon;
};

#endif // PRODUIT_H
