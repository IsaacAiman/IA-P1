#include <stdio.h>
#include <allegro5/allegro.h>
#include <cstdlib>
#include <iostream>
#include "allegro5/allegro_native_dialog.h"
#include "allegro5/allegro_image.h"
#include <ctime>

const float FPS = 60;


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

  // 5. restore the previous target and clean up
    al_set_target_bitmap(prev_target);
    al_destroy_bitmap(loaded_bmp);

    return resized_bmp;
}



int main(int argc, char **argv)
{
    if((argc<4)||(argc>4)){
        std::cerr<<"Numero de argumentos incorrecto"<<std::endl<<"./coche TAM_X TAM_Y \n";
        return -1;
    }

    std::srand(time(NULL));

    const unsigned W_WIDTH=atoi(argv[1]);
    const unsigned W_HEIGHT=atoi(argv[2]);
    const unsigned OBS_POP=atoi(argv[3]);


    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_BITMAP *wall =NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
    bool redraw = true;

    bool obstaculos[W_WIDTH][W_HEIGHT];

    for(int i=0; i<W_WIDTH; i++){
        for(int j=0; j<W_HEIGHT; j++){
            obstaculos[i][j]=false;
        }
    }

    for(int i=0; i<W_WIDTH; i++){
        for(int j=0; j<W_HEIGHT; j++){
            int ran_aux= rand() % 100;
            if(ran_aux<OBS_POP)
                obstaculos[i][j]=true;
        }
    }

    if(!al_init()) {
        fprintf(stderr, "Fallo al inciiar la librería gráfica!!\n");
        return -1;
    }

    timer = al_create_timer(1.0 / FPS);
    if(!timer) {
        fprintf(stderr, "failed to create timer!\n");
        return -1;
    }

    event_queue = al_create_event_queue();
    if(!event_queue) {
        fprintf(stderr, "failed to create event_queue!\n");
        al_destroy_display(display);
        al_destroy_timer(timer);
        return -1;
    }

    if(!al_init_image_addon()) {
        al_show_native_message_box(display, "Error", "Error", "Failed to initialize al_init_image_addon!",
                                    NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return 0;
    }

    display = al_create_display(25*W_WIDTH, 25*W_HEIGHT);
    if(!display) {
        fprintf(stderr, "Fallo al crear la pantalla!\n");
        return -1;
    }

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));

    al_clear_to_color(al_map_rgb(0,0,0));

    wall = load_bitmap_at_size("./images/00_0.png", 25, 25);

    if(!wall) {
        al_show_native_message_box(display, "Error", "Error", "Failed to load image!",
                                    NULL, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(display);
        return 0;
    }

    for(int i=0; i<W_WIDTH; i++){
        for(int j=0; j<W_HEIGHT; j++){
            if(obstaculos[i][j]){
                al_draw_bitmap(wall,25*i,25*j,0);
            }
        }
    }
    al_start_timer(timer);
    al_flip_display();


    while(1)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if(ev.type == ALLEGRO_EVENT_TIMER) {
            redraw = true;
        }
        else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }

        if(redraw && al_is_event_queue_empty(event_queue)) {
            redraw = false;
            al_clear_to_color(al_map_rgb(0,0,0));
            for(int i=0; i<W_WIDTH; i++){
                for(int j=0; j<W_HEIGHT; j++){
                    if(obstaculos[i][j]){
                        al_draw_bitmap(wall,25*i,25*j,0);
                    }
                }
            }
            al_flip_display();
        }
    }


    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);

    return 0;
}
