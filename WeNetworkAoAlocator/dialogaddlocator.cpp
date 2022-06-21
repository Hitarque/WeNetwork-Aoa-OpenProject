/*Fait par Hugo FABRE*/
#include "dialogaddlocator.h"
#include "ui_dialogaddlocator.h"

/*Setup de l'interface utilisateur*/
Dialogaddlocator::Dialogaddlocator(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialogaddlocator)
{
    ui->setupUi(this);
}


/*Destruction de l'interface utilisateur*/
Dialogaddlocator::~Dialogaddlocator()
{
    delete ui;
}


/*Action lorsque validée, il appel la création d'un nouveau locator avec les informations rentré*/
void Dialogaddlocator::on_buttonBox_accepted()
{
    database::GetInstance().addlocator(ui->comboBox->currentText(),ui->textEdit_2->toPlainText(),ui->doubleSpinBox->value(),ui->doubleSpinBox_2->value());
    delete ui;
}

