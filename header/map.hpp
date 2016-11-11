#ifndef MAP_H
#define MAP_H

#include "common.hpp"
#include "coche.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

class map
{
    public:
        map();
        virtual ~map();
        celda get_pos_coche();
        celda get_pos_final();
        unsigned kind_of_celda(celda aux);
        void modify_cell(celda aux, short kind);
        void create_car(celda x);
        void create_end(celda x);
        void move_car (celda aux, int recorrido, ALLEGRO_BITMAP* imgcoche );

    private:
        short ** cells;
        coche * car;
        celda * final;
};

#endif // MAP_H
