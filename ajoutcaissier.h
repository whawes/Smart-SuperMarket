#ifndef AJOUTCAISSIER_H
#define AJOUTCAISSIER_H

#include <QDialog>
#include <QSystemTrayIcon>
#include "caisse.h"

namespace Ui {
class AjoutCaissier;
}

class AjoutCaissier : public QDialog
{
    Q_OBJECT

public:
    explicit AjoutCaissier(QWidget *parent = nullptr);
    ~AjoutCaissier();

private slots:
    void on_pushButton_clicked();

private:
    Ui::AjoutCaissier *ui;
    QSystemTrayIcon *mSystemTrayIcon;
    Caisse Cai;
};

#endif // AJOUTCAISSIER_H
