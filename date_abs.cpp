#include "date_abs.h"
#include "ui_date_abs.h"
#include "absence.h"
date_abs::date_abs(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::date_abs)
{
    ui->setupUi(this);
}

date_abs::~date_abs()
{
    delete ui;
}

void date_abs::on_pushButton_clicked()
{
    QSqlQueryModel *modal=new QSqlQueryModel();
           QSqlQuery qry;
          QString  date=ui->e_date->text();
           qry.prepare("select *from Absence where Date_Abs='"+date+"'");
           qry.addBindValue(date);
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
