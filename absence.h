#ifndef ABSENCE_H
#define ABSENCE_H
#include <QString>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QMessageBox>
#include <QtSql/QSqlQueryModel>
class Absence
{
private:
    QString Date_Abs;
    int ID_Employe;
public:
    Absence();
    Absence(QString date,int id);
    int getID_Employe();
    QString getDate();
    void setID_Employe(int id);
    void setDate(QString date);
    bool ajouterAbsence();
    bool supprimerAbsence(int id);
    bool modifierAbsence();
    QSqlQueryModel * afficherAbsence();
};

#endif // ABSENCE_H
