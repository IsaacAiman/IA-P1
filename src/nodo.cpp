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
celda node::get_end(void) const{

  return end;

}
celda node::get_start(void) const{

  return start;

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

bool operator == ( node n1, node n2){ //dos nodos son iguales si están en la misma posición
  if ((n1.get_pos().x == n2.get_pos().x) && (n1.get_pos().y == n2.get_pos().y))
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
node node::operator = (node n1){

  pos = n1.get_pos();
  end = n1.get_end();
  start = n1.get_start();
  h = n1.get_h();
  g = n1.get_g();
  f = n1.get_f();
  parent = get_parent();

  std::cout << "asdad" << std::endl;
  return *this;
}
