/*Fait par Hugo FABRE*/
#include "dialoginfos.h"
#include "ui_dialoginfos.h"

/*Ui d'information: version logiciel, licences, etc...*/
Dialoginfos::Dialoginfos(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialoginfos)
{
    ui->setupUi(this);
}

Dialoginfos::~Dialoginfos()
{
    delete ui;
}
