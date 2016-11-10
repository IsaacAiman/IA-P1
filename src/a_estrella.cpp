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
  node start(pos_inicio, NULL, pos_final, pos_inicio);
  node end(pos_final, NULL, pos_final, pos_inicio);

  node current(pos_inicio, NULL, pos_final, pos_inicio);
  std::multiset<node>::iterator it;

  open.insert(start);
  bool salida = false;

  while(!salida){
    //std::cout << "pos: "<<current.get_pos().x <<" "<< current.get_pos().y << std::endl;
    it=open.begin();
    current = *it;
    open.erase(it);
    closed.insert(current);
    if (current == end){
      salida = true;
    }else{
      std::multiset<node> neighbours = vecinos(current);
      std::multiset<node>::iterator it_aux;
      for (it=neighbours.begin(); it!=neighbours.end(); ++it){
        if (!((vecinos(*it).size() == 0) || *closed.find(*it) == *it)){
          if ( ((*open.find(*it) == *it) && (*it < *open.find(*it))) || !(*open.find(*it) == *it) ){
            //*it es el nodo vecino.
            if ((*open.find(*it) == *it)){ //el nodo está en open.
              open.erase(*open.find(*it)); //elimina el nodo de open.
            }
            open.insert(*it); //inserta el vecino (nuevo nodo, misma posición) en open.
            //open.find(*it)->set_f(it->get_f());
          }
        }
      }
    }
  }

  std::cout << "fin del algoritmo" << std::endl;

  salida = false;
  node* padre = &current;
  while (!salida){
    std::cout << "current: "<<padre->get_pos().x <<" "<< padre->get_pos().y << std::endl;
    if (padre->get_parent() != NULL){
      std::cout << "asd" << std::endl;
        padre = padre->get_parent();
    }
    else{
      std::cout << "lll" << std::endl;
      salida = true;
    }
  }
  //std::multiset<node> contenedor = vecinos(padre);

//std::multiset<node>::iterator it;
/*
std::cout <<"multiset size: " <<contenedor.size() << std::endl;
for (it=contenedor.begin(); it!=contenedor.end(); ++it){

  std::cout << "x: " << it->get_pos().x<<" y: "<<it->get_pos().y<<std::endl;

}*/

}

std::multiset<node> a_estrella::vecinos (node vecino){

  celda v = vecino.get_pos();
  int y = v.y;
  int x = v.x;
  celda aux;
  std::multiset<node> neighbours;

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
void dibujar_camino(std::multiset<node> n){



}
