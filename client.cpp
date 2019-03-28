#include "client.h"

Client::Client()
{
   CIN=0;
}

Client::Client(int cin)
{
    CIN=cin;
}

int Client::getCIN()
{
    return  CIN;
}

bool Client::ajouter()
{
    QSqlQuery query;
    QString cin= QString::number(CIN);
    query.prepare("INSERT INTO CLIENT (CIN) "
                        "VALUES (:CIN)");
    query.bindValue(":CIN",cin);
    return query.exec();
}

QSqlQueryModel *Client::afficher()
{
    QSqlQueryModel *model= new QSqlQueryModel();
    model->setQuery("select CIN from CLIENT");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
    return model;
}

bool Client::modifier(int ocin, int ncin)
{
    QSqlQuery query;
    QString oldcin= QString::number(ocin);
    QString newcin= QString::number(ncin);
    query.prepare("UPDATE CLIENT SET CIN=:CIN WHERE CIN=:CINN");
    query.bindValue(":CIN",newcin);
    query.bindValue(":CINN",oldcin);
    return query.exec();
}

bool Client::supprimer(int cin)
{
    QSqlQuery query;
    QString res= QString::number(cin);
    query.prepare("Delete from CLIENT where CIN = :CIN ");
    query.bindValue(":CIN", res);
    return query.exec();
}
