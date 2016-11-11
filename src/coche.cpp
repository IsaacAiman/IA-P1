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

void coche::move(celda aux, int recorrido, ALLEGRO_BITMAP* carimg){
    if(recorrido==each_pixel_height-1){
        switch(d){
        case 2:
            coord_x++;
            break;
        case 0:
            coord_x--;
            break;
        case 1:
            coord_y--;
            break;
        case 3:
            coord_y++;
            break;
        }
    }
    if(aux.x > coord_x){
        d=2;
    }
    if(aux.x < coord_x){
        d=0;
    }

    if(aux.y > coord_y){
        d=3;
    }
    if(aux.y < coord_y){
        d=1;
    }
    if(!(recorrido==each_pixel_height-1)){
        switch(d){
        case 2:
            al_draw_scaled_rotated_bitmap(carimg, al_get_bitmap_width(carimg)/2, al_get_bitmap_height(carimg)/2,
                                      coord_x*each_pixel_width+(each_pixel_width/2)+recorrido, coord_y*each_pixel_height+(each_pixel_height/2)+50,
                                       (each_pixel_width+0.0)/al_get_bitmap_width(carimg), (each_pixel_height+0.0)/al_get_bitmap_height(carimg), (d)*(ALLEGRO_PI/2), 0);
            break;
        case 0:
            al_draw_scaled_rotated_bitmap(carimg, al_get_bitmap_width(carimg)/2, al_get_bitmap_height(carimg)/2,
                                      coord_x*each_pixel_width+(each_pixel_width/2)-recorrido, coord_y*each_pixel_height+(each_pixel_height/2)+50,
                                       (each_pixel_width+0.0)/al_get_bitmap_width(carimg), (each_pixel_height+0.0)/al_get_bitmap_height(carimg), (d)*(ALLEGRO_PI/2), 0);
            break;
        case 3:
            al_draw_scaled_rotated_bitmap(carimg, al_get_bitmap_width(carimg)/2, al_get_bitmap_height(carimg)/2,
                                      coord_x*each_pixel_width+(each_pixel_width/2), coord_y*each_pixel_height+(each_pixel_height/2)+50+recorrido,
                                       (each_pixel_width+0.0)/al_get_bitmap_width(carimg), (each_pixel_height+0.0)/al_get_bitmap_height(carimg), (d)*(ALLEGRO_PI/2), 0);
            break;
        case 1:
            al_draw_scaled_rotated_bitmap(carimg, al_get_bitmap_width(carimg)/2, al_get_bitmap_height(carimg)/2,
                                      coord_x*each_pixel_width+(each_pixel_width/2), coord_y*each_pixel_height+(each_pixel_height/2)+50-recorrido,
                                       (each_pixel_width+0.0)/al_get_bitmap_width(carimg), (each_pixel_height+0.0)/al_get_bitmap_height(carimg), (d)*(ALLEGRO_PI/2), 0);
            break;
        }
    }
}

