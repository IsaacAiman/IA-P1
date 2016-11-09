#include "../header/common.hpp"

ALLEGRO_BITMAP *load_bitmap_at_size(const char *filename, int w, int h)
{
    ALLEGRO_BITMAP *resized_bmp, *loaded_bmp, *prev_target;

    resized_bmp = al_create_bitmap(w, h);
    if (!resized_bmp) return NULL;

    loaded_bmp = al_load_bitmap(filename);
    if (!loaded_bmp)
    {
        al_destroy_bitmap(resized_bmp);
        return NULL;
    }

    prev_target = al_get_target_bitmap();
    al_set_target_bitmap(resized_bmp);

    al_draw_scaled_bitmap(loaded_bmp,
        0, 0,                                // source origin
        al_get_bitmap_width(loaded_bmp),     // source width
        al_get_bitmap_height(loaded_bmp),    // source height
        0, 0,                                // target origin
        w, h,                                // target dimensions
        0                                    // flags
    );

    al_set_target_bitmap(prev_target);
    al_destroy_bitmap(loaded_bmp);

    return resized_bmp;
}

ALLEGRO_BITMAP * modify_size(ALLEGRO_BITMAP * origen, int width, int height){

    ALLEGRO_BITMAP * prev_target = al_get_target_bitmap();
    ALLEGRO_BITMAP* destino= NULL;

    destino = al_create_bitmap(width, height);

    al_set_target_bitmap(destino);

    al_draw_scaled_bitmap(origen,
        0, 0,
        al_get_bitmap_width(origen),
        al_get_bitmap_height(origen),
        0, 0,
        width, height,
        0
    );
    al_set_target_bitmap(prev_target);
    return destino;
}

int pixels_width=500;
int pixels_height=500;
