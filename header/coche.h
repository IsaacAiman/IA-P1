#ifndef COCHE_H
#define COCHE_H



#include <iostream>
#include "../header/aux_func.hpp"


class coche
{
    private:
        float coord_x;
        float coord_y;
        float tam_x;
        float tam_y;
        int d;
        bool dummy;
        ALLEGRO_BITMAP* coche_img;

    public:
        coche();
        coche(const char filename[],float x, float y, float pos_x, float pos_y);
        virtual ~coche();
        void coche_change_size(const char filename[],float x, float y);
        void dibujar();
        void move(int dir);

};

#endif // COCHE_H
