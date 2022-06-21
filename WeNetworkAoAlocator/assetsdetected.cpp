/*Fait par Hugo FABRE*/
#include "assetsdetected.h"
#include "database.h"
#include <QDebug>


assetsdetected::assetsdetected()
{
    listazimuth.append(0);
}

/*Cette fonction modifie l'Azimuth associé a un locator d'un asset, c'est ici que l'on fait le
  lissage par moyenne glissante avec g le nombre de valeurs pour effectuer la moyenne glissante*/
void assetsdetected::addtolist(double az){
    int g=database::GetInstance().returnmoyglissante();
    //qDebug()<<"[assetdetected.cpp] add to list";
    //qDebug()<<"[assetdetected.cpp] current listazimuth length="<<listazimuth.length();
    if(listazimuth.length()>=g){
        //qDebug()<<"[assetdetected.cpp] case >=10";
        for(int i=0;i<=g-1;i++)
        {
            //qDebug()<<"[assetdetected.cpp]For loop:"<<i<<"  "<<listazimuth.value(i);
            listazimuth.replace(i,listazimuth.value(i+1));
        }
        listazimuth.removeLast();
        azim=calcul();
        //qDebug()<<"[assetdetected.cpp]g:"<<g<<"  ";
        //qDebug()<<"[assetdetected.cpp]Azim calculer:"<<azim<<"  ";
    }
    else{
        //qDebug()<<"[assetdetected.cpp] case <10";
        listazimuth.append(az);
    }


}

/*Calcul de moyenne des g valeurs afin de sortir la moyenne glissante*/
double assetsdetected::calcul()
{
    int g=database::GetInstance().returnmoyglissante();
    double memorysumm=0;
    for(int i=0;i<=listazimuth.length();i++)
    {
        memorysumm=memorysumm+listazimuth.value(i);
    }

    return memorysumm/g;

}
