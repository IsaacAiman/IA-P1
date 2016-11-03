#ifndef COCHE_H
#define COCHE_H



#include <iostream>
#include "../header/aux_func.hpp"


class coche
{
    private:
        unsigned coord_x;
        unsigned coord_y;
        int d;
        ALLEGRO_BITMAP* coche_img;

    public:
        coche();
        coche(const char filename[],float x, float y);
        virtual ~coche();
        void coche_change_size(const char filename[],float x, float y);
        void dibujar();
        void move(int dir);

};

#endif // COCHE_H
