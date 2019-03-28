#include "verifachat.h"
#include "ui_verifachat.h"
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QMessageBox>
#include <QPainter>
#include <QtPrintSupport/QPrinter>
#include <QTextDocument>
#include <QPrintDialog>
# include "connexion.h"


VerifAchat::VerifAchat(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VerifAchat)
{
    ui->setupUi(this);
}

VerifAchat::~VerifAchat()
{
    delete ui;
}

void VerifAchat::on_pushButton_clicked()
{
    /* Connection c;
               QSqlQueryModel *modal=new QSqlQueryModel();
               QSqlQuery* query=new QSqlQuery(c.db);
               QString  id=ui->line_ref->text();
               query->prepare("SELECT * FROM Poubelle where REF=:id");
               query->bindValue(":Ref",id);
               query->exec();
               modal->setQuery(*query);
               ui->tView->setModel(modal);*/
        QSqlQueryModel *modal=new QSqlQueryModel();
           QSqlQuery qry;
          QString  id=ui->line_num->text();
           qry.prepare("select *from Pan  where Num_Panier=:Num_Panier");
           qry.bindValue(":Num_Panier",id);
           if(qry.exec())
           {
               modal->setQuery(qry);
             ui->tview->setModel(modal);
           }
           else
           {
               QMessageBox::critical(nullptr, QObject::tr("critical error"),
               QObject::tr("ERROR            "
                           "VERIFIER VOTRE PARAMETRE !!."), QMessageBox::Cancel);
           }
}

void VerifAchat::on_pushButton_2_clicked()
{
    QString html="aaaa";
    QTextDocument document;
    document.setHtml(html);
    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName("Achats.pdf");
    document.print(&printer);
}

void VerifAchat::on_pushButton_3_clicked()
{

    QPrinter printer;
    printer.setPrinterName("Imprimer");
    QPrintDialog dialog(&printer,this);
    dialog.exec();
}

void VerifAchat::on_buttonBox_accepted()
{

               QSqlQueryModel *modal=new QSqlQueryModel();
               QSqlQuery* query=new QSqlQuery();
    query->prepare("DELETE  FROM Pan");

    query->exec();
}
