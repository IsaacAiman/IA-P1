#ifndef COMMON_H
#define COMMON_H



#include <allegro5/allegro.h>
#include "allegro5/allegro_native_dialog.h"
#include "allegro5/allegro_image.h"

#define MURO 1
#define VACIO 0
#define PERSONA 2


ALLEGRO_BITMAP *load_bitmap_at_size(const char *filename, int w, int h);

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

#endif // AUX_FUNC_H
