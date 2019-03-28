#include "supprimcaissier.h"
#include "ui_supprimcaissier.h"
#include "ajoutcaissier.h"
#include <QMessageBox>

SupprimCaissier::SupprimCaissier(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SupprimCaissier)
{
    ui->setupUi(this);
    mSystemTrayIcon = new QSystemTrayIcon(this);
        mSystemTrayIcon->setIcon(QIcon(":/myappico.png"));
        mSystemTrayIcon->setVisible(true);

}

SupprimCaissier::~SupprimCaissier()
{
    delete ui;
}

void SupprimCaissier::on_pushButton_clicked()
{
    int id = ui->e_id_3->text().toInt();
     bool test=Cai.supprimerCaissier(id);
     if(test==true)
     {
         mSystemTrayIcon->showMessage(tr("Employe supprimé "),
                                               tr("Nouvelle Facture à supprimer"));

     }
     else
         QMessageBox::critical(nullptr, QObject::tr("Supprimer un employe"),
                     QObject::tr("Erreur !.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);
}
