#include "../header/menu.hpp"
#include <iostream>

menu::menu(void){
  display = NULL;
  event_queue = NULL;
  timer = NULL;
}

menu::~menu(void){

}

int menu::crear_menu(void){

    al_init();
    al_install_mouse();
    al_init_image_addon();
    al_init_native_dialog_addon();
    al_get_mouse_state(&state);


    img1 = al_load_bitmap("./images/menu/moral1.jpg");
    img2 = al_load_bitmap("./images/menu/moral2.jpg");
    img3 = al_load_bitmap("./images/menu/moral3.jpg");


    event_queue = al_create_event_queue();
    display = al_create_display(1029, 493);
    timer = al_create_timer(1.0 / 30);

    al_register_event_source(event_queue , al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));

    bool salida = false;
    bool redraw=true;

    al_draw_bitmap(img1,0,0,0);
    al_flip_display();
    al_start_timer(timer);
    int button;

    while(!salida){

      ALLEGRO_EVENT ev;
      al_wait_for_event(event_queue, &ev);

      if(ev.type == ALLEGRO_EVENT_TIMER)
          redraw = true;

      if(ev.type==ALLEGRO_EVENT_MOUSE_AXES){

          if((ev.mouse.x > 0  && ev.mouse.x < 515) && (ev.mouse.y > 250 && ev.mouse.y < 493)){
              if(redraw)
                  al_draw_bitmap(img2,0,0,0);
          }

          else if((ev.mouse.x > 515  && ev.mouse.x < 1029) && (ev.mouse.y > 250 && ev.mouse.y < 493)){
              if(redraw)
                  al_draw_bitmap(img3,0,0,0);
          }
          else{
              if(redraw)
                  al_draw_bitmap(img1,0,0,0);
          }
          if(redraw){
              al_flip_display();
              redraw=false;
          }
      }
      if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){

        if((ev.mouse.x > 0  && ev.mouse.x < 515) && (ev.mouse.y > 250 && ev.mouse.y < 493)){
            if(redraw){
              button = al_show_native_message_box(display,"Configuración del tablero","¿Estás seguro ?","¿Desea iniciar el tablero vacío?",NULL,ALLEGRO_MESSAGEBOX_YES_NO);
              salida = true;
            }
        }

        else if((ev.mouse.x > 515  && ev.mouse.x < 1029) && (ev.mouse.y > 250 && ev.mouse.y < 493)){
            if(redraw)
                exit (0);
          }
      }

    }
    al_destroy_bitmap(img1);
    al_destroy_bitmap(img2);
    al_destroy_bitmap(img3);
    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_event_queue(event_queue);

    return button;
}
