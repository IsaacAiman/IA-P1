#include "../header/coche.h"

coche::coche()
{
    coord_x=0;
    coord_y=0;
    d=0;
    coche_img=NULL;
    t
}

coche::coche(const char filename[], unsigned x, unsigned y, float w, float h){
    coord_x=x;
    coord_y=y;
    d=0;
    tam_w = w;
    tam_h = h;

    coche_img=load_bitmap_at_size(filename, tam_w, tam_h);
}

coche::~coche()
{
    al_destroy_bitmap(coche_img);
}

void coche::dibujar(){
    al_draw_rotated_bitmap(coche_img, 25.0/2, 25.0/2, coord_x+12.5, coord_y+12.5, (d)*(ALLEGRO_PI/2), 0);
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
