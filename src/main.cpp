
#include "../header/coche.h"
#include "../header/common.hpp"
#include "../header/map.hpp"
#include "../header/enviroment.hpp"

unsigned cells_width;
unsigned cells_height;
unsigned obs_prob;
int each_pixel_height;
int each_pixel_width;
float proporcion;
bool from_scratch;

int main(int argc, char **argv)
{
    if((argc<5)||(argc>5)){
        std::cerr<<"Número de argumentos incorrecto"<<std::endl<<"./coche TAM_X TAM_Y PORCENTAJE_OBSTÁCULOS\n";
        return -1;
    }

    cells_height=atoi(argv[2]);
    cells_width=atoi(argv[1]);
    obs_prob=atoi(argv[3]);
    proporcion=(cells_width+0.0)/(cells_height+0.0);
    from_scratch=atoi(argv[4]);

    if(proporcion<=1){
        pixels_height=750;
        pixels_width=(700*proporcion);
    }
    else{
        pixels_width=700;
        pixels_height=(700/proporcion)+50;
    }
    each_pixel_width=pixels_width/cells_width;
    each_pixel_height=(pixels_height-50)/cells_height;

    bool error=false;
    enviroment entorno(error);
    if(error)
        return -1;
    entorno.principal();

    return false;

    return 0;
}
