#include "dialogaddlocator.h"
#include "ui_dialogaddlocator.h"

Dialogaddlocator::Dialogaddlocator(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialogaddlocator)
{
    ui->setupUi(this);
}

Dialogaddlocator::~Dialogaddlocator()
{
    delete ui;
}

void Dialogaddlocator::on_buttonBox_accepted()
{
    database::GetInstance().addlocator(ui->comboBox->currentText(),ui->textEdit_2->toPlainText(),ui->doubleSpinBox->value(),ui->doubleSpinBox_2->value());
    delete ui;
}

