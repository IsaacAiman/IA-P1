#include "../header/map.hpp"

map::map()
{

    cells=new short*[cells_width];
    for(unsigned i=0; i<cells_width; i++){
        cells[i]=new short[cells_height];
    }


    for(unsigned i=0; i<cells_width; i++){
        for(unsigned j=0; j<cells_height; j++){
            cells[i][j]=VACIO;
        }
    }


    std::srand(time(NULL));
    if(!from_scratch)
        for(unsigned i=0; i<cells_width; i++){
            for(unsigned j=0; j<cells_height; j++){
                unsigned ran_aux = rand() % 100;
                if(ran_aux<obs_prob)
                    cells[i][j]=MURO;
            }
        }

    car=NULL;
    final=NULL;
}

map::~map()
{
    for (unsigned i = 0; i < cells_width; ++i)
        delete [] cells[i];
    delete [] cells;

    if(car){
        delete car;
    }

    if(final){
        delete final;
    }
}

celda map::get_pos_coche(){
    celda aux;
    aux.x=car->get_x();
    aux.y=car->get_y();
    return aux;
}

celda map::get_pos_final(){
    celda aux;
    aux.x=final->x;
    aux.y=final->y;
    return aux;
}

unsigned map::kind_of_celda(celda aux){
    return cells[aux.x][aux.y];
}

void map::modify_cell(celda aux, short kind){
    cells[aux.x][aux.y]=kind;
}

void map::create_car(celda x){
    car = new coche(x.x, x.y);
}

void map::create_end(celda x){
    final= new celda;
    final->x=x.x;
    final->y=x.y;
}




