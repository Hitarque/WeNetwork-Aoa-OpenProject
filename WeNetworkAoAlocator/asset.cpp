#include "asset.h"

Asset::Asset()
{

}

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
