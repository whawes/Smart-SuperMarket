#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    int const n=0;
    ui->setupUi(this);
    QMediaPlayer *player = new QMediaPlayer;
    player->setMedia(QUrl::fromLocalFile("C:/Users/admin/Desktop/esprit 2/projet/Qt/Elevator Music.mp3"));
    player->setVolume(n);
    player->play();
    ui->spinBox->setRange(0,100);
    ui->spinBox->setValue(n);
    ui->horizontalSlider->setRange(0,100);
    ui->horizontalSlider->setValue(n);
    QObject::connect(ui->horizontalSlider,SIGNAL(valueChanged(int)),ui->spinBox,SLOT(setValue(int)));
    QObject::connect(ui->spinBox,SIGNAL(valueChanged(int)),ui->horizontalSlider,SLOT(setValue(int)));
    QObject::connect(ui->horizontalSlider,SIGNAL(valueChanged(int)),player,SLOT(setVolume(int)));
    QObject::connect(ui->spinBox,SIGNAL(valueChanged(int)),player,SLOT(setVolume(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Client_clicked()
{
    Start s;
    s.setModal(true);
    s.exec();
}

void MainWindow::on_Help_clicked()
{
    Help h;
    h.setModal(true);
    h.exec();
}

void MainWindow::on_Quit_clicked()
{
    QMessageBox::StandardButton reply=QMessageBox::question(this,"","Etes vous sur?",QMessageBox::Yes|QMessageBox::No);
    if(reply==QMessageBox::Yes)
        QApplication::quit();
}

