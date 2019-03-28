#include "modifiercaissier.h"
#include "ui_modifiercaissier.h"
#include "caisse.h"

ModifierCaissier::ModifierCaissier(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModifierCaissier)
{
    ui->setupUi(this);
    mSystemTrayIcon = new QSystemTrayIcon(this);
        mSystemTrayIcon->setIcon(QIcon(":/myappico.png"));
        mSystemTrayIcon->setVisible(true);
}

ModifierCaissier::~ModifierCaissier()
{
    delete ui;
}

void ModifierCaissier::on_pushButton_clicked()
{
    int id = ui->e_id_2->text().toInt();
    QString prenom = ui->e_pre->text();
    QString nom = ui->e_nom_7->text();
    QString fonction = ui->e_fce->text();
    int telephone = ui->e_tel->text().toInt();
    QString mdp = ui->e_mdp_3->text();
    int cin = ui->e_cin_3->text().toInt();
    Caisse e(id,prenom,nom,cin,telephone,fonction,mdp);
    if (e.modifierCaissier())
    {
        mSystemTrayIcon->showMessage(tr("Caissier a modifié "),
                                              tr("Nouveau Caissier à modifier"));
    }
}
