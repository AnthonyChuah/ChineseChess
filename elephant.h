#ifndef ELEPHANT_H
#define ELEPHANT_H

#include "includes.h"

class Elephant : public Unit {
 public:
  Elephant();
  Elephant(int _row, int _col, bool _black, Board* _ptr);
  ~Elephant();
  std::string name() const;
  bool move(const int _rowsteps, const int _colsteps); // Instantiation of pure virtual function in Unit.
  void threatRange(std::set<std::pair<int, int> >& _dangerzones); // Instantiation of pure virtual in Unit.
  bool beforeRiver(const int _row); // True if row and col specify coordinate before the river.
};

#endif
