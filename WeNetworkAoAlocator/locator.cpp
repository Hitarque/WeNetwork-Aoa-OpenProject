/*Fait par Hugo FABRE*/
#include "locator.h"
#include "database.h"

Locator::Locator()
{
    //qDebug()<<"[Locator.cpp] Nombre d'asset "<<assetsdetecteds.length();
}

/*insertion de la position x et y ainsi que le nom et l'ip d'un locator, lorsque ces data sont entré il run la méthode runpowershell() qui lance le programme
situé dans le dossier aoa_locator qui permet la communication entre le locator et le broker MQTT*/
void Locator::insertdata(QString na,QString i, double x,double y){
   this->posy=y;
   this->posx=x;
   this->name=na;
   this->ip=i;
   //qDebug()<<"[LOCATOR.CPP]"+name<<ip<<posx<<posy;

   runpowershell();
}


/*Run un script shell qui lance le fichier .exe situé a l'emplacement indiqué par l'uilisateur. Ce .exe permet la communication avec le locator et le logiciel au travers
d'un broker mqtt.
Le .exe est un code d'exemple proposé par Silicon labs*/
void Locator::runpowershell(){
    std::ofstream file;
          file.open("test.ps1");

          std::string newArg = "-auto";
          std::string powershell;
          powershell = "cd '"+database::GetInstance().returnurlAoa_locaor().toStdString()+"' \n";
          powershell += "Start-Process -FilePath \"aoa_locator.exe\" -ArgumentList \"-t "+ip.toStdString()+" [-m "+database::GetInstance().returnurlbroker().toStdString()+"[:"+database::GetInstance().returnportbroker().toStdString()+"]] [-f 1] [-c aoa_locator/config/]\"  ";

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
                      //qDebug()<<"ERROR WITH POWERSHELLE OF "<<name<<" LOCATOR // Retry";

                   }
              } catch (...) {
                  pclose(pipe);
                  throw;
              }


     remove("test.ps1");

}

/*Créer un asset assigné a ce locator dans un liste des asset connu, il definir le nom, quand, azim et elev associé a ce nouvel asset*/
void Locator::addnewassetdetected(QString name, QString date,double az,double ele){
  assetsdetected a;
  a.name=name;
  a.date=date;
  a.azim=az;
  a.elev=ele;
  assetsdetecteds.append(a);
  //qDebug()<<"[Locator.cpp] Add new asset:"<<name;
}

/*Mise a jour d'un asset précédement créer afin de definir de novelles valeurs (azim, elev principalement)*/
void Locator::majassetdetected(int id,QString name, QString date,double az,double ele){
//qDebug()<<"[Locator.cpp] Majassetdetected"<<name<<" "<<az<<" "<<ele;
        assetsdetecteds[id].addtolist(az);
        //assetsdetecteds[id].setname(name);
        //assetsdetecteds[id].setdate(date);
        //assetsdetecteds[id].setaz(az);
        assetsdetecteds[id].setelev(ele);

}

/*Return le numéro d'index de l'asset correspondant au nom demandé en entré*/
int Locator::findasset(QString name)
{
    for(int i=0;i<assetsdetecteds.length();i++){
        if(assetsdetecteds[i].name==name)
        {
            return i;
        }
    }
}

/*Nothing*/
int Locator::eraseall(){

}

/*Return un asset complet en fonction de l'index d'entré*/
assetsdetected Locator::returnasset(int i){

    assetsdetected a;
    a.name=assetsdetecteds[i].name;
    a.date =assetsdetecteds[i].date;
    a.azim =assetsdetecteds[i].azim;
    a.elev=assetsdetecteds[i].elev;
    ////qDebug()<<"[LOCATOR.CPP]Returnung asset: "<< a.name<<" "<<a.azim<<" "<<a.elev;
    return a;
}

/*Setter du name*/
void Locator::setname(QString n)
{
   this->name=n;
}
/*Setter de l'Ip*/
void Locator::setip(QString n)
{
    this->ip=n;
}
/*Setter de pos x*/
void Locator::setposx(double n)
{
    this->posx=n;
}
/*Setter de pos y*/
void Locator::setposy(double n)
{
    this->posy=n;
}
