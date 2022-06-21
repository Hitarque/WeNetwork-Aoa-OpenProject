#ifndef DIALOGOPTIONS_H
#define DIALOGOPTIONS_H

#include <QDialog>

namespace Ui {
class Dialogoptions;
}

class Dialogoptions : public QDialog
{
    Q_OBJECT

public:
    explicit Dialogoptions(QWidget *parent = nullptr);
    ~Dialogoptions();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::Dialogoptions *ui;
};

#endif // DIALOGOPTIONS_H
