#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include "../header/aux_func.hpp"
#include "../header/coche.h"

const float FPS = 30;

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
    ALLEGRO_BITMAP *end =NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
    bool redraw = true;
    coche * car = NULL;
    int x_end=-1;
    int y_end=-1;
    bool car_bool=false;
    bool end_bool=false;

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
        fprintf(stderr, "Fallo al inciiar la librer�a gr�fica!!\n");
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

    if (!al_install_mouse()){
      fprintf(stderr, "Fallo al instalar controlador de ratón!\n");
      return -1;
    }

    display = al_create_display(25*W_WIDTH, 25*W_HEIGHT);
    if(!display) {
        fprintf(stderr, "Fallo al crear la pantalla!\n");
        return -1;
    }

    al_register_event_source(event_queue , al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));


    al_clear_to_color(al_map_rgb(0,0,0));


    wall = load_bitmap_at_size("./images/00_0.png", 25, 25);
    end = load_bitmap_at_size("./images/00_3.png", 25, 25);

    if((!wall) || (!end)) {
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

    int count=0;
    int current_direction=0;
    while(1)
    {
        if(0==(count=count%25)){
            //LLAMADA AL ALGORITMO
        }
        count++;

        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if(ev.type == ALLEGRO_EVENT_TIMER) {
            redraw = true;
        }
        else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }
        if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {

            if (ev.mouse.button & 1 ){
                int x = (ev.mouse.x/25)*25;
                int y= (ev.mouse.y/25)*25;


                if (!obstaculos[x/25][y/25] && car_bool && !end_bool){
                    end_bool=true;
                    x_end = x;
                    y_end = y;
                }
                if (!obstaculos[x/25][y/25] && !car_bool){
                    car_bool=true;
                    car = new coche("./images/00_1.png", x, y);
                }
            }
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
            if(car){
                car->move(current_direction);
                car->dibujar();
            }

            if ((end_bool)&&(x_end>=0)&&(y_end>=0))
                al_draw_bitmap(end,x_end,y_end,0);//dibujar cochecito.


            al_flip_display();
        }
    }


    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_bitmap(wall);
    al_destroy_bitmap(end);
    al_destroy_event_queue(event_queue);

    return 0;
}
