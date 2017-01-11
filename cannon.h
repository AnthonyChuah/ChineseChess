#ifndef CANNON_H
#define CANNON_H

#include "includes.h"

class Cannon : public Unit {
 public:
  Cannon();
  Cannon(int _row, int _col, bool _black, Board* _ptr);
  ~Cannon();
  std::string name() const;
  bool move(const int _rowsteps, const int _colsteps); // Instantiation of pure virtual in Unit.
  void threatRange(std::set<std::pair<int, int> >& _dangerzones); // Instantiation of pure virtual in Unit.
  // Note: Cannon's strike range differs from its move range.
  // Hence, move function does not borrow code from threatRange function.
  void moveRange(std::set<std::pair<int, int> >& _dangerzones);
};

#endif
