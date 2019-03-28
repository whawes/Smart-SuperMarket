#include "admin.h"
#include <QSqlQuery>
Admin::Admin(): Employee()
{
    Autorite="";
}
Admin::Admin(int id,QString nom,QString prenom,int cin,int telephone,QString fonction,QString motDePasse,QString autorite):Employee( id,nom,prenom,cin,telephone,fonction,motDePasse)
{
    Autorite=autorite;
}

bool Admin:: ajouterEmploye()
{
    QSqlQuery query;
         query.prepare("INSERT INTO Admin(ID,Prenom,Nom,CIN,Telephone,Fonction,MotDePasse,AUTORITE)Values(?,?,?,?,?,?,?,?)");
         query.addBindValue(ID);
         query.addBindValue(Prenom);
         query.addBindValue(Nom);
         query.addBindValue(CIN);
         query.addBindValue(Telephone);
         query.addBindValue(Fonction);
         query.addBindValue(MotDePasse);
         query.addBindValue(Autorite);
         if(query.exec())
             return true;
         else
             return false;
}
bool Admin:: supprimerEmploye(int id)
{
    QSqlQuery query;
    query.prepare("Delete from Admin where Id=:id");
    query.addBindValue(id);
    return query.exec();
}
bool Admin :: modifierEmploye()
{



        QSqlQuery query;
        query.prepare("update Admin set Nom='"+Nom+"',Prenom='"+Prenom+"',CIN=:CIN,Telephone=:Telephone,Fonction='"+Fonction+"',MDP='"+MotDePasse+"' ,Autorite='"+Autorite+"'  where ID=:ID");
        query.bindValue(":ID",ID);
        query.bindValue(":Prenom",Prenom);
        query.bindValue(":Nom",Nom);
        query.bindValue(":CIN",CIN);
        query.bindValue(":Telephone",Telephone);
        query.bindValue(":Fonction",Fonction);
        query.bindValue(":MDP",MotDePasse);
        query.bindValue(":Autorite",Autorite);
        if(!query.exec())
        {
                //QMessageBox::critical(this,tr("Connection Lost"),tr("Failed to connect to the database"));
            return true;
        }
        else
        {
           // QMessageBox::information(this,tr("Successful"),tr("Personne a été modifiée "));
             return false;
         }
}
QSqlQueryModel * Admin :: afficherEmploye()
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from Admin");

        return model;
}
