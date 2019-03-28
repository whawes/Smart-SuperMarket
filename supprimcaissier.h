#ifndef SUPPRIMCAISSIER_H
#define SUPPRIMCAISSIER_H

#include <QDialog>
#include "ajoutcaissier.h"
#include <QSystemTrayIcon>

namespace Ui {
class SupprimCaissier;
}

class SupprimCaissier : public QDialog
{
    Q_OBJECT

public:
    explicit SupprimCaissier(QWidget *parent = nullptr);
    ~SupprimCaissier();

private slots:
    void on_pushButton_clicked();

private:
    Ui::SupprimCaissier *ui;
    QSystemTrayIcon *mSystemTrayIcon;
    Caisse Cai;
};

#endif // SUPPRIMCAISSIER_H
