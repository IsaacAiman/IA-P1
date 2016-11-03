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
        float tam_w;
        float tam_h;
        ALLEGRO_BITMAP* coche_img;

    public:
        coche();
        coche(const char filename[], unsigned x, unsigned y,  float tam_x, float tam_y);
        virtual ~coche();
        void dibujar();
        void move(int dir);

};

#endif // COCHE_H
