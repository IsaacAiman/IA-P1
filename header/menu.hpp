#ifndef MENU_H
#define MENU_H

#include "common.hpp"
#include <string>

class menu {
private:
  ALLEGRO_DISPLAY *display;
  ALLEGRO_EVENT ev;
  ALLEGRO_MOUSE_STATE state;
  ALLEGRO_BITMAP *img1;
  ALLEGRO_BITMAP *img2;
  ALLEGRO_BITMAP *img3;
  ALLEGRO_EVENT_QUEUE *event_queue;
  ALLEGRO_TIMER *timer;

public:
  menu (void);
  ~menu ();
  int crear_menu(void);

};
#endif // MENU_H
