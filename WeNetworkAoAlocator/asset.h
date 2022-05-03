#ifndef ASSET_H
#define ASSET_H

#include <QString>
#include <QList>
class Asset
{
public:
    Asset();

    QList<QList<double>> memory;
    double posx;
    double posy;
    QString name;
    QString last_data;

    void insertdatainarray(double x, double y);
};

#endif // ASSET_H
