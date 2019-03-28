#include "emplacement.h"
#include <QDebug>

Emplacement::Emplacement()
{
    Numero=0;
    Valeur=0;
    Reservtion=0;
}

Emplacement::Emplacement(int num)
{
    Numero=num;
    Valeur=0;
    Reservtion=0;
}

int Emplacement::getNumero()
{
    return Numero;
}

void Emplacement::setNumero(int num)
{
    Numero=num;
}

int Emplacement::getValeur()
{
    return Valeur;
}

void Emplacement::setValeur(int valeur)
{
    Valeur=valeur;
}

int Emplacement::getReservation()
{
    return Reservtion;
}

void Emplacement::setReservation(int reservation)
{
    Reservtion=reservation;
}

QTime Emplacement::getTempsEntree()
{
    return TempsEntree;
}

void Emplacement::setTempsEntree(QTime temps)
{
    TempsEntree=temps;
}

QTime Emplacement::getTempsReservation()
{
    return  TempsReservation;
}

void Emplacement::setTempsReservation(QTime temps)
{
    TempsReservation=temps;
}

bool Emplacement::verifierHeure()
{
    QTime t;
    if(t.hour()-TempsEntree.hour()>4)
        return false;
    else return true;
}

QSqlQueryModel *Emplacement::afficher(int choix)
{
    QString a=QString::number(choix);
    qDebug()<<a;
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select Numero from Emplacement where Numero like '"+a+"%' and Valeur=0");
    return model;
}

bool Emplacement::ajouter()
{
    QSqlQuery query;
    QString res= QString::number(Numero);
    query.prepare("INSERT INTO EMPLACEMENT (NUMERO, VALEUR, RESERVATION, TEMPSENTREE, TEMPSRESERVATION) "
                        "VALUES (:NUMERO,:VALEUR,:RESERVATION,:TEMPSENTREE,:TEMPSRESERVATION)");
    query.bindValue(":NUMERO", res);
    query.bindValue(":VALEUR", Valeur);
    query.bindValue(":RESERVATION", Reservtion);
    query.bindValue(":TEMPSENTREE", TempsEntree);
    query.bindValue(":TEMPSRESERVATION", TempsReservation);
    return query.exec();
}

QSqlQueryModel *Emplacement::affichertotal()
{
    QSqlQueryModel *model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM EMPLACEMENT");
    return  model;
}

bool Emplacement::modifier(int Oldid, int Newid)
{
    QSqlQuery query;
    QString oldid= QString::number(Oldid);
    QString newid= QString::number(Newid);
    query.prepare("UPDATE EMPLACEMENT SET NUMERO=:NEWNUMERO WHERE NUMERO=:NUMERO");
    query.bindValue(":NUMERO",oldid);
    query.bindValue(":NEWNUMERO",newid);
    return query.exec();
}

bool Emplacement::supprimer(int id)
{
    QSqlQuery query;
    QString res= QString::number(id);
    query.prepare("Delete from EMPLACEMENT where NUMERO = :NUMERO ");
    query.bindValue(":NUMERO", res);
    return query.exec();
}

bool Emplacement::reserver(int choix, int id, Arduino A)
{
    QTime time;
    QSqlQuery query;
    QString numero= QString::number(id);
    TempsEntree=time.currentTime();
    TempsReservation=TempsEntree.addSecs(choix*3600);
    query.prepare("UPDATE EMPLACEMENT SET VALEUR=1,RESERVATION=1,TEMPSENTREE=:TEMPSENTREE,TEMPSRESERVATION=:TEMPSRESERVATION WHERE NUMERO=:NUMERO");
    query.bindValue(":NUMERO",numero);
    query.bindValue(":TEMPSENTREE",time.currentTime());
    query.bindValue(":TEMPSRESERVATION",TempsReservation);
    A.write_to_arduino("1");
    return query.exec();
}

void Emplacement::verifier(/*Arduino A,*/QByteArray data)
{
    QSqlQuery query;
    QString numero= QString::number(102);
    data=A.read_from_arduino();
    QString Data=data;
    qDebug()<<a;
    if(data=="1")
    {
        QTime time;
        TempsEntree=time.currentTime();
        query.prepare("UPDATE EMPLACEMENT SET VALEUR=1,RESERVATION=0,TEMPSENTREE=:TEMPSENTREE WHERE NUMERO=:NUMERO");
        query.bindValue(":NUMERO",numero);
        query.bindValue(":TEMPSENTREE",time.currentTime());
    }
    else if (data=="0")
    {
        query.prepare("UPDATE EMPLACEMENT SET VALEUR=0,RESERVATION=0 WHERE NUMERO=:NUMERO");
        query.bindValue(":NUMERO",numero);
    query.exec();
}

void Emplacement::reset()
{
    QTime time;
    QSqlQuery query;
    QSqlQuery qry;
    query.exec("select * from emplacement");
    while (query.next())
    {
        if(query.value(4)<time.currentTime())
        {
            QTime t;
            QVariant q=query.value(0);
            qry.prepare("UPDATE EMPLACEMENT SET VALEUR=0,RESERVATION=0,TEMPSENTREE=:temps,TEMPSRESERVATION=:temps WHERE NUMERO=:NUMERO");
            qry.bindValue(":NUMERO",q);
            qry.bindValue(":temps",t);
            qry.exec();
        }
    }
}
