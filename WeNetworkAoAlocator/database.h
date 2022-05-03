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
    static database &GetInstance()
        {
           static database instance;
           return instance;
        }
    int returncurrentlocator(){
        return currentlocator;
    }
    void sercurrentlocator(int i){
        currentlocator = i ;
    }
    void addlocator(QString name,QString ip, double x, double y ){
        Locator* a=new Locator();
        a->insertdata(name,ip,x,y);
        a->addnewassetdetected("","",0,0);
        locators.append(*a);
        qDebug()<<"locator added";
        numberofloctor++;
         qDebug()<<"locator count:" << numberofloctor;
    }

    void addassets(QString name,double x, double y, QString date){
        Asset* a = new Asset();
        a->name=name;
        a->posx=x;
        a->posy=y;
        a->last_data=date;
        assets.append(*a);
        numberofasset++;
    }

    void setnewposasset(QString name,double x, double y){
        for(int i=0;i<assets.length();i++){
            if(assets[i].name==name){
                assets[i].posx=x;
                assets[i].posy=y;
                return;
            }
        }
        qDebug()<<"[Database.h]Pas d'asset créé a ce nom";
    }

    int findassets(QString name){
        int index;
        for(int i=0;i<assets.length();i++)
        {
            qDebug()<<"[Database.h]A :"+assets[i].name;
            if(assets[i].name==name){
                index=i;
            }
        }
       return index;
    }

    Asset returnasset(int i){
        return assets[i];
    }

    void modifylocator(int i,QString name,QString ip, double x, double y )
    {
       locators[i].setname(name);
       locators[i].setip(ip);
       locators[i].setposx(x);
       locators[i].setposy(y);
    }

    void modifylocatorassets(int i,QString name, QString date,double az,double ele){
       qDebug()<<"[Database.h]Locaotr id:"<<i;
        locators[i].majassetdetected(0,name,date,az,ele);
    }

    void removelocator(int i){
        locators.remove(i);
        numberofloctor--;
    }

    Locator returnlocator(int i){
        return locators.at(i);
    }
    int returnlocatornumber(){
        return numberofloctor;
    }
    int returnassetnumber(){
        return numberofasset;
    }

    int returnnumberofdatastoredinasset(){
        return assets[0].memory.length();
    }

    void insertinmemoryasset(double x,double y){
        assets[0].memory.append({x,y});
    };

    QList<double> returnrowmemoryasset(int row){
        return assets[0].memory[row];
    }

    int linebyline(QString path)
    {
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
    }


};
#endif // DATABASE_H
