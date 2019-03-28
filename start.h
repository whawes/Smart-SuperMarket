#ifndef START_H
#define START_H
#include "employee.h"
#include <QDialog>
#include <QMessageBox>
#include "client.h"
#include "identification.h"
#include <QSqlRecord>
#include "afficherclient.h"
#include "emplacement.h"
#include "afficheremplacement.h"
#include <QSystemTrayIcon>
#include "fournisseur.h"
#include "commande.h"
#include "facture.h"
#include "Ligne_commande.h"
#include <QString>
#include <QPdfWriter>
#include <QPrinter>
#include <QPainter>
#include <QTextDocument>
#include "produit.h"
#include "rayon.h"
#include "absence.h"
#include "admin.h"
namespace Ui {
class Start;
}

class Start : public QDialog
{
    Q_OBJECT

public:
    explicit Start(QWidget *parent = nullptr);
    ~Start();
    bool verifierlogin(QString,QString);
    int verifierchoix();
    int verifierlength(int);
private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_22_clicked();

    void on_pushButton_25_clicked();

    void on_pushButton_30_clicked();

    void on_pushButton_31_clicked();

    void on_pushButton_37_clicked();

    void on_pushButton_36_clicked();

    void on_pushButton_34_clicked();

    void on_pushButton_35_clicked();

    void on_pushButton_32_clicked();

    void on_pushButton_38_clicked();

    void on_pushButton_23_clicked();

    void on_pushButton_24_clicked();

    void on_pushButton_21_clicked();

    void on_pushButton_33_clicked();

    void on_pushButton_39_clicked();

    void on_pushButton_40_clicked();

    void on_pushButton_26_clicked();

    void on_pushButton_27_clicked();

    void on_pushButton_41_clicked();

    void on_pushButton_43_clicked();

    void on_pushButton_42_clicked();

    void on_pushButton_28_clicked();

    void on_pushButton_44_clicked();

    void on_pushButton_29_clicked();

    void on_pushButton_45_clicked();

    void on_pushButton_20_clicked();

    void on_pushButton_47_clicked();

    void on_pushButton_46_clicked();

    void on_pushButton_48_clicked();

    void on_pushButton_18_clicked();

    void on_pushButton_51_clicked();

    void on_pushButton_49_clicked();

    void on_pushButton_50_clicked();

    void on_pushButton_52_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_53_clicked();

    void on_pushButton_54_clicked();

    void on_pushButton_55_clicked();

    void on_pushButton_56_clicked();

    void on_pushButton_57_clicked();

    void on_pushButton_58_clicked();

    void on_pushButton_59_clicked();

    void on_pushButton_60_clicked();

    void on_pushButton_61_clicked();

    void on_pushButton_62_clicked();

    void on_pushButton_63_clicked();

    void on_pushButton_64_clicked();

    void on_pushButton_65_clicked();

    void on_pushButton_66_clicked();

    void on_pushButton_67_clicked();

    void on_pushButton_68_clicked();

    void on_pushButton_71_clicked();

    void on_pushButton_70_clicked();

    void on_pushButton_72_clicked();

    void on_pushButton_78_clicked();

    void on_pushButton_73_clicked();

    void on_pushButton_79_clicked();

    void on_pushButton_80_clicked();

    void on_pushButton_74_clicked();

    void on_pushButton_75_clicked();

    void on_pushButton_77_clicked();

    void on_pushButton_76_clicked();

    void on_pushButton_81_clicked();

    void on_pushButton_163_clicked();

    void on_pushButton_164_clicked();

    void on_pushButton_69_clicked();

    void on_pushButton_86_clicked();

    void on_pushButton_165_clicked();

    void on_pushButton_19_clicked();

    void on_pushButton_166_clicked();

    void on_sendBtn1_clicked();

    void on_pushButton_88_clicked();

    void on_pushButton_199_clicked();

    void on_pushButton_210_clicked();

    void on_pushButton_469_clicked();

    void on_pushButton_472_clicked();

    void on_pushButton_470_clicked();

    void on_pushButton_85_clicked();

    void on_pushButton_471_clicked();

    void on_pushButton_82_clicked();

    void on_pushButton_84_clicked();

    void on_pushButton_83_clicked();

    void on_pushButton_475_clicked();

    void on_pushButton_215_clicked();

    void on_pushButton_213_clicked();

    void on_pushButton_214_clicked();

    void on_pushButton_200_clicked();

private:

    Fournisseur four;
    Commande com;
    Facture fact;
    QSystemTrayIcon *mSystemTrayIcon;
    Employee Emp;
    Client cl;
    Absence ab;
    Emplacement em;
    Ui::Start *ui;
    QByteArray data;
    Arduino A;
    QString rfid;
    Admin ad;
    bool t=false;
};

#endif // START_H
