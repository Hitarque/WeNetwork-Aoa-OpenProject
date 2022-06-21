/*Fait par Hugo FABRE*/
#include "asset.h"

Asset::Asset()
{

}

/*Cette fonction permet de changer les valeurs de positions enregistré dans la mémoire del'Asset réel*/
void Asset::insertdatainarray(double x, double y)
{
if(memory.length()==5){
    memory.removeAt(0);
    memory.append({x,y});
}
else{
    memory.append({x,y});
}


}
