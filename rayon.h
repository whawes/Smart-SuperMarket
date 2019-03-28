#ifndef RAYON_H
#define RAYON_H
#include <QWidget>
#include "bib.h"

namespace Ui {
class Rayon;
}

class Rayon : public QWidget
{
    Q_OBJECT

public:
public:
    explicit Rayon(QWidget *parent = nullptr);
    ~Rayon();
    int getIdrayon();
    void setIdrayon(int idrayon);
    int getNbproduit();
    void setNbproduit(int nbproduit);
    double getHauteur();
    void setHauteur(double hauteur);
    double getLargeur();
    void setLargeur(double largeur);
    void Ajouter_Rayon(int Idrayon, double Hauteur, double Largeur ,int Nbproduit);
    void Modifier_Rayon(int Idrayon, double Hauteur, double Largeur ,int Nbproduit);
    void Afficher_Rayon();
    void Supprimer_Rayon();
    void Rechercher_Rayon();
    void tri_Rayon_d();
    void tri_Rayon_c();
private slots:
    void on_ajouter_2_clicked();

    void on_supprimer_clicked();

    void on_modifier_clicked();

    void on_AfficherR_itemClicked(QTableWidgetItem *item);

    void on_chercher_clicked();

    void on_tricroissant_clicked();

    void on_tridecroissant_clicked();

private:
    Ui::Rayon *ui;
    int Idrayon;
    double Hauteur;
    double Largeur;
    int Nbproduit;
    QSystemTrayIcon *mSystemTrayIcon;
};

#endif // RAYON_H
