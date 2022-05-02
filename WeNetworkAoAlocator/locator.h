#ifndef LOCATOR_H
#define LOCATOR_H

#include <QString>
#include <QDebug>
#include <iostream>
#include <fstream>

#include <string>

#include <io.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "assetsdetected.h"
#include "QList"

class Locator
{
public:
    Locator();
    QList<assetsdetected> assetsdetecteds;
    void runpowershell();

    void insertdata(QString na,QString i, double x,double y);
    double posx;
    double posy;
    QString name;
    QString ip;
    QString last_data;
    int numberofassets=0;

    void addnewassetdetected(QString name, QString date,double az,double ele);
    void majassetdetected(int id,QString name, QString date,double az,double ele);

    void setname(QString n);
    void setip(QString n);
    void setposx(double n);
    void setposy(double n);
    int findasset(QString name);
    assetsdetected returnasset(int i);
    int eraseall();
};

#endif // LOCATOR_Hs
