#ifndef AUTHENTIFICATIONCLIENT_H
#define AUTHENTIFICATIONCLIENT_H

#include <QDialog>
#include <QVector>
#include <QTableWidget>
#include <produits.h>
#include <QSystemTrayIcon>
#include "arduino.h"

namespace Ui {
class AuthentificationClient;
}

class AuthentificationClient : public QDialog
{
    Q_OBJECT

public:
    explicit AuthentificationClient(QWidget *parent = nullptr);
    ~AuthentificationClient();


private slots:
    void on_pushButton_clicked();
    void cellSelected(int row, int col);
     void update_label();


    void on_pushButton_2_clicked();

    void on_supprimer_clicked();

    void on_pushButton_3_clicked();

    void on_pushtri_clicked();

    //void on_trie_poids_clicked();

    //void on_lcdNumber_overflow();

private:
    QVector <Produits> vprods;
    Ui::AuthentificationClient *ui;
    QSystemTrayIcon *mSystemTrayIcon;
    Arduino A;
    QString AR="";
    QByteArray Data;
};

#endif // AUTHENTIFICATIONCLIENT_H
