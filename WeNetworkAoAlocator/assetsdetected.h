#ifndef ASSETSDETECTED_H
#define ASSETSDETECTED_H

#include <QString>

class assetsdetected
{
public:
    assetsdetected();

    QString name;
    QString date;
    double azim;
    double elev;

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

#endif // ASSETSDETECTED_H
