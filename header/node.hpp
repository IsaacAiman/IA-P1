#ifndef NODO_H
#define NODO_H

#include "common.hpp"
#include <iostream>
#include <cmath>

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
  node (celda posicion, node* p, celda fin, celda inicio);
  ~node ();
  celda get_pos(void) const;
  celda get_end(void) const;
  celda get_start(void) const;
  int get_h(void) const;
  int get_g(void) const;
  int get_f(void) const;
  node* get_parent(void);
  int manhattan (celda x, celda y);
  void calcular_g(void);
  void calcular_h(void);
  void calcular_f(void);
  node operator = (node n1);

};
bool operator == (node n1,  node n2);
bool operator < ( node n1,  node n2);


#endif // NODO_H
