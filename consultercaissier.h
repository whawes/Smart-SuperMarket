#ifndef CONSULTERCAISSIER_H
#define CONSULTERCAISSIER_H

#include <QDialog>

namespace Ui {
class ConsulterCaissier;
}

class ConsulterCaissier : public QDialog
{
    Q_OBJECT

public:
    explicit ConsulterCaissier(QWidget *parent = nullptr);
    ~ConsulterCaissier();

private slots:
    void on_pushButton_clicked();

private:
    Ui::ConsulterCaissier *ui;
};

#endif // CONSULTERCAISSIER_H
