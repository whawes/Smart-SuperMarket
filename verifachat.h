#ifndef VERIFACHAT_H
#define VERIFACHAT_H

#include <QDialog>

namespace Ui {
class VerifAchat;
}

class VerifAchat : public QDialog
{
    Q_OBJECT

public:
    explicit VerifAchat(QWidget *parent = nullptr);
    ~VerifAchat();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_buttonBox_accepted();

private:
    Ui::VerifAchat *ui;
};

#endif // VERIFACHAT_H
