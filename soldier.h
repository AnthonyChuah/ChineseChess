#ifndef SOLDIER_H
#define SOLDIER_H

#include "includes.h"

class Soldier : public Unit {
 public:
  Soldier();
  Soldier(int _row, int _col, bool _black, Board* _ptr);
  ~Soldier();
  bool move(const int _rowsteps, const int _colsteps); // Instantiation of pure virtual function in Unit.
  void threatRange(std::set<std::pair<int, int> >& _dangerzones); // Instantiation of pure virtual in Unit.
};

#endif
