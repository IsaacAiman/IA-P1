#ifndef A_ESTRELLA_H
#define A_ESTRELLA_H

#include "common.hpp"
#include "map.hpp"
#include "node.hpp"
#include <set>

class a_estrella {
private:
  std::set<node> open;
  std::set<node> closed;
  map* mapa;
  celda pos_actual;
  celda pos_final;


public:
  a_estrella (map *m);
  ~a_estrella ();
  void camino (void);

};

#endif // A_ESTRELLA_H
