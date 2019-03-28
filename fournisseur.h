#ifndef FOURNISSEUR_H
#define FOURNISSEUR_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QTableWidget>

class Fournisseur
{ private:
    int Id_Fournisseur;
    QString Nom;
    int Telephone;
    QString Adresse;
public:
    Fournisseur();
    Fournisseur(QString nom,int tel,QString ad);
    void setId_Fournisseur(int id);
    QString getNom();
    void setNom(QString nom);
    int getTelephone();
    void setTelephone(int tel);
    QString getAdresse();
    void setAdresse(QString ad);
    bool ajouter_F();
    QSqlQueryModel *afficher_fourniseur();
    bool supprimer(QString nomS);
    bool Update(QString name,QString Nom,QString Adresse,int Telephone);
    QSqlQueryModel * afficher(QString login, QString motdepasse);
    QSqlQueryModel* rechercher(QString arg1);
};


#endif // FOURNISSEUR_H
