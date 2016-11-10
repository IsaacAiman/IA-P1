#include "../header/node.hpp"


node::node (celda posicion, node* p, celda fin, celda inicio){

  pos = posicion;
  parent = p;
  end = fin;
  start = inicio;
  calcular_g();
  calcular_h();
  calcular_f();

}
node::~node (){

}
celda node::get_pos(void) const{

  return pos;

}
int node::get_h(void) const{

  return h;

}
int node::get_g(void) const{

  return g;

}
int node::get_f(void) const{

  return f;

}
node* node::get_parent(void){

  return parent;

}

bool operator == ( node n1, node n2){
  if (n1.get_f() == n2.get_f())
    return true;
  return false;
}
bool operator < ( node n1, node n2){
  if (n1.get_f() < n2.get_f())
    return true;
  return false;
}
void node::calcular_g(void){

 g = manhattan(pos, start);
 std::cout << "g: " << g << std::endl;
}

void node::calcular_h(void){

  h = manhattan(pos, end);
  std::cout << "h: " << h << std::endl;

}

void node::calcular_f(void){

  f = g+h;
  std::cout << "f: " << f << std::endl;

}
int node::manhattan (celda x, celda y){

  return (abs(x.y-y.y) + abs(x.x-y.x));

}
