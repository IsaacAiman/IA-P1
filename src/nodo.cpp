#include "../header/node.hpp"


node::node (celda n, node* p, celda fin, celda inicio){

  pos =n;
  parent = p;
  end = fin;
  start = inicio;
  calcular_g();
  calcular_h();
  calcular_f();

}
node::~node (){

}
celda node::get_pos(void){

  return pos;

}
int node::get_h(void){

  return h;

}
int node::get_g(void){

  return g;

}
int node::get_f(void) {

  return f;

}
node* node::get_parent(void){

  return parent;

}

bool operator == (node n1, node n2){
  if (n1.get_f() == n2.get_f())
    return true;
  return false;
}
bool operator > (node n1, node n2){
  if (n1.get_f() > n2.get_f())
    return true;
  return false;
}
void node::calcular_g(void){

  int op1 = ((pos.y-start.y)*14) + (mahalanobis(pos,start) -(pos.y-start.y))*10;
  int op2 = ((pos.x-start.x)*14) + (mahalanobis(pos,start) -(pos.x-start.x))*10;
  if (op1<op2){
    g=op1;
  }
  else{
    g=op2;
  }
}
void node::calcular_h(void){
  
  int op1 = (pos.y-end.y*14) + (mahalanobis(pos,end) - (pos.y-end.y))*10;
  int op2 = ((pos.x-end.x)*14) + (mahalanobis(pos,end) -(pos.x-end.x))*10;
  if (op1<op2){
    g=op1;
  }
  else{
    g=op2;
  }
}

void node::calcular_f(void){

  f = g+h;
  std::cout << "f: " << f << std::endl;

}
int node::mahalanobis (celda x, celda y){

  if ((x.x-y.x)<(x.y-y.y)){
    return (x.x-y.x);
  }
  return (x.y-y.y);


}
