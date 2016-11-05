#ifndef ENVIROMENT_H
#define ENVIROMENT_H

#include "common.hpp"
#include "map.hpp"
#include <stdio.h>

const float FPS = 30;

class enviroment
{
    public:
        enviroment(bool &error);
        virtual ~enviroment();
        void main();

    private:
        map mapa;
        ALLEGRO_DISPLAY *display = NULL;
        ALLEGRO_BITMAP *wall =NULL;
        ALLEGRO_BITMAP *end =NULL;
        ALLEGRO_BITMAP *carimg=NULL;
        ALLEGRO_BITMAP *person=NULL;
        ALLEGRO_EVENT_QUEUE *event_queue = NULL;
        ALLEGRO_TIMER *timer = NULL;
        bool car_bool;
        bool end_bool;
        int keyboard_status;

        void draw_map();
        bool events();
        void draw_text();
};

#endif // ENVIROMENT_H
