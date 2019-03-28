#include "prodtrier.h"
#include "ui_prodtrier.h"
#include "QSqlQueryModel"

ProdTrier::ProdTrier(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProdTrier)
{
    ui->setupUi(this);
    Produit c;
    QSqlQueryModel* p=c.TriProduits();
    ui->tabletri->setModel(p);
}

ProdTrier::~ProdTrier()
{
    delete ui;
}
