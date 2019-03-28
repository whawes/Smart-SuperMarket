#ifndef PRODTRIER_H
#define PRODTRIER_H

#include <QDialog>
#include "produit.h"


namespace Ui {
class ProdTrier;
}

class ProdTrier : public QDialog
{
    Q_OBJECT

public:
    explicit ProdTrier(QWidget *parent = nullptr);
    ~ProdTrier();

private:
    Ui::ProdTrier *ui;
    Produit c;
    bool test=false;

};

#endif // PRODTRIER_H
