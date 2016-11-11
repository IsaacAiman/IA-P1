#include "../header/a_estrella.hpp"


a_estrella::a_estrella (map *m){
  mapa = m;
  pos_actual = mapa->get_pos_coche();
  pos_inicio = pos_actual;
  pos_final = mapa->get_pos_final();
}

a_estrella::~a_estrella (){

  for (int i = 0; i<closed.size(); i++){
    delete closed[i];
  }
  for (int i = 0; i<open.size(); i++){
    delete open[i];
  }
  mapa = NULL;
  delete path;
  closed.resize(0);
  open.resize(0);

}

bool a_estrella::camino (void){
  node *start = new node(pos_inicio, NULL, pos_final, pos_inicio);
  node *end = new node(pos_final, NULL, pos_final, pos_inicio);
  node *current = start;

  open.push_back(start);

  bool salida = false;

  while(!salida && open.size()){
    current = open[0];
    if (*current == *end){
      salida = true;
    }
    else{
      open.erase(open.begin());
      insert_closed(current);
      std::vector<node*> neighbours = vecinos(current);
      for (int i = 0; i<neighbours.size(); i++){
        insert_open(neighbours[i]);
      }

      std::sort(open.begin(), open.end()); //ordenando vector open.

    }
  }

  std::cout << "fin del algoritmo" << std::endl;
  path = current;
  return salida;
}

std::vector<node*> a_estrella::vecinos (node *vecino){

  celda v = vecino->get_pos();
  int y = v.y;
  int x = v.x;
  celda aux;
  std::vector<node*> neighbours;

  if ((y-1)>=0){ //vecino de arriba
    aux.x = x;
    aux.y = y-1;
    if (mapa->kind_of_celda(aux)!=MURO){
      node * vecino1 = new node(aux, vecino, pos_final, pos_inicio);
      neighbours.push_back(vecino1);
    }
  }

  if ((y+1)<cells_height){ //vecino de abajo
    aux.x = x;
    aux.y = y+1;
    if (mapa->kind_of_celda(aux)!=MURO ){
        node * vecino1 = new node(aux, vecino, pos_final, pos_inicio);
      neighbours.push_back(vecino1);
    }
  }

  if ((x-1)>=0){ //vecino de la izquierda
    aux.x = x-1;
    aux.y = y;
    if (mapa->kind_of_celda(aux)!=MURO){
        node * vecino1 = new node(aux, vecino, pos_final, pos_inicio);
      neighbours.push_back(vecino1);
    }
  }

  if ((x+1)<cells_width){ //vecino de la derecha
    aux.x = x+1;
    aux.y = y;
    if (mapa->kind_of_celda(aux)!=MURO){
        node * vecino1 = new node(aux, vecino, pos_final, pos_inicio);
      neighbours.push_back(vecino1);
    }
  }

  return neighbours;
}
void dibujar_camino(std::vector<node*> n){



}
bool a_estrella::in_closed(node* aux){

  for (int i = 0; i<closed.size(); i++){
    if (*closed[i]==*aux){
      return true;
    }
  }
  return false;
}

bool a_estrella::in_open(node* aux){
  for (int i = 0; i<open.size(); i++){
    if (*open[i]==*aux){
      return true;
    }
  }
  return false;
}

int a_estrella::find_open(node* aux){
  for (int i = 0; i<open.size(); i++){
    if (*open[i]==*aux){
      return i;
    }
  }
  return -1;
}
int a_estrella::find_closed(node* aux){
  for (int i = 0; i<closed.size(); i++){
    if (*closed[i]==*aux){
      return i;
    }
  }
  return -1;
}
void a_estrella::insert_closed(node* aux){
  for (int i=0; i<closed.size(); i++){
    if(*aux==*closed[i] && *aux<*closed[i]){
      closed[i]=aux;
    }
  }
  if (!in_closed(aux)){
    closed.push_back(aux);
  }
}
void a_estrella::insert_open(node* aux){

  if (in_closed(aux)){
    if (*closed[find_closed(aux)] < *aux ){
      return;
    }
  }
  for (int i=0; i<open.size(); i++){
    if(*aux==*open[i] && *aux<*open[i]){
      node *aux_ = open[i];
      open[i]=aux;
      insert_closed(aux_);
    }
  }
  if (!in_open(aux)){
    open.push_back(aux);
  }
}
std::vector<celda> a_estrella::dibujar_camino(void){

  std::vector<celda> aux;

  while(path!=NULL){
    aux.push_back(path->get_pos());
    path = path->get_parent();
  }

  return aux;
}
