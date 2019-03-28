#ifndef CAISSE_H
#define CAISSE_H
#include <QString>
#include <QSqlQueryModel>

class Caisse
{
private:
        int ID;
        QString Nom;
        QString Prenom;
        int CIN;
        int Telephone;
        QString Fonction;
        QString MotDePasse;

public:
    Caisse();
    Caisse (int,QString,QString,int,int,QString,QString);
    //~Caisse();
        int getID();
        void setID(int);

        QString getNom();
        void setNom(QString);

        QString getPrenom();
        void setPrenom(QString);

        int getCIN();
        void setCIN(int);

        int getTelephone();
        void setTelephone(int);


        QString getFonction();
        QString getMotDePasse();
        QSqlQueryModel *afficher(QString login, QString motdepasse);
        void afficherCaissier(int id);
        bool ajouterCaissier();
        bool supprimerCaissier(int id);
        bool modifierCaissier();

};

#endif // CAISSE_H
