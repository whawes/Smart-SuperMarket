#include "afficherclient.h"
#include "ui_afficherclient.h"

AfficherClient::AfficherClient(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AfficherClient)
{
    setFixedSize(309,254);
    ui->setupUi(this);
    ui->tableView->setModel(cl.afficher());
}

AfficherClient::~AfficherClient()
{
    delete ui;
}

void AfficherClient::on_pushButton_clicked()
{
    QWidget::close();
}
