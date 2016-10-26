#include "../header/coche.h"

coche::coche()
{
    coord_x=0;
    coord_y=0;
    d=0;
    coche_img=NULL;
}

coche::coche(char filename[], unsigned x, unsigned y){
    coord_x=x;
    coord_y=y;
    d=0;
    coche_img=load_bitmap_at_size(filename, 25, 25);
}

coche::~coche()
{
    al_destroy_bitmap(coche_img);
}

void coche::dibujar(){
    al_draw_bitmap(coche_img,coord_x,coord_y,0);
}

void coche::move(int dir){
    d=0;
    if(dir){
        d=dir;
        switch(dir){
        case 1:
            coord_y--;
            break;
        case 2:
            coord_x++;
            break;
        case 3:
            coord_y++;
            break;
        case 4:
            coord_x--;
            break;
        }
    }
}


