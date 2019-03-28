#include "ajoutcaissier.h"
#include "ui_ajoutcaissier.h"


AjoutCaissier::AjoutCaissier(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AjoutCaissier)
{
    ui->setupUi(this);
    mSystemTrayIcon = new QSystemTrayIcon(this);
        mSystemTrayIcon->setIcon(QIcon(":/myappico.png"));
        mSystemTrayIcon->setVisible(true);

}

AjoutCaissier::~AjoutCaissier()
{
    delete ui;
}

void AjoutCaissier::on_pushButton_clicked()
{

    int id = ui->e_id_2->text().toInt();
    QString prenom = ui->e_pre->text();
    QString nom = ui->e_nom_3->text();
    QString fonction = ui->e_fce->text();
    int telephone = ui->e_tel->text().toInt();
    QString mdp = ui->e_mdp_3->text();
    int cin = ui->e_cin_3->text().toInt();
   // Caisse e(id,prenom,nom,cin,telephone,fonction,mdp);
    Caisse e(id,prenom,nom,cin,telephone,fonction,mdp);
    if(e.ajouterCaissier())
    {
    mSystemTrayIcon->showMessage(tr("Caissier ajouté "),
                                          tr("Nouveau Caissier à ajouter"));
    }
}
