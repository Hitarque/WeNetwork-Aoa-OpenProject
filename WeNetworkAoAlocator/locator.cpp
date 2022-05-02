#include "locator.h"

Locator::Locator()
{
    qDebug()<<"[Locator.cpp] Nombre d'asset "<<assetsdetecteds.length();
}

void Locator::insertdata(QString na,QString i, double x,double y){
   this->posy=y;
   this->posx=x;
   this->name=na;
   this->ip=i;
   qDebug()<<"[LOCATOR.CPP]"+name<<ip<<posx<<posy;

   runpowershell();
}


void Locator::runpowershell(){
    std::ofstream file;
          file.open("test.ps1");

          std::string newArg = "-auto";
          std::string powershell;
          powershell = "cd 'E:/Activ''esaip/aoa_locator/exe/' \n";
          powershell += "Start-Process -FilePath \"aoa_locator.exe\" -ArgumentList \"-t "+ip.toStdString()+" [-m localhost[:1883]] [-f 1] [-c aoa_locator/config/]\"  ";

          file << powershell << std::endl;
          file.close();

          char buffer[128];
              std::string result = "";
              FILE* pipe = popen("powershell -ExecutionPolicy Bypass -F test.ps1", "r");
              if (!pipe) throw std::runtime_error("popen() failed!");
              try {

                  while (fgets(buffer, sizeof buffer, pipe) != NULL) {
                      result += buffer;

                  }
                  if(fgets(buffer, sizeof buffer, pipe)==NULL){
                      qDebug()<<"ERROR WITH POWERSHELLE OF "<<name<<" LOCATOR // Retry";

                   }
              } catch (...) {
                  pclose(pipe);
                  throw;
              }


     remove("test.ps1");

}

void Locator::addnewassetdetected(QString name, QString date,double az,double ele){
  assetsdetected a;
  a.name=name;
  a.date=date;
  a.azim=az;
  a.elev=ele;
  assetsdetecteds.append(a);
}


void Locator::majassetdetected(int id,QString name, QString date,double az,double ele){
qDebug()<<"[Locator.cpp] Majassetdetected";
        assetsdetecteds[id].setname(name);
        assetsdetecteds[id].setdate(date);
        assetsdetecteds[id].setaz(az);
        assetsdetecteds[id].setelev(ele);

}

int Locator::findasset(QString name)
{
    for(int i=0;i<assetsdetecteds.length();i++){
        if(assetsdetecteds[i].name==name)
        {
            return i;
        }
    }
}
int Locator::eraseall(){

}

assetsdetected Locator::returnasset(int i){

    assetsdetected a;
    a.name=assetsdetecteds[i].name;
    a.date =assetsdetecteds[i].date;
    a.azim =assetsdetecteds[i].azim;
    a.elev=assetsdetecteds[i].elev;
    //qDebug()<<"[LOCATOR.CPP]Returnung asset: "<< a.name<<" "<<a.azim<<" "<<a.elev;
    return a;
}


void Locator::setname(QString n)
{
   this->name=n;
}
void Locator::setip(QString n)
{
    this->ip=n;
}
void Locator::setposx(double n)
{
    this->posx=n;
}
void Locator::setposy(double n)
{
    this->posy=n;
}
