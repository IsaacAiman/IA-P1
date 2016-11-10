#include "../header/a_estrella.hpp"


a_estrella::a_estrella (map *m){
  std::cout << "w: "<<cells_width << std::endl;
  std::cout << "h: "<<cells_height << std::endl;
  mapa = m;
  pos_actual = mapa->get_pos_coche();
  std::cout << pos_actual.x <<"   "<<pos_actual.y << std::endl;
  pos_inicio = pos_actual;
  pos_final = mapa->get_pos_final();
  camino();
}

a_estrella::~a_estrella (){

}

void a_estrella::camino (void){
  node p(pos_inicio, NULL, pos_final, pos_inicio);
  std::set<node> contendor = vecinos(p);

std::set<node>::iterator it;

for (it=contendor.begin(); it!=contendor.end(); ++it){

  std::cout << "x: " << it->get_pos().x<<" y: "<<it->get_pos().y<<std::endl;

}

}

std::set<node> a_estrella::vecinos (node vecino){

  celda v = vecino.get_pos();
  int y = v.y;
  int x = v.x;
  celda aux;
  std::set<node> neighbours;

  if ((y-1)>=0){ //vecino de arriba
    aux.x = x;
    aux.y = y-1;
    if (mapa->kind_of_celda(aux)!=MURO){
      node vecino1(aux, &vecino, pos_final, pos_inicio);
      neighbours.insert(vecino1);
    }
  }

  if ((y+1)<cells_height){ //vecino de abajo
    aux.x = x;
    aux.y = y+1;
    if (mapa->kind_of_celda(aux)!=MURO){
      node vecino1(aux, &vecino, pos_final, pos_inicio);
      neighbours.insert(vecino1);
    }
  }

  if ((x-1)>=0){ //vecino de la izquierda
    aux.x = x-1;
    aux.y = y;
    if (mapa->kind_of_celda(aux)!=MURO){
      node vecino1(aux, &vecino, pos_final, pos_inicio);
      neighbours.insert(vecino1);
    }
  }

  if ((x+1)<cells_width){ //vecino de la derecha
    aux.x = x+1;
    aux.y = y;
    if (mapa->kind_of_celda(aux)!=MURO){
      node vecino1(aux, &vecino, pos_final, pos_inicio);
      neighbours.insert(vecino1);
    }
  }

  return neighbours;
}
