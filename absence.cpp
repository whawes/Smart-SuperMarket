#include "absence.h"

Absence::Absence()
{
    Date_Abs="";
    ID_Employe=0;
}
Absence::Absence(QString date,int id)
{
    this->ID_Employe=id;
    this->Date_Abs=date;
}
int Absence::getID_Employe()
{
    return ID_Employe;
}
QString Absence::getDate()
{
    return Date_Abs;
}
void Absence::setID_Employe(int id)
{
    ID_Employe=id;
}
void Absence::setDate(QString date)
{
    Date_Abs=date;
}
bool Absence:: ajouterAbsence()
{
    QSqlQuery query;
         query.prepare("INSERT INTO Absence(Date_Abs,ID_Employe)Values(?,?)");
         query.addBindValue(Date_Abs);
         query.addBindValue(ID_Employe);
         if(query.exec())
             return true;
         else
             return false;
}
bool Absence:: supprimerAbsence(int id)
{
    QSqlQuery query;
    query.prepare("Delete from Absence where ID_Employe=:id");
    query.addBindValue(id);
    return query.exec();
}
bool  Absence :: modifierAbsence()
{
        QSqlQuery query;
        query.prepare("update Absence set Date_Abs='"+Date_Abs+"' where ID_Employe=:ID_Employe");
        query.bindValue(":Date_Abs",Date_Abs);
        query.bindValue(":ID_Employe",ID_Employe);
        if(query.exec())
            return true;
        else
            return false;
}
QSqlQueryModel * Absence :: afficherAbsence()
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from Absence");

        return model;
}
