#ifndef DATABASE_H
#define DATABASE_H

#include "locator.h"
#include "asset.h"
#include <QList>
#include <QDebug>
#include <QFile>

class database
{
private:
QList<Locator> locators;
QList<Asset> assets;

QList<QList<double>> alldatafromcsv;

int numberofloctor=0;
int numberofasset=0;
int currentlocator=0;

public:

    QString urlbroker="";
    QString portbroker="";
    QString urlAoa_locaor="C:/aoa_locator/exe";
    QString urlogdatasave="";
    int moyglissantelength = 10;

    static database &GetInstance()
        {
           static database instance;
           return instance;
        }
    int returnmoyglissante(){
        return moyglissantelength;
    }
    QString returnportbroker(){
        return urlbroker;
    }

    QString returnurllogdata(){
        return urlogdatasave;
    }


    QString returnurlbroker(){
        return portbroker;
    }

    QString returnurlAoa_locaor(){
        return urlAoa_locaor;
    }



    int returncurrentlocator(){
        //qDebug()<<"[database.h]returning Locator";
        return currentlocator;
    }
    void sercurrentlocator(int i){
        //qDebug()<<"[database.h]Setting curent selected Locator";
        currentlocator = i ;
    }
    void addlocator(QString name,QString ip, double x, double y ){
        //qDebug()<<"[database.h]adding locator";
        Locator* a=new Locator();
        a->insertdata(name,ip,x,y);
        a->addnewassetdetected("","",0,0);
        locators.append(*a);
        //qDebug()<<"locator added";
        numberofloctor++;
         //qDebug()<<"locator count:" << numberofloctor;
    }

    void addassets(QString name,double x, double y, QString date){
        //qDebug()<<"[database.h]adding asset";
        Asset* a = new Asset();
        a->name=name;
        a->posx=x;
        a->posy=y;
        a->last_data=date;
        assets.append(*a);
        numberofasset++;
    }

    void setnewposasset(QString name,double x, double y){
        //qDebug()<<"[database.h]new pos asset: "<<name<<"  "<<x<<"  "<<y;
        for(int i=0;i<assets.length();i++){
            if(assets[i].name==name){
                assets[i].posx=x;
                assets[i].posy=y;
                //qDebug()<<"[database.h]Added to assets: "<<i<<"  "<<assets[i].name<<" x "<<assets[i].posx<<" y "<<assets[i].posy;
                return;

            }
        }
        //qDebug()<<"[Database.h]Pas d'asset créé a ce nom";
    }

    int findassets(QString name){
        //qDebug()<<"[database.h]Finding asset";
        int index;
        for(int i=0;i<assets.length();i++)
        {
            //qDebug()<<"[Database.h]A :"+assets[i].name;
            if(assets[i].name==name){
                index=i;
            }
        }
       return index;
    }

    Asset returnasset(int i){
        //qDebug()<<"[database.h]returning asset " <<assets[i].posx;
        return assets[i];
    }

    void modifylocator(int i,QString name,QString ip, double x, double y )
    {
        //qDebug()<<"[database.h]Modifying Locator";
       locators[i].setname(name);
       locators[i].setip(ip);
       locators[i].setposx(x);
       locators[i].setposy(y);
    }

    void modifylocatorassets(int i,QString name, QString date,double az,double ele){
       //qDebug()<<"[Database.h]Locaotr id:"<<i;
        locators[i].majassetdetected(0,name,date,az,ele);
    }

    void removelocator(int i){
        //qDebug()<<"[database.h]removing locator";
        locators.remove(i);
        numberofloctor--;
    }

    Locator returnlocator(int i){
        //qDebug()<<"[database.h]returning Locator";
        return locators.at(i);
    }
    int returnlocatornumber(){
        //qDebug()<<"[database.h]returning Locator number";
        return numberofloctor;
    }
    int returnassetnumber(){
        //qDebug()<<"[database.h]returning asset";
        return numberofasset;
    }

    int returnnumberofdatastoredinasset(){
        //qDebug()<<"[database.h]returning number of assets";
        return assets[0].memory.length();
    }

    void insertinmemoryasset(double x,double y){
        //qDebug()<<"[database.h]Inserting in memory of asset";
        assets[0].memory.append({x,y});
    };

    QList<double> returnrowmemoryasset(int row){
        //qDebug()<<"[database.h]returning memory of asset";
        return assets[0].memory[row];
    }

    int linebyline(QString path)
    {
        //qDebug()<<"[database.h]Inscribe in log ";
        QFile inputFile(path);
        if (inputFile.open(QIODevice::ReadOnly))
        {
           QTextStream in(&inputFile);
           while (!in.atEnd())
           {
              QString line = in.readLine();
              QStringList  strs=  line.split(";");
                     alldatafromcsv.append({strs[1].toDouble(),strs[2].toDouble()});
           }
           inputFile.close();
        }
        return 0;
    }


};
#endif // DATABASE_H
