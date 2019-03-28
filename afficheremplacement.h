#ifndef AFFICHEREMPLACEMENT_H
#define AFFICHEREMPLACEMENT_H
#include "emplacement.h"
#include <QDialog>

namespace Ui {
class afficheremplacement;
}

class afficheremplacement : public QDialog
{
    Q_OBJECT

public:
    explicit afficheremplacement(QWidget *parent = nullptr);
    ~afficheremplacement();

private slots:
    void on_pushButton_clicked();

private:
    Emplacement em;
    Ui::afficheremplacement *ui;
};

#endif // AFFICHEREMPLACEMENT_H
