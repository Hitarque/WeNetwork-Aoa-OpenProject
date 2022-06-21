/*Fait par Hugo FABRE*/
#include "dialogmodifylocator.h"
#include "ui_dialogmodifylocator.h"

#include "database.h"

/*Setup ui de la page de modification + insertion des données pour l'affichage, enregistré dans database*/
Dialogmodifylocator::Dialogmodifylocator(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialogmodifylocator)
{
    int i=database::GetInstance().returncurrentlocator();
    Locator a=database::GetInstance().returnlocator(i);

    ui->setupUi(this);
    ui->textEdit->setText(a.name);
    ui->textEdit_2->setText(a.ip);

    ui->doubleSpinBox->setValue(a.posx);
    ui->doubleSpinBox_2->setValue(a.posy);
}

/*Destruction de l'UI*/
Dialogmodifylocator::~Dialogmodifylocator()
{
    delete ui;
}

/*Mise a jour des données enregistré dans database*/
void Dialogmodifylocator::on_buttonBox_accepted()
{
   database::GetInstance().modifylocator(database::GetInstance().returncurrentlocator(), ui->textEdit->toPlainText(), ui->textEdit_2->toPlainText(),ui->doubleSpinBox->value(),ui->doubleSpinBox_2->value());
 }

