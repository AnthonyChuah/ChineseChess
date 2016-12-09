#ifndef CHARIOT_H
#define CHARIOT_H

#include "includes.h"

class Chariot : public Unit {
 public:
  Chariot();
  Chariot(int _row, int _col, bool _black, Board* _ptr);
  ~Chariot();
  bool move(const int _rowsteps, const int _colsteps); // Instantiation of pure virtual function in Unit.
  void threatRange(std::set<std::pair<int, int> >& _dangerzones); // Instantiation of pure virtual in Unit.
};

#endif
