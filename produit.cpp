#include "produit.h"
#include "ui_produit.h"
#include "bib.h"

Produit::Produit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Produit)
{
    ui->setupUi(this);
    Afficher_Produit();
    mSystemTrayIcon = new QSystemTrayIcon(this);
    mSystemTrayIcon->setIcon(QIcon("myappico.png"));
    mSystemTrayIcon->setVisible(true);
}

Produit::~Produit()
{
    delete ui;
}

int Produit::getNumero()
{
    return Numero;
}
void Produit::setNumero(int numero)
{
    Numero=numero;
}
int Produit::getQuantite()
{
    return Quantite;
}
void Produit::setQuantite(int quantite)
{
    Quantite=quantite;
}
double Produit::getPrix()
{
    return Prix;
}
void Produit::setPrix(double prix)
{
    Prix=prix;
}
double Produit::getPoids()
{
    return Poids;
}
void Produit::setPoids(double poids)
{
    Poids=poids;
}
QString Produit::getNom()
{
    return Nom;
}
void Produit::setNom(QString nom)
{
    Nom=nom;
}
QString Produit::getMarque()
{
    return Marque;
}
void Produit::setMarque(QString marque)
{
    Marque=marque;
}
QString Produit::getType()
{
    return Type;
}
void Produit::setType(QString type)
{
    Type=type;
}
QString Produit::getLocalisation()
{
    return Localisation;
}
void Produit::setLocalisation(QString localisation)
{
    Localisation=localisation;
}

/**********************************************************************************************************************************************************************************/
void Produit::Ajouter_Produit(int Numero,int Quantite ,double Prix,double Poids ,QString Nom,QString Marque,QString Type ,QString Localisation)
{
    QSqlQuery qry;
    qry.prepare("INSERT INTO PRODUIT (NUMERO ,QUANTITE,PRIX,POIDS,NOM,MARQUE,TYPE,LOCALISATION)"
                 "VALUES(?,?,?,?,?,?,?,?)");
        qry.addBindValue(Numero);
        qry.addBindValue(Quantite);
        qry.addBindValue(Prix);
        qry.addBindValue(Poids);
        qry.addBindValue(Nom);
        qry.addBindValue(Marque);
        qry.addBindValue(Type);
        qry.addBindValue(Localisation);
        qry.exec();
        qry.prepare("INSERT INTO PRODUITS (NOM_PRODUIT ,PRIX_PRODUIT,POIDS_PRODUIT,QUANTITE_PRODUIT,ID_PRODUIT)"
                     "VALUES(?,?,?,?,?)");
        qry.addBindValue(Nom);

            qry.addBindValue(Prix);
            qry.addBindValue(Poids);
            qry.addBindValue(Quantite);
            qry.addBindValue(Numero);


            qry.exec();
            mSystemTrayIcon->showMessage(tr("Produit ajoute"),
                                                  tr("Operation effectué"));
        Afficher_Produit();
}
/***********************************************************************************************************************************************************************/

void Produit::Modifier_Produit(int Numero,int Quantite ,double Prix,double Poids ,QString Nom,QString Marque,QString Type ,QString Localisation)
{
    QSqlQuery qry;
    qry.prepare("UPDATE PRODUIT set QUANTITE=(?),PRIX=(?),POIDS=(?),NOM=(?),MARQUE=(?),TYPE=(?),LOCALISATION=(?) where NUMERO=(?) ");
    qry.addBindValue(Quantite);
    qry.addBindValue(Prix);
    qry.addBindValue(Poids);
    qry.addBindValue(Nom);
    qry.addBindValue(Marque);
    qry.addBindValue(Type);
    qry.addBindValue(Localisation);
    qry.addBindValue(Numero);
    qry.exec();
    mSystemTrayIcon->showMessage(tr("Produit modifie "),
                                          tr("Modification effectué"));
    ui->AfficherP->clearContents();
    Afficher_Produit();
}
/*************************************************************************************************************************************************************************/

void Produit::Afficher_Produit()
{
     QSqlQuery qry;
    while(ui->AfficherP->rowCount()>0)
        {
            ui->AfficherP->removeRow(0);
        }
        qry.exec("select * from Produit ");
            int c = -1;
            while (qry.next())
            {
                c++;
                ui->AfficherP->insertRow(c);
                for (int j=0; j<8; j++)
                {
                    QTableWidgetItem *item1 = new QTableWidgetItem(QString(qry.value(j).toString()));
                    this->ui->AfficherP->setItem(c,j,item1);
                 }
              }
}
/*********************************************************************************************************************************************************/

void Produit::Supprimer_Produit()
{
    QSqlQuery qry;
    int i=ui->AfficherP->currentRow();
                int id=ui->AfficherP->item(i,0)->text().toInt();
                qry.prepare("Delete from PRODUIT where NUMERO=(?)");
                qry.addBindValue(id);
                qry.exec();
                ui->AfficherP->removeRow(i);
                mSystemTrayIcon->showMessage(tr("Rayon supprimer "),
                                                      tr("Suppression effectué"));
}
/***************************************************************************************************************************************************/

void Produit::tri_Produit_c()
{
    QSqlQuery qry;
   while(ui->AfficherP->rowCount()>0)
       {
           ui->AfficherP->removeRow(0);
       }
       qry.exec("select * from Produit order by NOM asc");
           int c = -1;
           while (qry.next())
           {
               c++;
               ui->AfficherP->insertRow(c);
               for (int j=0; j<8; j++)
               {
                   QTableWidgetItem *item1 = new QTableWidgetItem(QString(qry.value(j).toString()));
                   this->ui->AfficherP->setItem(c,j,item1);
                }
             }
}
/*******************************************************************************************************************************************************************/

void Produit::tri_Produit_d()
{
    QSqlQuery qry;
   while(ui->AfficherP->rowCount()>0)
       {
           ui->AfficherP->removeRow(0);
       }
       qry.exec("select * from Produit order by NOM desc");
           int c = -1;
           while (qry.next())
           {
               c++;
               ui->AfficherP->insertRow(c);
               for (int j=0; j<8; j++)
               {
                   QTableWidgetItem *item1 = new QTableWidgetItem(QString(qry.value(j).toString()));
                   this->ui->AfficherP->setItem(c,j,item1);
                }
             }
}
/********************************************************************************************************************************************/


void Produit::on_ajouter_2_clicked()
{
   setNumero(ui->numero_->text().toInt());
   setQuantite(ui->quantite_->text().toInt());
   setPrix(ui->prix->text().toDouble());
   setPoids(ui->poids_->text().toDouble());
   setNom(ui->nom_->text());
   setMarque(ui->marque_->text());
   setType(ui->type_->text());
   setLocalisation(ui->localisation_->text());

   Ajouter_Produit( getNumero(), getQuantite() , getPrix(),getPoids() ,getNom(),getMarque(),getType() ,getLocalisation());
}
/**********************************************************************************************************************************************/

void Produit::on_supprimer_clicked()
{
    if(ui->AfficherP->currentRow()!=-1)
    Supprimer_Produit();
}
/***********************************************************************************************************************/

void Produit::on_AfficherP_itemClicked(QTableWidgetItem *i)
{
     int j=ui->AfficherP->currentRow();
    setNumero(ui->AfficherP->item(j,0)->text().toInt());
    setQuantite(ui->AfficherP->item(j,1)->text().toInt());
    setPrix(ui->AfficherP->item(j,2)->text().toDouble());
    setPoids(ui->AfficherP->item(j,3)->text().toDouble());
    setNom(ui->AfficherP->item(j,4)->text());
    setMarque(ui->AfficherP->item(j,5)->text());
    setType(ui->AfficherP->item(j,6)->text());
    setLocalisation(ui->AfficherP->item(j,7)->text());

             ui->numero_3->setText(ui->AfficherP->item(j,0)->text());
             ui->quantite_3->setText(ui->AfficherP->item(j,1)->text());
             ui->prix_4->setText(ui->AfficherP->item(j,2)->text());
             ui->poids_3->setText(ui->AfficherP->item(j,3)->text());
             ui->nom_3->setText(ui->AfficherP->item(j,4)->text());
             ui->marque_3->setText(ui->AfficherP->item(j,5)->text());
             ui->type_3->setText(ui->AfficherP->item(j,6)->text());
             ui->localisation_3->setText(ui->AfficherP->item(j,7)->text());

}
/***********************************************************************************************************************/

void Produit::on_modifier_clicked()
{
    Modifier_Produit(ui->numero_3->text().toInt(),ui->quantite_3->text().toInt(),ui->prix_4->text().toDouble(),ui->poids_3->text().toDouble(),ui->nom_3->text(),ui->marque_3->text(),ui->type_3->text(),ui->localisation_3->text());
}
/***************************************************************************************************************************************/
void Produit::Rechercher_Produit()
{
    QString type=ui->recherche->currentText();
    QString valeur=ui->ecrire->text();
    QSqlQuery qry;
    if(type=="NUMERO")
    {
        qry.prepare("select NUMERO,QUANTITE,PRIX,POIDS,NOM,MARQUE,TYPE,LOCALISATION from PRODUIT where NUMERO=(?)");
        qry.addBindValue(valeur);
        qry.exec();
    }
    else if(type=="QUANTITE")
    {
        qry.prepare("select NUMERO,QUANTITE,PRIX,POIDS,NOM,MARQUE,TYPE,LOCALISATION from PRODUIT where QUANTITE=(?)");
        qry.addBindValue(valeur);
        qry.exec();
    }
    else if(type=="PRIX")
    {
        qry.prepare("select NUMERO,QUANTITE,PRIX,POIDS,NOM,MARQUE,TYPE,LOCALISATION from PRODUIT where PRIX=(?)");
        qry.addBindValue(valeur);
        qry.exec();
    }

    else if(type=="POIDS")
    {
        qry.prepare("select NUMERO,QUANTITE,PRIX,POIDS,NOM,MARQUE,TYPE,LOCALISATION from PRODUIT where POIDS=(?)");
        qDebug()<<valeur;
        qry.addBindValue(valeur);
        qry.exec();
    }
    else if(type=="NOM")
    {
        qry.prepare("select NUMERO,QUANTITE,PRIX,POIDS,NOM,MARQUE,TYPE,LOCALISATION from PRODUIT where NOM=(?)");
        qry.addBindValue(valeur);
        qry.exec();
    }
    else if(type=="MARQUE")
    {
        qry.prepare("select NUMERO,QUANTITE,PRIX,POIDS,NOM,MARQUE,TYPE,LOCALISATION from PRODUIT where MARQUE=(?)");
        qry.addBindValue(valeur);
        qry.exec();
    }
    else if(type=="TYPE")
    {
        qry.prepare("select NUMERO,QUANTITE,PRIX,POIDS,NOM,MARQUE,TYPE,LOCALISATION from PRODUIT where TYPE=(?)");
        qry.addBindValue(valeur);
        qry.exec();
    }
    else if(type=="LOCALISATION")
    {
        qry.prepare("select NUMERO,QUANTITE,PRIX,POIDS,NOM,MARQUE,TYPE,LOCALISATION from PRODUIT where LOCALISATION=(?)");
        qry.addBindValue(valeur);
        qry.exec();
    }
    while(ui->AfficherP->rowCount()>0)
    {
        ui->AfficherP->removeRow(0);
    }
    int c=-1;
    while (qry.next())
    {

     c++;

     ui->AfficherP->insertRow(c);
     for(int j=0;j<9;j++)
     {
         QTableWidgetItem *item1= new QTableWidgetItem(QString(qry.value(j).toString()));
         this->ui->AfficherP->setItem(c,j,item1);
     }
    }
    if(valeur=="")
    {
        Afficher_Produit();
    }
}
/***************************************************************************************************************************************/


void Produit::on_chercher_clicked()
{
    Rechercher_Produit();
}
/***************************************************************************************************************************************/

void Produit::on_tricroissant_clicked()
{
    tri_Produit_c();
}
/***************************************************************************************************************************************/

void Produit::on_tridecroissant_clicked()
{
    tri_Produit_d();
}

QSqlQueryModel*  Produit::TriProduits()
{
        QSqlQueryModel* model =new QSqlQueryModel();
         QSqlQuery  *q  = new QSqlQuery();
         q->prepare("SELECT * FROM Produits order by Prix_produit asc");
         q->exec();
         model->setQuery(*q);
         return model ;
}
