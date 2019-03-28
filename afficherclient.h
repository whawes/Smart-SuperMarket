#ifndef AFFICHERCLIENT_H
#define AFFICHERCLIENT_H
#include "client.h"
#include <QDialog>

namespace Ui {
class AfficherClient;
}

class AfficherClient : public QDialog
{
    Q_OBJECT

public:
    explicit AfficherClient(QWidget *parent = nullptr);
    ~AfficherClient();

private slots:
    void on_pushButton_clicked();

private:
    Ui::AfficherClient *ui;
    Client cl;
};

#endif // AFFICHERCLIENT_H
