#include "start.h"
#include "ui_start.h"
#include <QDebug>
#include "smtp.h"
#include "prodtrier.h"
#include "authentificationclient.h"
#include <QPrintDialog>
#include "date_abs.h"
#include "consultercaissier.h"
#include "ajoutcaissier.h"
#include "modifiercaissier.h"
#include "supprimcaissier.h"
#include "verifachat.h"

Start::Start(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Start)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    int ret=A.connect_arduino(); // lancer la connexion à arduino
    switch(ret){
    case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
        break;
    case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
       break;
    case(-1):qDebug() << "arduino is not available";
    }
    em.reset();
    mSystemTrayIcon = new QSystemTrayIcon(this);
    mSystemTrayIcon->setIcon(QIcon("myappico.png"));
    mSystemTrayIcon->setVisible(true);
}

Start::~Start()
{
    delete ui;
}

bool Start::verifierlogin(QString login, QString motdepasse)
{
    Identification ident;
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM EMPLOYEE");
    int row_count = model->rowCount();
    for(int i=0;i<row_count;i++)
    {
        Champs ch;
        QString log = model->record(i).value("ID").toString();
        QString mdp = model->record(i).value("MOTDEPASSE").toString();
        ch.Login=log;
        ch.MotDePasse=mdp;
        ident.vChamps.push_back(ch);
    }
    for(int j=0;j<ident.vChamps.size();j++)
    {
        if((ident.vChamps[j].Login==login)&&(ident.vChamps[j].MotDePasse==motdepasse))
            return true;
    }
        return false;
}

void Start::on_pushButton_2_clicked()
{
     QString login=ui->lineEdit->text();
     QString motdepasse=ui->lineEdit_2->text();
     bool test=verifierlogin(login,motdepasse);
     if(test)
     {
         ui->stackedWidget->setCurrentIndex(3);
         ui->tabetudiant->setModel(Emp.afficher(login,motdepasse));

     }
     else
         QMessageBox::critical(nullptr, QObject::tr("Authentification"),
                  QObject::tr("Erreur !\n"
                               "Login ou Mot De Passe invalide\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);
}

void Start::on_pushButton_4_clicked()
{
    int cin=ui->lineEdit_3->text().toInt();
        bool test=cl.supprimer(cin);
        if(test)
        {
            QMessageBox::information(nullptr, QObject::tr("Supprimer Client"),
                        QObject::tr("Client supprimé.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        }
        else
            QMessageBox::critical(nullptr, QObject::tr("Supprimer Client"),
                        QObject::tr("Erreur !.\n"
                                    "Client n'existe pas\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);

}

void Start::on_pushButton_3_clicked()
{
        AfficherClient ac;
        ac.setModal(true);
        ac.exec();
}

int Start::verifierchoix()
{
    if(ui->radioButton_1->isChecked())
        return 1;
    else if(ui->radioButton_2->isChecked())
        return 2;
    else if(ui->radioButton_3->isChecked())
        return 3;
    else if(ui->radioButton_4->isChecked())
        return 4;
    else if(ui->radioButton_5->isChecked())
        return 5;
    else return 0;
}

int Start::verifierlength(int cin)
{
    int num=0;
    while(cin)
    {
        cin=cin/10;
        num++;
    }
    return num;
}

void Start::on_pushButton_clicked()
{
    int cin = ui->lineEdit_cin->text().toInt();
    Client c(cin);
    int testlength=verifierlength(cin);
    int testchoix=verifierchoix();
    if((testlength==8)&&(testchoix!=-1)&&(cin))
    {
        bool test=c.ajouter();
        if(test)
        {
            mSystemTrayIcon->showMessage(tr("Ajouter CIN"),
                                         tr("CIN ajouté avec succès"));
            ui->frame->setStyleSheet("background : green");
            ui->tableView11->setModel(em.afficher(testchoix));
        }
    }
    else if((testlength!=8)&&(testchoix!=-1))
    {
        ui->frame->setStyleSheet("background : red");
    }
    else if((testlength==8)&&(testchoix==-1))
    {
        ui->frame->setStyleSheet("background : red");
    }
    else if((testlength!=8)&&(testchoix==-1))
    {
        ui->frame->setStyleSheet("background : red");
    }
}

void Start::on_pushButton_5_clicked()
{
    int oldcin = ui->lineEdit_4->text().toInt();
    bool testold=verifierlength(oldcin);
    int newcin = ui->lineEdit_5->text().toInt();
    bool testnew=verifierlength(newcin);
    if((oldcin)&&(newcin))
    {
        if((testold)&&(testnew))
        {
            bool test=cl.modifier(oldcin,newcin);
            if(test)
            {
                mSystemTrayIcon->showMessage(tr("Modifier CIN"),
                                             tr("CIN modifié avec succès"));
            }

        }
        else
            QMessageBox::critical(nullptr, QObject::tr("Modifier CIN"),
                      QObject::tr("Erreur !\n"
                                  "Verifier les champs\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void Start::on_pushButton_6_clicked()
{
    int secteur= ui->lineEdit_7->text().toInt();
    int num= ui->lineEdit_8->text().toInt();
    Emplacement e(secteur*100+num);
    if((secteur)&&(num))
    {
            bool test=e.ajouter();
            if(test)
            {
                mSystemTrayIcon->showMessage(tr("Ajouter Emplacement"),
                                             tr("Emplacement ajouté avec succès"));
            }
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Ajouter Emplacement"),
                QObject::tr("Erreur !\n"
                            "Verifier les champs\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
}

void Start::on_pushButton_7_clicked()
{
    if(t==true)
        em.verifier(/*A,*/data);
        t=true;
        afficheremplacement ae;
        ae.setModal(true);
        ae.exec();
}

void Start::on_pushButton_8_clicked()
{
    int oldsecteur = ui->lineEdit_9->text().toInt();
    int oldnumero = ui->lineEdit_11->text().toInt();
    int newsecteur = ui->lineEdit_10->text().toInt();
    int newnumero = ui->lineEdit_12->text().toInt();
    if((oldsecteur!=0)&&(oldnumero!=0)&&(newsecteur!=0)&&(newnumero!=00))
    {
        bool test=em.modifier(oldsecteur*100+oldnumero,newsecteur*100+newnumero);
        if(test)
        {
            mSystemTrayIcon->showMessage(tr("Modifier Emplacement"),
                                         tr("Emplacement modifié avec succès"));
        }
        else
            QMessageBox::critical(nullptr, QObject::tr("Modifier Emplacement"),
                      QObject::tr("Erreur !\n"
                                  "Verifier les champs\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void Start::on_pushButton_9_clicked()
{
    int secteur=ui->lineEdit_13->text().toInt();
    int numero=ui->lineEdit_14->text().toInt();
    if((secteur!=0)&&(numero!=0))
    {
        bool test=em.supprimer(secteur*100+numero);
        if(test)
        {
            mSystemTrayIcon->showMessage(tr("Supprimer Emplacement"),
                                         tr("Emplacement supprimé avec succès"));
        }
        else
            QMessageBox::critical(nullptr, QObject::tr("Supprimer Emplacement"),
                        QObject::tr("Erreur !.\n"
                                    "Emplacement n'existe pas\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void Start::on_pushButton_10_clicked()
{
    bool test=false;
    int id=ui->lineEdit_6->text().toInt();
    if(id!=0)
        {
        if(ui->radioButton_6->isChecked())
        {
            test=em.reserver(1,id,A);
        }
        else if(ui->radioButton_7->isChecked())
        {
            test=em.reserver(2,id,A);
        }
        else if(ui->radioButton_8->isChecked())
        {
            test=em.reserver(3,id,A);
        }
    }
    if(test)
    {
        mSystemTrayIcon->showMessage(tr("Reserver Emplacement"),
                                     tr("Emplacement reservé avec succès"));
        A.write_to_arduino("Reserver");
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Reserver Emplacement"),
                    QObject::tr("Erreur !.\n"
                                "Emplacement non Reservé pas\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}


void Start::on_pushButton_11_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void Start::on_pushButton_13_clicked()
{
    ui->stackedWidget->setCurrentIndex(18);
}

void Start::on_pushButton_14_clicked()
{
    QString html="";
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM client");
    int row_count = model->rowCount();
    for(int i=0;i<row_count;i++)
    {
        QString cin = model->record(i).value("CIN").toString();
        html=html+"<h1>"+cin+"</h1>";
    }
    QTextDocument document;
    document.setHtml(html);
    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName("client.pdf");
    document.print(&printer);
    mSystemTrayIcon->showMessage(tr("Enregistrer"),
                                 tr("PDF enregistré avec succès"));
}

void Start::on_pushButton_16_clicked()
{
     ui->stackedWidget->setCurrentIndex(4);
    A.write_to_arduino("Open");
}

void Start::on_pushButton_17_clicked()
{
    //ui->stackedWidget->setCurrentIndex(9);
    AuthentificationClient autClient;
    autClient.setModal(true);
    autClient.exec();
}

void Start::on_pushButton_15_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
}

void Start::on_pushButton_22_clicked()
{
    ui->stackedWidget->setCurrentIndex(7);
}

void Start::on_pushButton_25_clicked()
{QString id,mdp;
    id=ui->lineEdit_15->text();
    mdp=ui->lineEdit_16->text();
    QSqlQuery quer;
    if(quer.exec("select *from ADMIN where MotDePasse='"+mdp+"' and ID='"+id+"'" ))
    {
        int count=0;
        while(quer.next())
        {
            count++;
        }
        if(count==1)
        {
            ui->stackedWidget->setCurrentIndex(2);
        }
        else
            QMessageBox::warning(this,tr("Warning"),tr("Nom d'utilisateur ou Mot de pass est incorrect!!"));
    }
}

void Start::on_pushButton_30_clicked()
{
    ui->stackedWidget->setCurrentIndex(20);
}

void Start::on_pushButton_31_clicked()
{
    ui->tableView->setModel(four.afficher_fourniseur());
    ui->tableView_2->setModel(com.afficher_C());
    ui->tableView_3->setModel(fact.afficher());
}

void Start::on_pushButton_37_clicked()
{
    Facture F;
    Commande C;
    Fournisseur A;
    QString nomS=ui->lineEdit_SS->text();
    QString pRESTATAIRE=ui->lineEdit_Indice->text();
    QString dd=ui->lineEdit_FS->text();

    bool test= A.supprimer(nomS);
    bool test1= C.supprimer(pRESTATAIRE);
    bool test2=F.supprimer(dd);
    if(nomS.length()!=0){
        if(test)
    {
            QMessageBox::information(nullptr, QObject::tr("yeeey"),
                        QObject::tr("Fournisseur Supprimé.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        }}



    if(pRESTATAIRE.length()!=0){
       if(test1)
       {
               QMessageBox::information(nullptr, QObject::tr("yeeey"),
                           QObject::tr("Commande Supprimée.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);}}

    if(dd.length()!=0){
        if(test2){
            QMessageBox::information(nullptr, QObject::tr("yes"),
                                  QObject::tr("Facture Supprimée.\n"
                                              "Click Ok to exit."), QMessageBox::Cancel);}

    }
    else {
        QMessageBox::critical(nullptr, QObject::tr("No"),
                              QObject::tr("Rien à supprimé Supprimer.\n"
                                          "Click Ok to exit."), QMessageBox::Cancel);}

    }





void Start::on_pushButton_36_clicked()
{
    QString Date_commande,presta,prod,date_Achat,name,adresse,Nom,pres,dd;
    int qtsA,qts,tel,prix;

    Date_commande=ui->LineEdit_DateC->text();
    presta=ui->prestataire->text();
    prod=ui->LineEdit_Produit->text();
    date_Achat=ui->LineEdit_DateA->text();
    Nom=ui->LineEdit_Nom->text();
    adresse=ui->LineEdit_Adresse->text();
    qtsA=ui->LineEdit_Quantitef->text().toInt();
    qts=ui->LineEdit_Quantite->text().toInt();
    tel=ui->LineEdit_Telephone->text().toInt();
    prix=ui->LineEdit_Prix->text().toInt();
    name=ui->lineEdit_rechF->text();
    dd=ui->lineEdit_RechA->text();
    pres=ui->lineEdit_RechC->text();

    Facture A;
    Fournisseur F;
    Commande C;

    if(name.length()!=0){
           F.Update(name,Nom,adresse,tel);
           QMessageBox::information(nullptr, QObject::tr("yes"),
                                 QObject::tr("Facture Modifiée.\n"
                                             "Click Ok to exit."), QMessageBox::Cancel);}

       if(dd.length()!=0){
           A.Modifier(dd,date_Achat,prix,qtsA);
           QMessageBox::information(nullptr, QObject::tr("yes"),
                                 QObject::tr("Facture Modifiée.\n"
                                             "Click Ok to exit."), QMessageBox::Cancel);}
       if(pres.length()!=0){
           C.Update(pres,Date_commande,presta,prod,qts);
           QMessageBox::information(nullptr, QObject::tr("yes"),
                                 QObject::tr("Facture Modifiée.\n"
                                             "Click Ok to exit."), QMessageBox::Cancel);}
       else {
           QMessageBox::critical(nullptr, QObject::tr("yes"),
                                 QObject::tr("Rien à modifier.\n"
                                             "Click Ok to exit."), QMessageBox::Cancel);}
}

void Start::on_pushButton_34_clicked()
{
    QString html;
    QString fournisseur=ui->LineEdit_Nom->text();
    QString adresse=ui->LineEdit_Adresse->text();
    QString telephone=ui->LineEdit_Telephone->text();
    QString commande=ui->LineEdit_DateC->text();
    QString Produit=ui->LineEdit_Produit->text();
    QString Quantitecommande =ui->LineEdit_Quantite->text();
    QString Prestataire=ui->prestataire->text();
    QString Date_Achat=ui->LineEdit_DateA->text();
    QString Prix_unitaire=ui->LineEdit_Prix->text();
    QString Quantite=ui->LineEdit_Produit->text();
    html="<h1>Fournisseur: "+fournisseur+"</h1>"
         "<h1>Adresse: "+adresse+"</h1>"
         "<h1>Télephone: "+telephone+"</h1>"
         "<h1>Date Commande: "+commande+"</h1>"
         "<h1>Produit: "+Produit+"</h1>"
         "<h1>Quantite de commande: "+Quantitecommande+"</h1>"
         "<h1>Prestataire: "+Prestataire+"</h1>"
         "<h1>Date_Achat: "+Date_Achat+"</h1>"
         "<h1>Prix_unitaire: "+Prix_unitaire+"</h1>"
         "<h1>Quantite: "+Quantite+"</h1>";
       QTextDocument document;
       document.setHtml(html);
       QPrinter printer(QPrinter::PrinterResolution);
       printer.setOutputFormat(QPrinter::PdfFormat);
       printer.setOutputFileName("test.pdf");
       document.print(&printer);
}

void Start::on_pushButton_35_clicked()
{
    int i=0;
    QString Date_commande,Prestataire,Produit,Date_Achat,Nom,Adresse;
    int QuantiteA,Quantite,Telephone,Prix_unitaire;

    Date_commande=ui->LineEdit_DateC->text();
    Prestataire=ui->prestataire->text();
    Produit=ui->LineEdit_Produit->text();
    Date_Achat=ui->LineEdit_DateA->text();
    Nom=ui->LineEdit_Nom->text();
    Adresse=ui->LineEdit_Adresse->text();
    QuantiteA=ui->LineEdit_Quantitef->text().toInt();
    Quantite=ui->LineEdit_Quantite->text().toInt();
    Telephone=ui->LineEdit_Telephone->text().toInt();
    Prix_unitaire=ui->LineEdit_Prix->text().toInt();
    Fournisseur F(Nom,Telephone,Adresse);
    Facture A(Date_Achat,Prix_unitaire,QuantiteA);
    Commande C(Date_commande,Prestataire,Produit,Quantite);

    bool test=F.ajouter_F();

       if(test && Nom.length()!=0 && Adresse.length()!=0 && (Telephone)!=0)
       {
           QMessageBox::information(nullptr, QObject::tr("aaaa"),
                       QObject::tr("fournisseur ajoutée.\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);
           i++;
       }
        bool test1=A.Ajouter();
       if(test1 && Date_Achat.length()!=0 && (Prix_unitaire)!=0 && (QuantiteA)!=0)
       {
           QMessageBox::information(nullptr, QObject::tr("aaaa"),
                       QObject::tr("Facture ajoutée.\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);
           i++;
       }
       bool test2=C.ajouter_C();
       if(test2 && Date_commande.length()!=0 && Prestataire.length()!=0 && Produit.length()!=0 && (Quantite)!=0)
       {
           QMessageBox::information(nullptr, QObject::tr("aaaa"),
                       QObject::tr("commande ajoutée.\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);
           i++;
       }
       if(i==3)
       {
            mSystemTrayIcon->showMessage(tr("Notification Finance "),
                                         tr("Nouvelle Facture à envoyer"));
       }
       else {
           QMessageBox::critical(nullptr, QObject::tr("Non!"),
                       QObject::tr("Erreur!.\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);
       }

}

void Start::on_pushButton_32_clicked()
{
    QString a=ui->lineEdit_17->text();
    ui->tableView_4->setModel(four.rechercher(a));
    ui->tableView_6->setModel(fact.rechercher(a));
    ui->tableView_5->setModel(com.rechercher(a));
}

void Start::on_pushButton_38_clicked()
{
    QString html="";
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM client");
    int row_count = model->rowCount();
    for(int i=0;i<row_count;i++)
    {
        QString cin = model->record(i).value("CIN").toString();
        html=html+cin+"\n";
    }
    Smtp* smtp = new Smtp("mohamedyassine.ghadhoune@esprit.tn","sakerfomek753","smtp.gmail.com",465);
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));
    smtp->sendMail("mohamedyassine.ghadhoune@esprit.tn","mohamedyassine.ghadhoune@esprit.tn","Liste_Clinets",html);
}

void Start::on_pushButton_23_clicked()
{
    this->hide();
    Produit *p=new Produit();
    p->show();
}

void Start::on_pushButton_24_clicked()
{this->hide();
    Rayon *r=new Rayon();
    r->show();
}

void Start::on_pushButton_21_clicked()
{
    VerifAchat verif;
    verif.setModal(true);
    verif.exec();
}

void Start::on_pushButton_33_clicked()
{
    QPrinter printer;
    printer.setPrinterName("Imprimer");
    QPrintDialog dialog(&printer,this);
    dialog.exec();
}

void Start::on_pushButton_39_clicked()
{
    QString html;
        QString fournisseur=ui->LineEdit_Nom->text();
        QString adresse=ui->LineEdit_Adresse->text();
        QString telephone=ui->LineEdit_Telephone->text();
        QString commande=ui->LineEdit_DateC->text();
        QString Produit=ui->LineEdit_Produit->text();
        QString Quantitecommande =ui->LineEdit_Quantite->text();
        QString Prestataire=ui->prestataire->text();
        QString Date_Achat=ui->LineEdit_DateA->text();
        QString Prix_unitaire=ui->LineEdit_Prix->text();
        QString Quantite=ui->LineEdit_Produit->text();
        html="<h1>Fournisseur: "+fournisseur+"</h1>"
             "<h1>Adresse: "+adresse+"</h1>"
             "<h1>Télephone: "+telephone+"</h1>"
             "<h1>Date Commande: "+commande+"</h1>"
             "<h1>Produit: "+Produit+"</h1>"
             "<h1>Quantite de commande: "+Quantitecommande+"</h1>"
             "<h1>Prestataire: "+Prestataire+"</h1>"
             "<h1>Date_Achat: "+Date_Achat+"</h1>"
             "<h1>Prix_unitaire: "+Prix_unitaire+"</h1>"
             "<h1>Quantite: "+Quantite+"</h1>";
        Smtp* smtp = new Smtp("mohamedyassine.ghadhoune@esprit.tn","sakerfomek753","smtp.gmail.com",465);
        connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));
        smtp->sendMail("mohamedyassine.ghadhoune@esprit.tn","mohamedyassine.ghadhoune@esprit.tn","facture",html);
}

void Start::on_pushButton_40_clicked()
{
    QPrinter printer;
    printer.setPrinterName("Imprimer");
    QPrintDialog dialog(&printer,this);
    dialog.exec();
}

void Start::on_pushButton_26_clicked()
{
    ui->tableView_7->setModel(Emp.afficherEmploye());
    ui->stackedWidget->setCurrentIndex(10);
}

void Start::on_pushButton_27_clicked()
{
    ui->stackedWidget->setCurrentIndex(9);
}

void Start::on_pushButton_41_clicked()
{
    int id = ui->e_id->text().toInt();
    QString prenom = ui->e_prenom->text();
    QString nom = ui->e_nom->text();
    QString fonction = ui->e_fonction->text();
    int telephone = ui->e_telephone->text().toInt();
    QString mdp = ui->e_mdp->text();
    int cin = ui->e_cin->text().toInt();
    Employee e(id,prenom,nom,cin,telephone,fonction,mdp);
    if(e.ajouterEmploye()){
    mSystemTrayIcon->showMessage(tr("Employe ajouté "),
                                          tr("Nouveau employé à ajouter"));}
    else {
        QMessageBox::critical(nullptr, QObject::tr("Ajouter un employe!"),
                    QObject::tr("Erreur!.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void Start::on_pushButton_43_clicked()
{
    QSqlQueryModel *modal=new QSqlQueryModel();
           QSqlQuery qry;
          int id=ui->lineEdit_18->text().toInt();
           qry.prepare("select * from Employee  where ID=:id ");
           qry.addBindValue(id);
           if(qry.exec())
           {
               modal->setQuery(qry);
             ui->tableView_8->setModel(modal);
           }
           else
           {
               QMessageBox::critical(nullptr, QObject::tr("critical error"),
               QObject::tr("ERROR            "
                           "VERIFIER VOTRE PARAMETRE !!."), QMessageBox::Cancel);
           }
}

void Start::on_pushButton_42_clicked()
{
    QSqlQueryModel *modal=new QSqlQueryModel();
           QSqlQuery qry;
           qry.prepare("select *from Employee ORDER BY ID");
           if(qry.exec())
           {
               modal->setQuery(qry);
             ui->tableView->setModel(modal);
           }
           else
           {
               QMessageBox::critical(nullptr, QObject::tr("critical error"),
               QObject::tr("ERROR            "
                           "VERIFIER VOTRE PARAMETRE !!."), QMessageBox::Cancel);
           }
}

void Start::on_pushButton_28_clicked()
{
    ui->stackedWidget->setCurrentIndex(11);
}

void Start::on_pushButton_44_clicked()
{
    int id = ui->e_id_2->text().toInt();
    QString date = ui->e_date->text();
    Absence a(date,id);
    bool test=a.modifierAbsence();
    if(test==true)
    {
        mSystemTrayIcon->showMessage(tr("Absence modifiée "),
                                              tr("Nouvelle Absence à modifier"));

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Modifier une absence"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}

void Start::on_pushButton_29_clicked()
{
    ui->stackedWidget->setCurrentIndex(12);
}

void Start::on_pushButton_45_clicked()
{
    int id = ui->e_id_3->text().toInt();
     bool test=Emp.supprimerEmploye(id);
     if(test==true)
     {
         mSystemTrayIcon->showMessage(tr("Employe supprimé "),
                                               tr("Nouveau employe à supprimer"));

     }
     else
         QMessageBox::critical(nullptr, QObject::tr("Supprimer un employe"),
                     QObject::tr("Erreur !.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);
}

void Start::on_pushButton_20_clicked()
{
    /*QSqlQueryModel *modal=new QSqlQueryModel();
    QSqlQuery* query=new QSqlQuery();

    query->prepare("SELECT * FROM Absence");

    query->exec();

    modal->setQuery(*query);*/
   ui->tableView_9->setModel(ab.afficherAbsence());

    ui->stackedWidget->setCurrentIndex(13);
}

void Start::on_pushButton_47_clicked()
{
    QSqlQueryModel *modal=new QSqlQueryModel();
           QSqlQuery qry;
           int id=ui->e_id_4->text().toInt();
           qry.prepare("select *from Absence where ID_Employe=:id");
           qry.addBindValue(id);
           if(qry.exec())
           {
               modal->setQuery(qry);
             ui->tableView_9->setModel(modal);
           }
           else
           {
               QMessageBox::critical(nullptr, QObject::tr("critical error"),
               QObject::tr("ERROR            "
                           "VERIFIER VOTRE PARAMETRE !!."), QMessageBox::Cancel);
           }

}

void Start::on_pushButton_46_clicked()
{
    date_abs db;
    db.setModal(true);
    db.exec();
}

void Start::on_pushButton_48_clicked()
{
    ui->stackedWidget->setCurrentIndex(14);
}

void Start::on_pushButton_18_clicked()
{
    int id = ui->e_id_5->text().toInt();
    QString date = ui->e_date_2->text();
    Absence a(date,id);
    if(a.ajouterAbsence())
    {
        mSystemTrayIcon->showMessage(tr("Absence ajouté "),
                                          tr("Nouvelle Absence à ajouter"));
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Ajouter une absence"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}

void Start::on_pushButton_51_clicked()
{
    int id = ui->e_id_6->text().toInt();
    QString prenom = ui->e_prenom_2->text();
    QString nom = ui->e_nom_2->text();
    QString fonction = ui->e_fonction_2->text();
    int telephone = ui->e_telephone_2->text().toInt();
    QString mdp = ui->e_mdp_2->text();
    int cin = ui->e_cin_2->text().toInt();
    Employee e(id,prenom,nom,cin,telephone,fonction,mdp);
    //e.modifierEmploye();
    if(e.modifierEmploye())
    {
        mSystemTrayIcon->showMessage(tr("Employe modifié "),
                                              tr("Nouveau employé à modifier"));

    }
    else
    {QMessageBox::critical(nullptr, QObject::tr("Modifier un employe"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);}
}

void Start::on_pushButton_49_clicked()
{
    ui->stackedWidget->setCurrentIndex(15);
}

void Start::on_pushButton_50_clicked()
{
    ui->stackedWidget->setCurrentIndex(16);
}

void Start::on_pushButton_52_clicked()
{
    int id=ui->lineEdit_19->text().toInt();
    //ab.supprimerAbsence(id);
    if(ab.supprimerAbsence(id))
    {
        mSystemTrayIcon->showMessage(tr("Absence supprimé "),
                                              tr("Nouvelle absence à supprimer"));

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Supprimer une absence"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}

void Start::on_pushButton_12_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void Start::on_pushButton_53_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void Start::on_pushButton_54_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void Start::on_pushButton_55_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void Start::on_pushButton_56_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
}

void Start::on_pushButton_57_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}
void Start::on_pushButton_58_clicked()
{
    ui->stackedWidget->setCurrentIndex(20);
}

void Start::on_pushButton_59_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void Start::on_pushButton_60_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void Start::on_pushButton_61_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void Start::on_pushButton_62_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void Start::on_pushButton_63_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void Start::on_pushButton_64_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void Start::on_pushButton_65_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void Start::on_pushButton_66_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void Start::on_pushButton_67_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void Start::on_pushButton_68_clicked()
{
    QSqlQueryModel *modal=new QSqlQueryModel();
           QSqlQuery qry;
           int id=ui->lineEdit->text().toInt();
           qry.prepare("select *from Absence where ID_Employe=:id");
           qry.addBindValue(id);
           if(qry.exec())
           {
               modal->setQuery(qry);
             ui->tableView_34->setModel(modal);
           }
           else
           {
               QMessageBox::critical(nullptr, QObject::tr("critical error"),
               QObject::tr("ERROR            "
                           "VERIFIER VOTRE PARAMETRE !!."), QMessageBox::Cancel);
           }
    ui->stackedWidget->setCurrentIndex(22);
}

void Start::on_pushButton_71_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void Start::on_pushButton_70_clicked()
{

}

void Start::on_pushButton_72_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}

void Start::on_pushButton_78_clicked()
{
    /*data=A.read_from_arduino();
    rfid += data ;
    QStringList pieces = rfid.split( "\r\n" );
    if( pieces.length() >= 2 )
    {
        if( pieces[pieces.length() - 2].size() == 11 )
        {
            qDebug() << pieces[pieces.length() - 2];
            rfid="";*/
            ui->stackedWidget->setCurrentIndex(8);
        /*}
    }*/
}

void Start::on_pushButton_73_clicked()
{
   ui->stackedWidget->setCurrentIndex(21);
}

void Start::on_pushButton_79_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void Start::on_pushButton_80_clicked()
{
    ui->stackedWidget->setCurrentIndex(18);
}

void Start::on_pushButton_74_clicked()
{
    ConsulterCaissier con;
    con.setModal(true);
    con.exec();
}

void Start::on_pushButton_75_clicked()
{
    AjoutCaissier ajoutcaissier;
    ajoutcaissier.setModal(true);
    ajoutcaissier.exec();
}

void Start::on_pushButton_77_clicked()
{
    SupprimCaissier sup;
    sup.setModal(true);
    sup.exec();
}

void Start::on_pushButton_76_clicked()
{
    ModifierCaissier modifiercaissier;
    modifiercaissier.setModal(true);
    modifiercaissier.exec();
}

void Start::on_pushButton_81_clicked()
{
    QString id,mdp;
        id=ui->lineEdit_22->text();
        mdp=ui->lineEdit_21->text();
        QSqlQuery quer;
        if(quer.exec("select * from caisse where MDP='"+mdp+"' and ID='"+id+"'" ))
        {
            int count=0;
            while(quer.next())
            {
                count++;
            }
            if(count==1)
            {
                ui->stackedWidget->setCurrentIndex(19);
            }
            else
                QMessageBox::warning(this,tr("Warning"),tr("Nom d'utilisateur ou Mot de pass est incorrect!!"));
        }
}

void Start::on_pushButton_163_clicked()
{
    ui->stackedWidget->setCurrentIndex(18);
}

void Start::on_pushButton_164_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void Start::on_pushButton_69_clicked()
{
    /*QString login=ui->lineEdit->text();
    QString motdepasse=ui->lineEdit_2->text();
    ui->tableView_34->setModel(Emp.afficher(login,motdepasse));
    ui->stackedWidget->setCurrentIndex(22);*/
    QSqlQueryModel *modal=new QSqlQueryModel();
           QSqlQuery qry;
           int id=ui->lineEdit->text().toInt();
           qry.prepare("select *from Employee where ID=:id");
           qry.addBindValue(id);
           if(qry.exec())
           {
               modal->setQuery(qry);
             ui->tableView_10->setModel(modal);
           }
           else
           {
               QMessageBox::critical(nullptr, QObject::tr("critical error"),
               QObject::tr("ERROR            "
                           "VERIFIER VOTRE PARAMETRE !!."), QMessageBox::Cancel);
           }
    ui->stackedWidget->setCurrentIndex(17);
}

void Start::on_pushButton_86_clicked()
{
    QString html="";
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM employee");
    int row_count = model->rowCount();
    for(int i=0;i<row_count;i++)
    {
        QString nom = model->record(i).value("nom").toString();
        QString prenom = model->record(i).value("prenom").toString();
        html=html+"<h1>Nom: "+nom+"</h1>"
                  "<h1>Prenom: "+prenom+"</h1>"
                  "<h1></h1>";
    }
    QTextDocument document;
    document.setHtml(html);
    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName("employee.pdf");
    document.print(&printer);
    mSystemTrayIcon->showMessage(tr("Enregistrer"),
                                 tr("PDF enregistré avec succès"));
}

void Start::on_pushButton_165_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void Start::on_pushButton_19_clicked()
{
    ui->stackedWidget->setCurrentIndex(23);
}

void Start::on_pushButton_166_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void Start::on_sendBtn1_clicked()
{
    Smtp* smtp = new Smtp(ui->uname1->text(),ui->paswd1->text(),ui->server1->text(),ui->port1->text().toInt());
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));
    smtp->sendMail(ui->uname1->text(),ui->rcpt1->text(),ui->subject1->text(),ui->msg1->toPlainText());
}

void Start::on_pushButton_88_clicked()
{

    int id = ui->e_id_7->text().toInt();
    QString prenom = ui->e_prenom_3->text();
    QString nom = ui->e_nom_3->text();
    QString fonction = ui->e_fonction_3->text();
    int telephone = ui->e_telephone_3->text().toInt();
    QString mdp = ui->e_mdp_3->text();
    int cin = ui->e_cin_3->text().toInt();
    QString autorite = ui->e_autorite_3->text();
    Employee e(id,prenom,nom,cin,telephone,fonction,mdp);
    Admin a(id,prenom,nom,cin,telephone,fonction,mdp,autorite);
    if(e.modifierEmploye()&&a.modifierEmploye())
    mSystemTrayIcon->showMessage(tr("Admin modifier "),
                                          tr("Nouveau Admin à ajouter"));
}

void Start::on_pushButton_199_clicked()
{

    int id = ui->e_id_20->text().toInt();
        QString prenom = ui->e_prenom_9->text();
        QString nom = ui->e_nom_9->text();
        QString fonction = ui->e_fonction_9->text();
        int telephone = ui->e_telephone_9->text().toInt();
        QString mdp = ui->e_mdp_9->text();
        int cin = ui->e_cin_9->text().toInt();
        QString autorite = ui->e_autorite->text();
        Employee e(id,prenom,nom,cin,telephone,fonction,mdp);
        Admin a(id,prenom,nom,cin,telephone,fonction,mdp,autorite);
        if(e.ajouterEmploye()&&a.ajouterEmploye())
        mSystemTrayIcon->showMessage(tr("Admin ajouté "),
                                              tr("Nouveau Admin à ajouter"));
}

void Start::on_pushButton_210_clicked()
{

    int id = ui->e_id_23->text().toInt();
    bool test1=ad.supprimerEmploye(id);
     bool test=Emp.supprimerEmploye(id);
     if(test&&test1)
     {
         mSystemTrayIcon->showMessage(tr("Admin supprimé "),
                                               tr("Nouveau Admin à supprimer"));

     }
     else
         QMessageBox::critical(nullptr, QObject::tr("Supprimer un Admin"),
                     QObject::tr("Erreur !.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);
}

void Start::on_pushButton_469_clicked()
{

}

void Start::on_pushButton_472_clicked()
{
    QString html="";
       QSqlQueryModel * model= new QSqlQueryModel();
       model->setQuery("SELECT * FROM Admin");
       int row_count = model->rowCount();
       for(int i=0;i<row_count;i++)
       {
           QString nom = model->record(i).value("nom").toString();
           QString prenom = model->record(i).value("prenom").toString();
           html=html+"<h1>Nom: "+nom+"</h1>"
                     "<h1>Prenom: "+prenom+"</h1>"
                     "<h1></h1>";
       }
       QTextDocument document;
       document.setHtml(html);
       QPrinter printer(QPrinter::PrinterResolution);
       printer.setOutputFormat(QPrinter::PdfFormat);
       printer.setOutputFileName("Admin.pdf");
       document.print(&printer);
       mSystemTrayIcon->showMessage(tr("Enregistrer"),
                                    tr("PDF enregistré avec succès"));
}

void Start::on_pushButton_470_clicked()
{

}

void Start::on_pushButton_85_clicked()
{
    ui->tableView_57->setModel(ad.afficherEmploye());
    QSqlQueryModel *modal=new QSqlQueryModel();
           QSqlQuery qry;
          int id=ui->lineEdit_15->text().toInt();
           qry.prepare("select *from Admin where ID=:id ");
           qry.addBindValue(id);
           if(qry.exec())
           {
               modal->setQuery(qry);
             ui->tableView_58->setModel(modal);
           }
           else
           {
               QMessageBox::critical(nullptr, QObject::tr("critical error"),
               QObject::tr("ERROR            "
                           "VERIFIER VOTRE PARAMETRE !!."), QMessageBox::Cancel);
           }
    ui->stackedWidget->setCurrentIndex(27);
}

void Start::on_pushButton_471_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void Start::on_pushButton_82_clicked()
{
    ui->stackedWidget->setCurrentIndex(25);
}

void Start::on_pushButton_84_clicked()
{
    ui->stackedWidget->setCurrentIndex(24);
}

void Start::on_pushButton_83_clicked()
{
    ui->stackedWidget->setCurrentIndex(26);
}

void Start::on_pushButton_475_clicked()
{

}

void Start::on_pushButton_215_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void Start::on_pushButton_213_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void Start::on_pushButton_214_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void Start::on_pushButton_200_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}
