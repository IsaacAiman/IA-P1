
#ifndef COCHE_H
#define COCHE_H



#include <iostream>
#include "../header/common.hpp"


class coche
{
    private:
        unsigned coord_x;
        unsigned coord_y;
        int d;

    public:
        coche();
        coche(unsigned x, unsigned y);
        virtual ~coche();
        short get_x();
        short get_y();
        //void move(int dir);
};

#endif // COCHE_H
