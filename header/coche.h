#ifndef COCHE_H
#define COCHE_H



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
        coche(char filename[], unsigned x, unsigned y);
        virtual ~coche();
        void dibujar();

};

#endif // COCHE_H
