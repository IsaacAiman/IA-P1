#ifndef NODO_H
#define NODO_H

#include "common.hpp"
#include <iostream>

class node {
private:
  celda pos; //guarda la posición del nodo
  celda end; //guarda la meta
  celda start; //guarda la posición de inicio
  int h;
  int g;
  int f;
  node* parent;
public:
  node (celda n, node* p, celda fin, celda inicio);
  ~node ();
  celda get_pos(void);
  int get_h(void);
  int get_g(void);
  int get_f(void) ;
  node* get_parent(void);
  int mahalanobis (celda x, celda y);
  void calcular_g(void);
  void calcular_h(void);
  void calcular_f(void);

};
bool operator == (node n1, node n2);
bool operator > (node n1, node n2);


#endif // NODO_H
