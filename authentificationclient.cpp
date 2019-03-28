#include "authentificationclient.h"
#include "ui_authentificationclient.h"
//#include "espaceclient.h"
#include "connexion.h"
#include "produits.h"
#include "pan.h"
#include <QTableWidget>
#include <QString>
#include <prodtrier.h>
#include <QDebug>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include<QGraphicsView>
#include <QPainter>
#include <QtPrintSupport/QPrinter>
#include <QTextDocument>
#include "arduino.h"

AuthentificationClient::AuthentificationClient(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AuthentificationClient)

{
    ui->setupUi(this);

    int ret=A.connect_arduino(); // lancer la connexion à arduino
      switch(ret){
      case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
          break;
      case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
         break;
      case(-1):qDebug() << "arduino is not available";
      }
       QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); // permet de lancer
       //le slot update_label suite à la reception du signal readyRead (reception des données).

    mSystemTrayIcon = new QSystemTrayIcon(this);
        mSystemTrayIcon->setIcon(QIcon(":/myappico.png"));
        mSystemTrayIcon->setVisible(true);


    QSqlQuery qry;
    QTableWidget *t=ui->tableWidget;
        int i;
        int j=0;
        qry.exec("select * from PRODUITS");
        while(qry.next()){
            j++;
        }
        t->setRowCount(j);
        t->setColumnCount(5);
        t->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
        t->setHorizontalHeaderLabels(QString("NOM_PRODUIT;PRIX_PRODUIT;POIDS_PRODUIT;QUANTITE_PRODUIT;ID_PRODUIT").split(";"));
        t->setEditTriggers(QAbstractItemView::NoEditTriggers);
        t->setSelectionBehavior(QAbstractItemView::SelectRows);
        t->setSelectionMode((QAbstractItemView::SingleSelection));
        i=0;
        qry.exec("select * from PRODUITS");
        while(qry.next())
        {
            Produits p(qry.value(0).toString(),qry.value(1).toString(),qry.value(2).toString(),qry.value(3).toString(),qry.value(4).toString());
            vprods.push_back(p);

                   t->setItem(i,0,new QTableWidgetItem(qry.value(0).toString()));
                   t->setItem(i,1,new QTableWidgetItem(qry.value(1).toString()));
                   t->setItem(i,2,new QTableWidgetItem(qry.value(2).toString()));
                   t->setItem(i,3,new QTableWidgetItem(qry.value(3).toString()));
                   t->setItem(i,4,new QTableWidgetItem(qry.value(4).toString()));
        i++;
        }

        connect(t, SIGNAL(cellDoubleClicked(int, int)), this, SLOT(cellSelected(int, int)));
        //connect(t, SIGNAL(cellDoubleClicked(int, int)), this, SLOT(cellSelected1(int, int)));



               }



void AuthentificationClient:: cellSelected(int row, int col)
{
   bool testquant=true;
   QMessageBox::information(this, "", vprods[row].getId_Prod());
   Pan p("1","0","0",vprods[row].getNom_Prod(),vprods[row].getPrix_Prod(),"1",vprods[row].getPoids_Prod(),vprods[row].getId_Prod());
    p.Somme_Poids();
    p.Somme_Prix();
    QString qt="";
    QString prix="";
    QString poids="";
    QString pd=p.getPoids_Prod();
    QString pr=p.getPrix_Prod();
    QSqlQuery query;
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select * from pan");
    for(int i=0;i<model->rowCount();i++)
    {
        if(model->record(i).value("NOM_PRODUIT").toString()==p.getNom_Prod())
        {
            testquant=false;
            qt=model->record(i).value("QUANTITE_PRODUIT").toString();

            int a=qt.toInt();
            a++;
            qt=QString::number(a);
       //   qDebug()<<qt;

            poids=model->record(i).value("POIDS_PRODUIT").toString();
            int tot=poids.toInt();
            int PD=pd.toInt();
            tot=tot+PD;
            poids=QString::number(tot);
            qDebug()<<poids;
            prix=model->record(i).value("PRIX_PRODUIT").toString();
            int Prix=prix.toInt();
            int PR=pr.toInt();
            Prix=Prix+PR;
            prix=QString::number(Prix);
            qDebug()<<prix;
            break;
        }
    }
    qDebug()<<testquant;
    if(testquant==true){
       bool test=p.ajouter_Panier();
       if(test==true)
               {
           mSystemTrayIcon->showMessage(tr("Article ajouté au Panier "),
                                                     tr("Nouveau Article à Ajouter"));

                              QSqlQueryModel *modal=new QSqlQueryModel();
                              QSqlQuery* query=new QSqlQuery();

                              query->prepare("SELECT * FROM Pan");

                              query->exec();
                              modal->setQuery(*query);
                              ui->tableView->setModel(modal);

               }
               else
                   QMessageBox::critical(nullptr, QObject::tr("Supprimer un employe"),
                               QObject::tr("Erreur !.\n"
                                           "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
     {

        model->setQuery("update Pan set Quantite_produit='"+qt+"' where Nom_produit='"+p.getNom_Prod()+"'");
        model->setQuery("update Pan set Poids_produit='"+poids+"' where Nom_produit='"+p.getNom_Prod()+"'");
        model->setQuery("update Pan set PRIX_PRODUIT='"+prix+"' where Nom_produit='"+p.getNom_Prod()+"'");

        QSqlQueryModel *modal=new QSqlQueryModel();
        QSqlQuery* query=new QSqlQuery();

        query->prepare("SELECT * FROM Pan");

        query->exec();
        modal->setQuery(*query);
        ui->tableView->setModel(modal);

    }

}



AuthentificationClient::~AuthentificationClient()
{
    delete ui;
}

void AuthentificationClient::on_pushButton_clicked()
{  Pan p;
    QByteArray s;
   int somme=p.Somme_Prix();

   s=QByteArray::number(somme);
    A.write_to_arduino(s);

}


void AuthentificationClient::on_pushButton_2_clicked()
{

}

void AuthentificationClient::on_supprimer_clicked()
{
    QString id = ui->s_id->text();
    Pan e;
             if(e.Verfier(id))
             {
                 e.supprimerPannier(id);
                 mSystemTrayIcon->showMessage(tr("Article est Supprimer "),
                                                           tr("Supression d'un Article"));

                            QSqlQueryModel *modal=new QSqlQueryModel();
                            QSqlQuery* query=new QSqlQuery();

                            query->prepare("SELECT * FROM Pan");

                            query->exec();
                            modal->setQuery(*query);
                            ui->tableView->setModel(modal);

             }

            else
                QMessageBox::critical(nullptr, QObject::tr("Supprimer un article"),
                            QObject::tr("Erreur !.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
}

void AuthentificationClient::on_pushButton_3_clicked()
{
       QString id = ui->id_mod->text();
       QString qt = ui->lineEdit_qt->text();
       Pan p(id,qt);
       if(p.Verfier(id)){
       p.modifierPanier();

                  QSqlQueryModel *modal=new QSqlQueryModel();
                  QSqlQuery* query=new QSqlQuery();

                  query->prepare("SELECT * FROM Pan");

                  query->exec();
                  modal->setQuery(*query);
                  ui->tableView->setModel(modal);
                  mSystemTrayIcon->showMessage(tr("Article est Modifie "),
                                                            tr("Modification d'un Article"));
       }
       else
           QMessageBox::warning(this,"ERROR","Identifiant n'existe pas");

}

void AuthentificationClient::on_pushtri_clicked()
{
    ProdTrier proTrie;
    proTrie.setModal(true);
    proTrie.exec();
}

void AuthentificationClient::update_label()
{
  Data=A.read_from_arduino();
  AR+=Data;

  QStringList pieces = AR.split( "\r\n" );

    if( pieces.length() >= 2 )

        ui->lineEdit->setText( pieces[pieces.length() - 2]) ;
        //qDebug()<<pieces;
}
