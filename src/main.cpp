
#include "../header/coche.h"
#include "../header/common.hpp"
#include "../header/map.hpp"
#include "../header/enviroment.hpp"

unsigned cells_width;
unsigned cells_height;
unsigned obs_prob;
int each_pixel_height;
int each_pixel_width;
float proporcion;
bool from_scratch;

int main(int argc, char **argv)
{
    if((argc<5)||(argc>5)){
        std::cerr<<"Número de argumentos incorrecto"<<std::endl<<"./coche TAM_X TAM_Y PORCENTAJE_OBSTÁCULOS\n";
        return -1;
    }

    cells_height=atoi(argv[2]);
    cells_width=atoi(argv[1]);
    obs_prob=atoi(argv[3]);
    proporcion=(cells_width+0.0)/(cells_height+0.0);
    from_scratch=atoi(argv[4]);
    std::cout<<from_scratch;

    if(proporcion<=1){
        pixels_height=500;
        pixels_width=(500*proporcion);
    }
    else{
        pixels_width=500;
        pixels_height=(500/proporcion);
    }
    each_pixel_width=pixels_width/cells_width;
    each_pixel_height=pixels_height/cells_height;

    bool error=false;
    enviroment entorno(error);
    if(error)
        return -1;
    entorno.principal();

    return false;

/*
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
    display = al_create_display(pixels_width, pixels_height);

    if(!display) {
        fprintf(stderr, "Fallo al crear la pantalla!\n");
        return -1;
    }

    al_register_event_source(event_queue , al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));


    al_clear_to_color(al_map_rgb(0,0,0));


    wall = al_load_bitmap("./images/00_0.png");
    end = al_load_bitmap("./images/00_3.png");
    carimg = al_load_bitmap("./images/00_1.png");

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
    while(1)
    {
        if(0==(count=count%25)){
            //LLAMADA AL ALGORITMO
        }
        count++;

        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);


        al_acknowledge_resize(display);
        if (ev.type == ALLEGRO_EVENT_DISPLAY_RESIZE){
            float w = al_get_display_width(display);
            float h = al_get_display_height(display);

            if(w!=pixels_width){
                al_resize_display(display,w,w);
                h=w;
            }
            else{
                al_resize_display(display,h,h);
                w=h;
            }

            each_pixel_width = w/cells_width;
            each_pixel_height =  h/cells_height;

            al_clear_to_color(al_map_rgb(0,0,0));
        }




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
                        al_draw_scaled_bitmap(wall,
                        0, 0, al_get_bitmap_width(wall), al_get_bitmap_height(wall),
                        i*each_pixel_width, j*each_pixel_height, each_pixel_width, each_pixel_height, 0);
                    }
                }
            }

            if(car_bool){
                celda aux=mapa.get_pos_coche();
                al_draw_scaled_bitmap(carimg,0, 0, al_get_bitmap_width(carimg), al_get_bitmap_height(carimg),
                aux.x*each_pixel_width, aux.y*each_pixel_height, each_pixel_width, each_pixel_height, 0);
            }

            if ((end_bool)){
                celda aux=mapa.get_pos_final();
                al_draw_scaled_bitmap(end,0, 0, al_get_bitmap_width(end), al_get_bitmap_height(end),
                aux.x*each_pixel_width, aux.y*each_pixel_height, each_pixel_width, each_pixel_height, 0);
            }

            al_flip_display();
        }
    }


    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_bitmap(wall);
    al_destroy_bitmap(end);
    al_destroy_bitmap(carimg);
    al_destroy_event_queue(event_queue);

    */
    return 0;
}
