#include "help.h"
#include "ui_help.h"
#include <QPropertyAnimation>

Help::Help(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Help)
{
    ui->setupUi(this);
    QPropertyAnimation *animation=new QPropertyAnimation(ui->pushButton, "geometry");
    animation->setDuration(1200);
    animation->setStartValue(QRect(150, 220, 75, 23));
    animation->setEndValue(QRect(270, 220, 75, 23));

    animation->start();
}

Help::~Help()
{
    delete ui;
}

void Help::on_pushButton_clicked()
{
    QWidget::close();
}
