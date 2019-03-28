#include "afficheremplacement.h"
#include "ui_afficheremplacement.h"

afficheremplacement::afficheremplacement(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::afficheremplacement)
{
    ui->setupUi(this);
    ui->tableView->setModel(em.affichertotal());
}

afficheremplacement::~afficheremplacement()
{
    delete ui;
}

void afficheremplacement::on_pushButton_clicked()
{
    QWidget::close();
}
