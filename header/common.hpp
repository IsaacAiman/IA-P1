#ifndef COMMON_H
#define COMMON_H



#include <allegro5/allegro.h>
#include "allegro5/allegro_native_dialog.h"
#include "allegro5/allegro_image.h"

#define MURO 1
#define VACIO 0
#define PERSONA 2
#define VISITADA 3

#define PONIENDOMUROS 2
#define PONIENDOPERSONAS 3
#define PONIENDOCOCHE 1
#define PONIENDOMETA 0

#define COLORCOCHE al_map_rgb(200,0,200)
#define COLORMURO al_map_rgb(0,0,200)
#define COLORVISITADO al_map_rgb(150,150,150)
#define COLORTRAYECTORIA al_map_rgb(255,0,0)
#define COLORMETA al_map_rgb(255,255,255)
#define COLORPERSONA al_map_rgb(100,255,255)

ALLEGRO_BITMAP *load_bitmap_at_size(const char *filename, int w, int h);
ALLEGRO_BITMAP* modify_size(ALLEGRO_BITMAP * origen, int width, int height);

struct celda{
    unsigned x;
    unsigned y;
};

extern int pixels_width;
extern int pixels_height;
extern unsigned cells_width;
extern unsigned cells_height;
extern unsigned obs_prob;
extern int each_pixel_width;
extern int each_pixel_height;
extern float proporcion;
extern bool from_scratch;

#endif // AUX_FUNC_H
