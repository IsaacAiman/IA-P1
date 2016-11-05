#include "../header/coche.h"

coche::coche()
{
    coord_x=0;
    coord_y=0;
    d=0;
}

coche::coche( unsigned x, unsigned y){
    coord_x=x;
    coord_y=y;
    d=0;
}

coche::~coche()
{

}

short coche::get_x(){
    return coord_x;
}

short coche::get_y(){
    return coord_y;
}


