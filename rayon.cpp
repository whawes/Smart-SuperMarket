#include "rayon.h"
#include "ui_rayon.h"
#include "bib.h"


Rayon::Rayon(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Rayon)
{
    ui->setupUi(this);
    Afficher_Rayon();
    mSystemTrayIcon = new QSystemTrayIcon(this);
    mSystemTrayIcon->setIcon(QIcon("myappico.png"));
    mSystemTrayIcon->setVisible(true);
}

Rayon::~Rayon()
{
    delete ui;
}

int Rayon:: getIdrayon()
{
    return  Idrayon;
}
void Rayon:: setIdrayon(int idrayon)
{
     Idrayon=idrayon;
}
int Rayon:: getNbproduit()
{
    return Nbproduit;
}
void Rayon:: setNbproduit(int nbproduit)
{
    Nbproduit=nbproduit;
}
double Rayon:: getHauteur()
{
    return  Hauteur;
}
void Rayon:: setHauteur(double hauteur)
{
    Hauteur=hauteur;
}
double Rayon:: getLargeur()
{
    return Largeur;
}
void Rayon:: setLargeur(double largeur)
{
    Largeur=largeur;
}

/********************************************************************************************************************************/
void Rayon:: Ajouter_Rayon(int Idrayon, double Hauteur, double Largeur ,int Nbproduit)
{
    QSqlQuery qry;
    qry.prepare("INSERT INTO RAYON (IDRAYON, HAUTEUR, LARGEUR, NBPRODUIT)"
                 "VALUES(?,?,?,?)");
        qry.addBindValue(Idrayon);
        qry.addBindValue(Hauteur);
        qry.addBindValue(Largeur);
        qry.addBindValue(Nbproduit);
        qry.exec();
        mSystemTrayIcon->showMessage(tr("Rayon ajouté "),
                                              tr("Le Rayon a ete ajoute"));
        Afficher_Rayon();
}
/*******************************************************************************************************************************************************************/

void Rayon:: Modifier_Rayon(int Idrayon, double Hauteur, double Largeur ,int Nbproduit)
{
    QSqlQuery qry;
    qry.prepare("UPDATE RAYON set IDRAYON=(?),HAUTEUR=(?),LARGEUR=(?),NBPRODUIT=(?) ");
    qry.addBindValue(Idrayon);
    qry.addBindValue(Hauteur);
    qry.addBindValue(Largeur);
    qry.addBindValue(Nbproduit);
    qry.exec();
    mSystemTrayIcon->showMessage(tr("Rayon modifie "),
                                          tr("Modification effectué"));
    ui->AfficherR->clearContents();
    Afficher_Rayon();
}
/*******************************************************************************************************************************************************************/

void Rayon:: Afficher_Rayon()
{
    QSqlQuery qry;
   while(ui->AfficherR->rowCount()>0)
       {
           ui->AfficherR->removeRow(0);
       }
       qry.exec("select * from RAYON ");
           int c = -1;
           while (qry.next())
           {
               c++;
               ui->AfficherR->insertRow(c);
               for (int j=0; j<5; j++)
               {
                   QTableWidgetItem *item1 = new QTableWidgetItem(QString(qry.value(j).toString()));
                   this->ui->AfficherR->setItem(c,j,item1);
                }
             }
}
/*******************************************************************************************************************************************************************/

void Rayon:: Supprimer_Rayon()
{
    QSqlQuery qry;
    int i=ui->AfficherR->currentRow();
                int Idrayon=ui->AfficherR->item(i,0)->text().toInt();
                qry.prepare("Delete from RAYON where IDRAYON=(?)");
                qry.addBindValue(Idrayon);
                qry.exec();
                ui->AfficherR->removeRow(i);
                mSystemTrayIcon->showMessage(tr("Rayon Supprimer "),
                                                      tr("Suppression effectué"));
}
/*******************************************************************************************************************************************************************/
void Rayon::on_ajouter_2_clicked()
{
    setIdrayon(ui->id->text().toInt());
    setHauteur(ui->hauteur->text().toDouble());
    setLargeur(ui->largeur->text().toDouble());
    setNbproduit(ui->nb->text().toInt());


    Ajouter_Rayon( getIdrayon(), getHauteur() , getLargeur(),getNbproduit() );
}
/*******************************************************************************************************************************************************************/

void Rayon::on_supprimer_clicked()
{
    if(ui->AfficherR->currentRow()!=-1)
    Supprimer_Rayon();
}
/*******************************************************************************************************************************************************************/





void Rayon::on_AfficherR_itemClicked(QTableWidgetItem *item)
{
   int j=ui->AfficherR->currentRow();
   setIdrayon(ui->AfficherR->item(j,0)->text().toInt());
   setHauteur(ui->AfficherR->item(j,1)->text().toDouble());
   setLargeur(ui->AfficherR->item(j,2)->text().toDouble());
   setNbproduit(ui->AfficherR->item(j,3)->text().toInt());


            ui->id_2->setText(ui->AfficherR->item(j,0)->text());
            ui->hauteur_2->setText(ui->AfficherR->item(j,1)->text());
            ui->largeur_2->setText(ui->AfficherR->item(j,2)->text());
            ui->nb_2->setText(ui->AfficherR->item(j,3)->text());
}

/*******************************************************************************************************************************************************************/
void Rayon::Rechercher_Rayon()
{
    QString type=ui->recherche->currentText();
    QString valeur=ui->ecrire->text();
    QSqlQuery qry;
    if(type=="IDRAYON")
    {
        qry.prepare("select IDRAYON,HAUTEUR,LARGEUR,NBPRODUIT from RAYON where IDRAYON=(?)");
        qry.addBindValue(valeur);
        qry.exec();
    }
    else if(type=="HAUTEUR")
    {
        qry.prepare("select IDRAYON,HAUTEUR,LARGEUR,NBPRODUIT from RAYON where HAUTEUR=(?)");
        qry.addBindValue(valeur);
        qry.exec();
    }
    else if(type=="LARGEUR")
    {
        qry.prepare("select IDRAYON,HAUTEUR,LARGEUR,NBPRODUIT from RAYON where LARGEUR=(?)");
        qry.addBindValue(valeur);
        qry.exec();
    }

    else if(type=="NBPRODUIT")
    {
        qry.prepare("select IDRAYON,HAUTEUR,LARGEUR,NBPRODUIT from RAYON where NBPRODUIT=(?)");
        qDebug()<<valeur;
        qry.addBindValue(valeur);
        qry.exec();
    }

    while(ui->AfficherR->rowCount()>0)
    {
        ui->AfficherR->removeRow(0);
    }
    int c=-1;
    while (qry.next())
    {

     c++;

     ui->AfficherR->insertRow(c);
     for(int j=0;j<4;j++)
     {
         QTableWidgetItem *item1= new QTableWidgetItem(QString(qry.value(j).toString()));
         this->ui->AfficherR->setItem(c,j,item1);
     }
    }
    if(valeur=="")
    {
        Afficher_Rayon();
    }
}


/*******************************************************************************************************************************************************************/

void Rayon::on_chercher_clicked()
{

Rechercher_Rayon();
}
/*******************************************************************************************************************************************************************/
void Rayon::tri_Rayon_c()
{
    QSqlQuery qry;
   while(ui->AfficherR->rowCount()>0)
       {
           ui->AfficherR->removeRow(0);
       }
       qry.exec("select * from rayon order by IDRAYON asc");
           int c = -1;
           while (qry.next())
           {
               c++;
               ui->AfficherR->insertRow(c);
               for (int j=0; j<4; j++)
               {
                   QTableWidgetItem *item1 = new QTableWidgetItem(QString(qry.value(j).toString()));
                   this->ui->AfficherR->setItem(c,j,item1);
                }
             }
}
/*******************************************************************************************************************************************************************/

void Rayon::tri_Rayon_d()
{
    QSqlQuery qry;
   while(ui->AfficherR->rowCount()>0)
       {
           ui->AfficherR->removeRow(0);
       }
       qry.exec("select * from rayon order by IDRAYON desc");
           int c = -1;
           while (qry.next())
           {
               c++;
               ui->AfficherR->insertRow(c);
               for (int j=0; j<4; j++)
               {
                   QTableWidgetItem *item1 = new QTableWidgetItem(QString(qry.value(j).toString()));
                   this->ui->AfficherR->setItem(c,j,item1);
                }
             }
}
/*******************************************************************************************************************************************************************/

void Rayon::on_tricroissant_clicked()
{
    tri_Rayon_c();
}

void Rayon::on_tridecroissant_clicked()
{
    tri_Rayon_d();
}
/*******************************************************************************************************************************************************************/

void Rayon::on_modifier_clicked()
{
    Modifier_Rayon(ui->id_2->text().toInt(),ui->hauteur_2->text().toDouble(),ui->largeur_2->text().toDouble(),ui->nb_2->text().toInt());
}
