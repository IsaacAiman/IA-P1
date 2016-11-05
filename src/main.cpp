#include <stdio.h>

#include "../header/coche.h"
#include "../header/common.hpp"
#include "../header/map.hpp"

const float FPS = 30;
unsigned cells_width;
unsigned cells_height;
unsigned obs_prob;

int main(int argc, char **argv)
{
    if((argc<4)||(argc>4)){
        std::cerr<<"Número de argumentos incorrecto"<<std::endl<<"./coche TAM_X TAM_Y PORCENTAJE_OBSTÁCULOS\n";
        return -1;
    }


    cells_height=atoi(argv[1]);
    cells_width=atoi(argv[2]);
    std::cout<<cells_width;
    obs_prob=atoi(argv[3]);

    int each_pixel_width=pixels_width/cells_width;
    int each_pixel_height=pixels_height/cells_height;

    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_BITMAP *wall =NULL;
    ALLEGRO_BITMAP *end =NULL;
    ALLEGRO_BITMAP *carimg=NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
    bool redraw = true;
    bool car_bool=false;
    bool end_bool=false;

    map mapa;



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

    al_set_new_display_flags(ALLEGRO_WINDOWED);
    al_set_new_display_flags(ALLEGRO_RESIZABLE);
    display = al_create_display(500, 500);

    if(!display) {
        fprintf(stderr, "Fallo al crear la pantalla!\n");
        return -1;
    }

    al_register_event_source(event_queue , al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));


    al_clear_to_color(al_map_rgb(0,0,0));


    wall = load_bitmap_at_size("./images/00_0.png", each_pixel_width, each_pixel_height);
    end = load_bitmap_at_size("./images/00_3.png", each_pixel_width, each_pixel_height);
    carimg = load_bitmap_at_size("./images/00_1.png", each_pixel_width, each_pixel_height);

    if((!wall) || (!end)) {
        al_show_native_message_box(display, "Error", "Error", "Failed to load image!",
                                    NULL, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(display);
        return 0;
    }

    for(unsigned i=0; i<cells_width; i++){
        for(unsigned j=0; j<cells_height; j++){
            celda aux;
            aux.x=i;
            aux.y=j;
            if(mapa.kind_of_celda(aux)==MURO){
                al_draw_bitmap(wall,each_pixel_width*i,each_pixel_height*j,0);
            }
        }
    }

    al_start_timer(timer);
    al_flip_display();

    int count=0;
    int current_direction=2;
    while(1)
    {
        if(0==(count=count%25)){
            //LLAMADA AL ALGORITMO
        }
        count++;

        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        /*
        al_acknowledge_resize(display);
        if (ev.type == ALLEGRO_EVENT_DISPLAY_RESIZE){
          float w = al_get_display_width(display);
          float h = al_get_display_height(display);

          tam_w = w/W_WIDTH;
          tam_h =  h/W_HEIGHT;
          al_destroy_bitmap(wall);
          al_destroy_bitmap(end);
          wall = load_bitmap_at_size("./images/00_0.png", tam_w, tam_h);
          end = load_bitmap_at_size("./images/00_3.png",  tam_w, tam_h);
          if (car_bool)
            car->coche_change_size("./images/00_1.png", tam_w, tam_h);
        }

        */


        if(ev.type == ALLEGRO_EVENT_TIMER) {
            redraw = true;
        }
        else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }
        if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {

            if (ev.mouse.button & 1 ){
                int x = (ev.mouse.x);
                int y = (ev.mouse.y);

                unsigned obs_x = x/each_pixel_width;
                unsigned obs_y = y/each_pixel_height;
                celda aux{obs_x,obs_y};

                if ((MURO!=mapa.kind_of_celda(aux)) && end_bool && !car_bool){
                    car_bool=true;
                    mapa.create_car(aux);
                }
                if ((MURO!=mapa.kind_of_celda(aux)) && !(car_bool)){
                    end_bool=true;
                    mapa.create_end(aux);
                }
            }
        }

        if(redraw && al_is_event_queue_empty(event_queue)) {
            redraw = false;
            al_clear_to_color(al_map_rgb(0,0,0));
            for(unsigned i=0; i<cells_width; i++){
                for(unsigned j=0; j<cells_height; j++){
                    celda aux;
                    aux.x=i;
                    aux.y=j;
                    if(mapa.kind_of_celda(aux)==MURO){
                        al_draw_bitmap(wall,each_pixel_width*i,each_pixel_height*j,0);
                    }
                }
            }

            if(car_bool){
                celda aux=mapa.get_pos_coche();
                al_draw_bitmap(carimg,aux.x*each_pixel_width,aux.y*each_pixel_height,0);
            }

            if ((end_bool)){
                celda aux=mapa.get_pos_final();
                al_draw_bitmap(end,aux.x*each_pixel_width,aux.y*each_pixel_height,0);
            }

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
