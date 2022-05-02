#ifndef DIALOGMODIFYLOCATOR_H
#define DIALOGMODIFYLOCATOR_H

#include <QDialog>

namespace Ui {
class Dialogmodifylocator;
}

class Dialogmodifylocator : public QDialog
{
    Q_OBJECT

public:
    explicit Dialogmodifylocator(QWidget *parent = nullptr);
    ~Dialogmodifylocator();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::Dialogmodifylocator *ui;
};

#endif // DIALOGMODIFYLOCATOR_H
