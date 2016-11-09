#include "../header/a_estrella.hpp"


a_estrella::a_estrella (map *m){

  mapa = m;
  pos_actual = mapa->get_pos_coche();
  pos_final = mapa->get_pos_final();

}
a_estrella::~a_estrella (){

}
void a_estrella::camino (void){

}
