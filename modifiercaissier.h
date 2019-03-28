#ifndef MODIFIERCAISSIER_H
#define MODIFIERCAISSIER_H

#include <QDialog>
#include <QSystemTrayIcon>


namespace Ui {
class ModifierCaissier;
}

class ModifierCaissier : public QDialog
{
    Q_OBJECT

public:
    explicit ModifierCaissier(QWidget *parent = nullptr);
    ~ModifierCaissier();

private slots:
    void on_pushButton_clicked();

private:
    Ui::ModifierCaissier *ui;
    QSystemTrayIcon *mSystemTrayIcon;
};

#endif // MODIFIERCAISSIER_H
