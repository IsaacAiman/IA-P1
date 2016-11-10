#ifndef A_ESTRELLA_H
#define A_ESTRELLA_H

#include "common.hpp"
#include "map.hpp"
#include "node.hpp"
#include "iostream"
#include <set>

class a_estrella {
private:
  celda pos_inicio;
  std::multiset<node> open;
  std::multiset<node> closed;
  map* mapa;
  celda pos_actual;
  celda pos_final;
  //node current;

public:
  a_estrella (map *m);
  ~a_estrella ();
  void camino (void);
  std::multiset<node> vecinos(node vecino); //calcula los vecinos
  void dibujar_camino(std::multiset<node> n);
};

#endif // A_ESTRELLA_H
