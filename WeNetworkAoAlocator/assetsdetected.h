#ifndef ASSETSDETECTED_H
#define ASSETSDETECTED_H

#include <QString>
#include <QList>

class assetsdetected
{
public:
    assetsdetected();

    QString name;
    QString date;
    double azim=0;
    double elev=0;

     QList<double> listazimuth;

    void addtolist(double az);
    double calcul();
    void setname(QString na){
    name=na;
    }
    void setdate(QString da){
    date=da;
    }
    void setaz(double az){
    azim=az;
    }
    void setelev(double el){
    elev=el;
    }
};
int compare(const void* a, const void* b);

#endif // ASSETSDETECTED_H
