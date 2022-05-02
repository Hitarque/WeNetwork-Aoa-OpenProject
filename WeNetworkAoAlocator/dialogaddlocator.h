#ifndef DIALOGADDLOCATOR_H
#define DIALOGADDLOCATOR_H

#include <QDialog>
#include <QString>
#include "database.h"
namespace Ui {
class Dialogaddlocator;
}

class Dialogaddlocator : public QDialog
{
    Q_OBJECT

public:
    explicit Dialogaddlocator(QWidget *parent = nullptr);
    ~Dialogaddlocator();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::Dialogaddlocator *ui;
};

#endif // DIALOGADDLOCATOR_H
