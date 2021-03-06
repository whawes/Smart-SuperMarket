#ifndef EMPLACEMENT_H
#define EMPLACEMENT_H
#include <windows.h>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QDate>
#include "arduino.h"

class Emplacement
{
private:
    int Numero;
    int Valeur;
    int Reservtion;    
    QTime TempsEntree;
    QTime TempsReservation;
public:
    Emplacement();
    Emplacement(int);

    int getNumero();
    void setNumero(int);

    int getValeur();
    void setValeur(int);

    int getReservation();
    void setReservation(int);

    QTime getTempsEntree();
    void setTempsEntree(QTime);

    QTime getTempsReservation();
    void setTempsReservation(QTime);

    bool verifierHeure();
    bool ajouter();
    bool modifier(int,int);
    bool supprimer(int);
    QSqlQueryModel *afficher(int);
    QSqlQueryModel *affichertotal();
    void verifier(/*Arduino,*/QByteArray);
    bool reserver(int,int,Arduino);
    void reset();
};

#endif // EMPLACEMENT_H
