#ifndef GENERAL_H
#define GENERAL_H

#include "includes.h"

class General : public Unit {
 public:
  General();
  General(int _row, int _col, bool _black, Board* _ptr);
  ~General();
  std::string name() const;
  bool move(const int _rowsteps, const int _colsteps); // Instantiation of pure virtual function in Unit.
  void threatRange(std::set<std::pair<int, int> >& _dangerzones); // Instantiation of pure virtual in Unit.
  // General is a weird case: his threatRange vs an opponent General is a straight line of sight vertically.
  // Otherwise, his threatRange is a single non-diagonal step inside the Palace only.
  bool withinPalace(const int _row, const int _col);
};

#endif
