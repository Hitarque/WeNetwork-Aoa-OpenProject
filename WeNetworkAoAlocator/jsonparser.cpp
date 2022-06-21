/*Fait par Hugo FABRE*/
#include "jsonparser.h"


jsonparser::jsonparser()
{

}

/*Charge les données d'un fichier Json pour la persistance des données d'options et les enregistre en tant que variables dans
la database*/
void jsonparser::jsonloader(){
    QFile inFile(QDir::currentPath()+"/config.json");
    //qDebug() << "[jsonparser.cpp] Data loaded from "+QDir::currentPath()+"/config.json";
        inFile.open(QIODevice::ReadOnly|QIODevice::Text);
        QString data = inFile.readAll();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(data.toUtf8());
        QJsonObject jsonObject = jsonResponse.object();
        QJsonArray jsonArray = jsonObject["datastored"].toArray();
        //qDebug()<<"[jsonparser.cpp]"<<jsonArray.size();
        foreach (const QJsonValue & value, jsonArray) {
            QJsonObject obj = value.toObject();
            database::GetInstance().urlAoa_locaor=obj["urlAoa_locaor"].toString();
            database::GetInstance().portbroker=obj["portbroker"].toString();
            database::GetInstance().urlbroker=obj["urlbroker"].toString();
            database::GetInstance().urlogdatasave=obj["urlogdatasave"].toString();
            database::GetInstance().moyglissantelength=obj["moyenneglissante"].toInt();
        }

}

/*/!\NE FONCTIONNE PAS CORRECTEMENT POUR L'INSTANT*/
/*Enregistre les data d'option dans le fichier Json sous un format lisible pour la réouverture du programme*/
void jsonparser::jsonsaver(){
    QFile file(QDir::currentPath() + "/config.json");
    if(!file.open(QIODevice::ReadWrite)) {
        //qDebug() << "[jsonparser.cpp] File open error";
    } else {
        //qDebug() <<"[jsonparser.cpp] File open! at:"<<QDir::currentPath() << "/config.json";
    }
    QJsonObject datastoredglobal;
    QJsonObject jsonObject;
        jsonObject.insert("Last open", QDateTime::currentDateTime().toString());
        jsonObject.insert("urlbroker", database::GetInstance().returnurlbroker() );
        jsonObject.insert("portbroker", database::GetInstance().returnportbroker());
        jsonObject.insert("urlAoa_locaor", database::GetInstance().returnurlAoa_locaor());
        jsonObject.insert("urlogdatasave", database::GetInstance().returnurllogdata());
        jsonObject.insert("moyenneglissante", database::GetInstance().returnmoyglissante());
    datastoredglobal.insert("datastored", jsonObject);

//Use QJsonDocument to set the json object
    QJsonDocument jsonDoc;
    jsonDoc.setObject(datastoredglobal);

//Write json to the file in text form and close the file.
    file.write(jsonDoc.toJson());
    file.close();

    //qDebug() << "[jsonparser.cpp] Write to file";
}


