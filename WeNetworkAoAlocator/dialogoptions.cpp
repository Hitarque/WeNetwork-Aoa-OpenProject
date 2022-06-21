/*Fait par Hugo FABRE*/
#include "dialogoptions.h"
#include "ui_dialogoptions.h"
#include "database.h"

/*Setup de l'ui option + insertion des données d'option pré-enregistré*/
Dialogoptions::Dialogoptions(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialogoptions)
{
    ui->setupUi(this);

    ui->textEdit_2->setText(database::GetInstance().returnurlbroker());
    ui->textEdit->setText(database::GetInstance().returnportbroker());
    ui->textEdit_3->setText(database::GetInstance().returnurlAoa_locaor());
    ui->textEdit_4->setText(database::GetInstance().returnurllogdata());
    ui->spinBox->setValue(database::GetInstance().returnmoyglissante());
}

/*Destruction de l'ui*/
Dialogoptions::~Dialogoptions()
{
    delete ui;
}

/*Mise a jour des données d'option dans la database*/
void Dialogoptions::on_buttonBox_accepted()
{
   database::GetInstance().urlbroker=ui->textEdit->toPlainText();
   database::GetInstance().portbroker=ui->textEdit_2->toPlainText();
   database::GetInstance().urlAoa_locaor=ui->textEdit_3->toPlainText();
   database::GetInstance().urlogdatasave=ui->textEdit_4->toPlainText();
   database::GetInstance().moyglissantelength=ui->spinBox->value();
}

