#ifndef DATE_ABS_H
#define DATE_ABS_H

#include <QDialog>

namespace Ui {
class date_abs;
}

class date_abs : public QDialog
{
    Q_OBJECT

public:
    explicit date_abs(QWidget *parent = nullptr);
    ~date_abs();

private slots:
    void on_pushButton_clicked();

private:
    Ui::date_abs *ui;
};

#endif // DATE_ABS_H
