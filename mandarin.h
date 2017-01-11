#ifndef MANDARIN_H
#define MANDARIN_H

#include "includes.h"

class Mandarin : public Unit {
 public:
  Mandarin();
  Mandarin(int _row, int _col, bool _black, Board* _ptr);
  ~Mandarin();
  std::string name() const;
  bool move(const int _rowsteps, const int _colsteps); // Instantiation of pure virtual function in Unit.
  void threatRange(std::set<std::pair<int, int> >& _dangerzones); // Instantiation of pure virtual in Unit.
  bool withinPalace(const int _row, const int _col);
};

#endif
