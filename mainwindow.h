#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMessageBox>
#include <QMainWindow>
#include "help.h"
#include "start.h"
#include <QMediaPlayer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Client_clicked();

    void on_Help_clicked();

    void on_Quit_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
