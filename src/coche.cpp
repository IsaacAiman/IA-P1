#include "../header/coche.h"

coche::coche()
{
    coord_x=0;
    coord_y=0;
    d=0;
    coche_img=NULL;

}

coche::coche(const char filename[], float x, float y, float pos_x, float pos_y){
    coord_x=pos_x*x;
    coord_y=pos_y*y;
    tam_x = x;
    tam_y = y;
    d=0;
    dummy = false;
    coche_change_size(filename,  x, y);
}

coche::~coche()
{
    al_destroy_bitmap(coche_img);
}

void coche::dibujar(){

    al_draw_rotated_bitmap(coche_img, tam_x/2, tam_y/2, coord_x+tam_x/2, coord_y+tam_y/2, (d)*(ALLEGRO_PI/2), 0);

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
void coche::coche_change_size(const char filename[],float x, float y){
//actualizar coordenadas

  coord_x=(coord_x/tam_x)*x;
  coord_y=(coord_y/tam_y)*y;

  tam_x = x;
  tam_y = y;
  if (dummy)
    al_destroy_bitmap(coche_img);
  coche_img=load_bitmap_at_size(filename,  x, y);
  dummy = true;

}
