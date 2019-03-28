#include "consultercaissier.h"
#include "ui_consultercaissier.h"
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QMessageBox>
#include "connexion.h"

ConsulterCaissier::ConsulterCaissier(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConsulterCaissier)
{
    ui->setupUi(this);
}

ConsulterCaissier::~ConsulterCaissier()
{
    delete ui;
}

void ConsulterCaissier::on_pushButton_clicked()
{
    QSqlQueryModel *modal=new QSqlQueryModel();
           QSqlQuery qry;
          int id=ui->lineEdit_18->text().toInt();
           qry.prepare("select *from CAISSE  where ID=:id ");
           qry.addBindValue(id);
           if(qry.exec())
           {
               modal->setQuery(qry);
             ui->tableView->setModel(modal);
           }
           else
           {
               QMessageBox::critical(nullptr, QObject::tr("critical error"),
               QObject::tr("ERROR            "
                           "VERIFIER VOTRE PARAMETRE !!."), QMessageBox::Cancel);
           }
}
