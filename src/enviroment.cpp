#include "../header/enviroment.hpp"

enviroment::enviroment(bool &error)
{
    car_bool=false;
    end_bool=false;
    keyboard_status=0;

    path.resize(0);


    if(!al_init()) {
        fprintf(stderr, "Fallo al inciiar la librer�a gr�fica!!\n");
        error=true;
    }

    timer = al_create_timer(1.0 / FPS);
    if(!timer) {
        fprintf(stderr, "failed to create timer!\n");
        error=true;
    }

    event_queue = al_create_event_queue();
    if(!event_queue) {
        fprintf(stderr, "failed to create event_queue!\n");
        al_destroy_display(display);
        al_destroy_timer(timer);
        error=true;
    }

    if(!al_init_image_addon()) {
        al_show_native_message_box(display, "Error", "Error", "Failed to initialize al_init_image_addon!",
                                    NULL, ALLEGRO_MESSAGEBOX_ERROR);
        error=true;
    }

    al_init_font_addon();

    if(!al_init_ttf_addon()) {
        al_show_native_message_box(display, "Error", "Error", "Failed to initialize al_init_ttf_addon!",
                                    NULL, ALLEGRO_MESSAGEBOX_ERROR);
        error=true;
    }


    if (!al_install_mouse()){
      fprintf(stderr, "Fallo al instalar controlador de ratón!\n");
      error=true;
    }

    if (!al_install_keyboard()){
      fprintf(stderr, "Fallo al instalar controlador de teclado!\n");
      error=true;
    }

    al_init_primitives_addon();

    al_set_new_display_flags(ALLEGRO_WINDOWED);
    al_set_new_display_flags(ALLEGRO_RESIZABLE);
    display = al_create_display(pixels_width, pixels_height);

    if(!display) {
        fprintf(stderr, "Fallo al crear la pantalla!\n");
        error=true;
    }

    al_register_event_source(event_queue , al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());


    al_clear_to_color(al_map_rgb(0,0,0));


    wall = al_load_bitmap("./images/00_0.png");
    end = al_load_bitmap("./images/00_3.png");
    carimg = al_load_bitmap("./images/00_1.png");
    person = al_load_bitmap("./images/00_2.png");

    fuente= al_load_ttf_font("./fonts/OpenSans-Regular.ttf", 16,0);

    al_flip_display();


    if((!wall) || (!end) || (!carimg)) {
        al_show_native_message_box(display, "Error", "Error", "Failed to load image!",
                                    NULL, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(display);
        error=true;
    }
    al_start_timer(timer);
}

enviroment::~enviroment()
{
    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_bitmap(wall);
    al_destroy_bitmap(end);
    al_destroy_bitmap(carimg);
    al_destroy_event_queue(event_queue);
    al_destroy_font(fuente);
}

void enviroment::draw_map(){

    al_clear_to_color(al_map_rgb(0,0,0));
    al_hold_bitmap_drawing(true);
    for(unsigned i=0; i<cells_width; i++){
        for(unsigned j=0; j<cells_height; j++){
            celda aux{i,j};
            if(mapa.kind_of_celda(aux)==MURO){
                al_draw_scaled_bitmap(wall,
                0, 0, al_get_bitmap_width(wall), al_get_bitmap_height(wall),
                i*each_pixel_width, j*each_pixel_height+50, each_pixel_width, each_pixel_height, 0);
            }
            else if(mapa.kind_of_celda(aux)==PERSONA){
                al_draw_scaled_bitmap(person,
                0, 0, al_get_bitmap_width(person), al_get_bitmap_height(person),
                i*each_pixel_width, j*each_pixel_height+50, each_pixel_width, each_pixel_height, 0);
            }
            else if(mapa.kind_of_celda(aux)==VISITADA){
                al_draw_filled_rectangle(aux.x*each_pixel_width, aux.y*each_pixel_height+50, each_pixel_width*aux.x+each_pixel_width, each_pixel_height*aux.y+each_pixel_height+50, COLORVISITADO);
            }
            else if(mapa.kind_of_celda(aux)==TRAYECTORIA){
                al_draw_filled_rectangle(aux.x*each_pixel_width, aux.y*each_pixel_height+50, each_pixel_width*aux.x+each_pixel_width, each_pixel_height*aux.y+each_pixel_height+50, COLORTRAYECTORIA);
            }
        }
    }

    if(car_bool){
        celda aux=mapa.get_pos_coche();
        al_draw_scaled_bitmap(carimg,0, 0, al_get_bitmap_width(carimg), al_get_bitmap_height(carimg),
        aux.x*each_pixel_width, aux.y*each_pixel_height+50, each_pixel_width, each_pixel_height, 0);
    }

    if ((end_bool)){
        celda aux=mapa.get_pos_final();
        al_draw_scaled_bitmap(end,0, 0, al_get_bitmap_width(end), al_get_bitmap_height(end),
        aux.x*each_pixel_width, aux.y*each_pixel_height+50, each_pixel_width, each_pixel_height, 0);
    }
    al_hold_bitmap_drawing(false);

}

void enviroment::principal(){
    bool keep=true;
    do{
        keep=events();
    }while(keep);
}


bool enviroment::events(){
    bool keep=true;
    ALLEGRO_EVENT ev;
    al_wait_for_event(event_queue, &ev);


    al_acknowledge_resize(display);
    if (ev.type == ALLEGRO_EVENT_DISPLAY_RESIZE){
        int x;
        int y;
        al_get_window_position(display, &x, &y);

        float w = al_get_display_width(display);
        float h = al_get_display_height(display);

        if(w!=pixels_width){
            h=(w/proporcion)+50;
        }
        else{
            w=(h-50)*proporcion;
        }
        al_resize_display(display,w,h);
        al_set_window_position(display,x,y);
        each_pixel_width = w/cells_width;
        each_pixel_height =  (h-50)/cells_height;
        pixels_width=w;
        pixels_height=h;
    }

    if(ev.type == ALLEGRO_EVENT_TIMER) {
        draw_map();
        draw_text();
        al_flip_display();
    }
    else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        keep=false;
    }
    else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
        if (ev.mouse.button & 1 ){
            int x = (ev.mouse.x);
            int y = (ev.mouse.y)-50;

            unsigned obs_x = x/each_pixel_width;
            unsigned obs_y = y/each_pixel_height;
            celda aux{obs_x,obs_y};

            if(aux.x<cells_width && aux.y<cells_height && y>=0 ){
                if(keyboard_status==PONIENDOPERSONAS){
                    mapa.modify_cell(aux, PERSONA);
                }
                if(keyboard_status==PONIENDOMUROS){
                    mapa.modify_cell(aux, MURO);
                }

                if ((MURO!=mapa.kind_of_celda(aux)) && keyboard_status==PONIENDOCOCHE ){
                    car_bool=true;
                    mapa.create_car(aux);
                }
                if ((MURO!=mapa.kind_of_celda(aux)) && keyboard_status==PONIENDOMETA){
                    end_bool=true;
                    mapa.create_end(aux);
                }
            }
        }
    }
    else if(ev.type==ALLEGRO_EVENT_KEY_DOWN){
        if(ev.keyboard.keycode==ALLEGRO_KEY_M){
            keyboard_status=PONIENDOMUROS;
        }
        else if(ev.keyboard.keycode==ALLEGRO_KEY_G){
            keyboard_status=PONIENDOMETA;
        }
        else if(ev.keyboard.keycode==ALLEGRO_KEY_C){
            keyboard_status=PONIENDOCOCHE;
        }
        else if(ev.keyboard.keycode==ALLEGRO_KEY_SPACE){
            if(car_bool){
                for(unsigned i=0; i<cells_width; i++){
                    for(unsigned j=0; j<cells_height; j++){
                        celda aux{i,j};
                        if((mapa.kind_of_celda(aux)==TRAYECTORIA)||(mapa.kind_of_celda(aux)==VISITADA)){
                            mapa.modify_cell(aux, VACIO);
                        }
                    }
                }
                a_estrella busqueda(&mapa);
                if (!busqueda.camino()){

                  al_show_native_message_box(display,"No hay solución","","Inténtelo de nuevo.",NULL,ALLEGRO_MESSAGEBOX_WARN);

                }
                path = busqueda.dibujar_camino();
                for(int i=0; i<path.size()-1;i++){
                    if(mapa.kind_of_celda(path[i])!=PERSONA){
                        mapa.modify_cell(path[i], TRAYECTORIA);
                    }
                }
            }
            else{
                al_show_native_message_box(display,"Introduzca el coche","","Intentelo de nuevo",NULL,ALLEGRO_MESSAGEBOX_WARN);
            }

        }
        else if(ev.keyboard.keycode==ALLEGRO_KEY_P){
            keyboard_status=PONIENDOPERSONAS;
        }
    }

    return keep;

}

void enviroment::draw_text(){
    al_draw_text(fuente, al_map_rgb(255,255,255), pixels_width/2, 0, ALLEGRO_ALIGN_CENTER, "Insertar: [p|g|c|m] Algoritmo: espacio");

    switch(keyboard_status){
        case PONIENDOMUROS:
            al_draw_text(fuente, al_map_rgb(255,255,255), pixels_width/2, 20, ALLEGRO_ALIGN_CENTER, "Poniendo muros");
            break;

        case PONIENDOMETA:
            al_draw_text(fuente, al_map_rgb(255,255,255), pixels_width/2, 20, ALLEGRO_ALIGN_CENTER, "Poniendo meta");
            break;

        case PONIENDOPERSONAS:
            al_draw_text(fuente, al_map_rgb(255,255,255), pixels_width/2, 20, ALLEGRO_ALIGN_CENTER, "Poniendo personas");
            break;

        case PONIENDOCOCHE:
            al_draw_text(fuente, al_map_rgb(255,255,255), pixels_width/2, 20, ALLEGRO_ALIGN_CENTER, "Poniendo el coche");
            break;
    }
}
