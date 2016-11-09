#ifndef ENVIROMENT_H
#define ENVIROMENT_H

#include "common.hpp"
#include "map.hpp"
#include "node.hpp"
#include <stdio.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>


const float FPS = 30;

class enviroment
{
    public:
        enviroment(bool &error);
        virtual ~enviroment();
        void principal();

    private:
        map mapa;
        ALLEGRO_DISPLAY *display = NULL;
        ALLEGRO_BITMAP *wall =NULL;
        ALLEGRO_BITMAP *end =NULL;
        ALLEGRO_BITMAP *carimg=NULL;
        ALLEGRO_BITMAP *person=NULL;
        ALLEGRO_EVENT_QUEUE *event_queue = NULL;
        ALLEGRO_TIMER *timer = NULL;
        ALLEGRO_FONT *fuente =NULL;

        bool primitivas;
        bool car_bool;
        bool end_bool;

        int keyboard_status;

        void draw_map();
        bool events();
        void draw_text();
};

#endif // ENVIROMENT_H
