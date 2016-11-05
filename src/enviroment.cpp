#include "../header/enviroment.hpp"

enviroment::enviroment(bool &error)
{
    car_bool=false;
    end_bool=false;
    keyboard_status=0;


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

    if (!al_install_mouse()){
      fprintf(stderr, "Fallo al instalar controlador de ratón!\n");
      error=true;
    }

    if (!al_install_keyboard()){
      fprintf(stderr, "Fallo al instalar controlador de teclado!\n");
      error=true;
    }

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
}

void enviroment::draw_map(){

    al_clear_to_color(al_map_rgb(0,0,0));
    for(unsigned i=0; i<cells_width; i++){
        for(unsigned j=0; j<cells_height; j++){
            celda aux{i,j};
            if(mapa.kind_of_celda(aux)==MURO){
                al_draw_scaled_bitmap(wall,
                0, 0, al_get_bitmap_width(wall), al_get_bitmap_height(wall),
                i*each_pixel_width, j*each_pixel_height, each_pixel_width, each_pixel_height, 0);
            }
            else if(mapa.kind_of_celda(aux)==PERSONA){
                al_draw_scaled_bitmap(person,
                0, 0, al_get_bitmap_width(person), al_get_bitmap_height(person),
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

void enviroment::principal(){
    bool keep=true;
    do{
        keep=events();
        //draw_text();
    }while(keep);
}


bool enviroment::events(){
    bool keep=true;
    ALLEGRO_EVENT ev;
    al_wait_for_event(event_queue, &ev);


    al_acknowledge_resize(display);
    if (ev.type == ALLEGRO_EVENT_DISPLAY_RESIZE){
        float w = al_get_display_width(display);
        float h = al_get_display_height(display);

        if(w!=pixels_width){
            al_resize_display(display,w,w*proporcion);
            h=w/proporcion;
        }
        else{
            al_resize_display(display,h,h);
            w=h*proporcion;
        }
        al_resize_display(display,w,h);
        each_pixel_width = w/cells_width;
        each_pixel_height =  h/cells_height;
        pixels_width=w;
        pixels_height=h;

    }

    if(ev.type == ALLEGRO_EVENT_TIMER) {
        draw_map();
    }
    else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        keep=false;
    }
    else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
        std::cout<<keyboard_status;
        if (ev.mouse.button & 1 ){
            int x = (ev.mouse.x);
            int y = (ev.mouse.y);

            unsigned obs_x = x/each_pixel_width;
            unsigned obs_y = y/each_pixel_height;
            celda aux{obs_x,obs_y};

            if(keyboard_status==PONIENDOPERSONAS){
                mapa.modify_cell(aux, PERSONA);
            }
            if(keyboard_status==PONIENDOMUROS){
                mapa.modify_cell(aux, MURO);
            }

            if ((MURO!=mapa.kind_of_celda(aux)) && !(car_bool) && keyboard_status==PONIENDOCOCHE ){
                car_bool=true;
                mapa.create_car(aux);
            }
            if ((MURO!=mapa.kind_of_celda(aux)) && !(car_bool) && keyboard_status==PONIENDOMETA){
                end_bool=true;
                mapa.create_end(aux);
            }
        }
    }
    else if(ev.type==ALLEGRO_EVENT_KEY_DOWN){
        if(ev.keyboard.keycode==ALLEGRO_KEY_M){
            keyboard_status=PONIENDOMUROS;
            std::cout<<"hi";
        }
        else if(ev.keyboard.keycode==ALLEGRO_KEY_G){
            keyboard_status=PONIENDOMETA;
        }
        else if(ev.keyboard.keycode==ALLEGRO_KEY_C){
            keyboard_status=PONIENDOCOCHE;
        }
        else if(ev.keyboard.keycode==ALLEGRO_KEY_SPACE){
            //CORRE EL ALGORITMO
        }
        else if(ev.keyboard.keycode==ALLEGRO_KEY_P){
            keyboard_status=PONIENDOPERSONAS;
        }
    }

    return keep;

}
