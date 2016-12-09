#ifndef UNIT_H
#define UNIT_H

#include "includes.h"

class Board;

class Unit {
 public:
  Unit();
  Unit(int _row, int _col, bool _black, Board* _ptr);
  virtual ~Unit() = 0;
  // Getter functions
  std::string icon() const; // Returns the 3-character ASCII icon.
  bool colour() const; // Returns the player colour: true if black, false if red.
  int type() const; // Returns the type of the unit, 1 if Soldier, 2 if Cannon, etc. See includes.h.
  bool assessMove(const int _destrow, const int _destcol); // Verify that move is legal.
  virtual std::string name() const; // Returns the name of the unit, e.g. "Horseman", "General".
  virtual bool move(const int _rowsteps, const int _colsteps) = 0; // Pure virtual: move unit.
  virtual void threatRange(std::set<std::pair<int, int> >& _dangerzones) = 0; // Pure virtual: accumulate the
  // set of coordinates which are within the strike-range of the units of a given player.
 protected:
  Board* boardptr;
  int row;
  int col;
  bool is_black; // true for black, false for red.
  int unit_type; // See includes.h for which units are mapped to which numbers.
  std::string unit_name; // Name of the unit.
  std::string text_icon; // 3-character icon representing the unit.
};

#endif
