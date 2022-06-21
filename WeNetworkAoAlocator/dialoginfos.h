#ifndef DIALOGINFOS_H
#define DIALOGINFOS_H

#include <QDialog>

namespace Ui {
class Dialoginfos;
}

class Dialoginfos : public QDialog
{
    Q_OBJECT

public:
    explicit Dialoginfos(QWidget *parent = nullptr);
    ~Dialoginfos();

private:
    Ui::Dialoginfos *ui;
};

#endif // DIALOGINFOS_H
