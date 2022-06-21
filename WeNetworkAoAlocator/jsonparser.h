#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>
#include <QString>
#include <QDebug>
#include <QFile>
#include <QDateTime>
#include <QDir>
#include "database.h"

class jsonparser
{
public:
    jsonparser();

    void jsonloader();
    void jsonsaver();


};

#endif // JSONPARSER_H
