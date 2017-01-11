#include "general.h"

General::General() : boardptr(NULL), row(-1), col(-1), is_black(true) {
  type = GENERAL;
  icon = "_G_";
}

General::General(int _row, int _col, bool _black, Board* _ptr) :
  boardptr(_ptr), row(_row), col(_col), is_black(_black) {
  type = GENERAL;
  if (is_black) {
    icon = "_G_";
  } else {
    icon = "*G*";
  }
}

General::~General() {}
std::string General::name() { return "General"; }

bool General::withinPalace(const int _row, const int _col) {
  if (_col < 3 || _col > 5)
    return false;
  if (colour() == BLACK) {
    if (_row < 0 || _row > 2)
      return false;
  } else {
    if (_row < 7 || _row > 9)
      return false;
  }
  return true;
}

bool General::move(const int _rowsteps, const int _colsteps) {
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

void General::threatRange(std::set<std::pair<int, int> >& _dangerzones) {
  if (withinPalace(row + 1, col))
    addToThreatRange(row + 1, col);
  if (withinPalace(row - 1, col))
    addToThreatRange(row - 1, col);
  if (withinPalace(row, col + 1))
    addToThreatRange(row, col + 1);
  if (withinPalace(row, col - 1))
    addToThreatRange(row, col - 1);
  if (colour() == BLACK) {
    for (int mrow = row; mrow < NUMROWS; ++mrow) {
      if (cellHasUnit(mrow, col)) {
	if (boardptr->board[mrow][col]->name() == "General")
	  _dangerzones.insert(std::make_pair(mrow, col));
        break;
      }
    }
  } else {
    for (int mrow = row; mrow >= 0; --mrow) {
      if (cellHasUnit(mrow, col)) {
	if (boardptr->board[mrow][col]->name() == "General")
	  _dangerzones.insert(std::make_pair(mrow, col));
        break;
      }
    }
  }
}
