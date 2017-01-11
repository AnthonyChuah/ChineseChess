#include "chariot.h"

Chariot::Chariot() : boardptr(NULL), row(-1), col(-1), is_black(true) {
  type = CHARIOT;
  icon = "_R_";
}

Chariot::Chariot(int _row, int _col, bool _black, Board* _ptr) :
  boardptr(_ptr), row(_row), col(_col), is_black(_black) {
  type = CHARIOT;
  if (is_black) {
    icon = "_R_";
  } else {
    icon = "*R*";
  }
}

Chariot::~Chariot() {}
std::string Chariot::name() { return "Chariot"; }

bool Chariot::move(const int _rowsteps, const int _colsteps) {
  std::set<std::pair<int, int> > range;
  threatRange(range);
  int destrow = row + _rowsteps; int destcol = col + _colsteps;
  std::pair<int, int> dest(destrow, destcol);
  std::set<std::pair<int, int> >::iterator it = range.find(dest);
  if (it == range.end())
    return false;
  // Else, found a movement destination within the range of the rook.
  if (cellHasUnit(destrow, destcol)) {
    // The threatRange() function will NOT allow the murder of an ally, so no need to check for it.
    if (!(assessMove(destrow, destcol))) {
      return false;
    } else {
      Unit* victim = occupyCell(destrow, destcol);
      delete victim; // Delete the enemy piece.
    }
  } else {
    // Else, the target cell has no unit.
    if (!(assessMove(destrow, destcol))) {
      return false;
    } else {
      occupyCell(destrow, destcol);
    }
  }
  return true;
}

void Chariot::threatRange(std::set<std::pair<int, int> >& _dangerzones) {
  // The "threat range" of a unit is the squares it may ATTACK into. This is used for evaluating Checks.
  int searchrow, searchcol;
  // Search leftwards and append coordinates which are valid for this Chariot to reach to _dangerzones.
  searchrow = row; searchcol = col-1;
  while (searchcol >= 0) {
    if (cellHasUnit(searchrow, searchcol)) {
      if (!cellHasAlly(searchrow, searchcol)) {
	_dangerzones.insert(std::make_pair(searchrow, searchcol));
      }
      break; // The square has a blocking unit. Break the while loop.
    } else {
      _dangerzones.insert(std::make_pair(searchrow, searchcol));
      searchcol--;
    }
  }
  searchrow = row; searchcol = col+1; // Search rightwards.
  while (searchcol < NUMCOLS) {
    if (cellHasUnit(searchrow, searchcol)) {
      if (!cellHasAlly(searchrow, searchcol)) {
	_dangerzones.insert(std::make_pair(searchrow, searchcol));
      }
      break; // The square has a blocking unit. Break the while loop.
    } else {
      _dangerzones.insert(std::make_pair(searchrow, searchcol));
      searchcol++;
    }
  }
  searchrow = row+1; searchcol = col; // Search downwards.
  while (searchrow <= 9) {
    if (cellHasUnit(searchrow, searchcol)) {
      if (!cellHasAlly(searchrow, searchcol)) {
	_dangerzones.insert(std::make_pair(searchrow, searchcol));
      }
      break; // The square has a blocking unit. Break the while loop.
    } else {
      _dangerzones.insert(std::make_pair(searchrow, searchcol));
      searchrow++;
    }
  }
  searchrow = row-1; searchcol = col; // Search upwards.
  while (searchrow >= 0) {
    if (cellHasUnit(searchrow, searchcol)) {
      if (!cellHasAlly(searchrow, searchcol)) {
	_dangerzones.insert(std::make_pair(searchrow, searchcol));
      }
      break; // The square has a blocking unit. Break the while loop.
    } else {
      _dangerzones.insert(std::make_pair(searchrow, searchcol));
      searchrow--;
    }
  }
}
