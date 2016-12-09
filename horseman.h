#ifndef HORSEMAN_H
#define HORSEMAN_H

#include "includes.h"

class Horseman : public Unit {
 public:
  Horseman();
  Horseman(int _row, int _col, bool _black, Board* _ptr);
  ~Horseman();
  bool move(const int _rowsteps, const int _colsteps); // Instantiation of pure virtual function in Unit.
  void threatRange(std::set<std::pair<int, int> >& _dangerzones); // Instantiation of pure virtual in Unit.
};

#endif
