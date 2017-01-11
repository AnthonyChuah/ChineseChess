#include "elephant.h"

Elephant::Elephant() : boardptr(NULL), row(-1), col(-1), is_black(true) {
  type = ELEPHANT;
  icon = "_E_";
}

Elephant::Elephant(int _row, int _col, bool _black, Board* _ptr) :
  boardptr(_ptr), row(_row), col(_col), is_black(_black) {
  type = ELEPHANT;
  if (is_black) {
    icon = "_E_";
  } else {
    icon = "*E*";
  }
}

Elephant::~Elephant() {}
std::string Elephant::name() { return "Elephant"; }

bool Elephant::move(const int _rowsteps, const int _colsteps) {
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

bool Elephant::beforeRiver(const int _row) {
  if (colour() == BLACK) {
    return (_row <= BLACK_PAST_RIVER);
  }
  return (_row >= RED_PAST_RIVER);
}

void Elephant::threatRange(std::set<std::pair<int, int> >& _dangerzones) {
  if (cellWithinBoard(row + 1, col + 1) && !cellHasUnit(row + 1, col + 1)) {
    if (beforeRiver(row + 2) addToThreatRange(row + 2, col + 2, _dangerzones);
  }
  if (cellWithinBoard(row - 1, col - 1) && !cellHasUnit(row - 1, col - 1)) {
    if (beforeRiver(row - 2) addToThreatRange(row - 2, col - 2, _dangerzones);
  }
  if (cellWithinBoard(row + 1, col - 1) && !cellHasUnit(row + 1, col - 1)) {
    if (beforeRiver(row + 2) addToThreatRange(row + 2, col - 2, _dangerzones);
  }
  if (cellWithinBoard(row - 1, col + 1) && !cellHasUnit(row - 1, col + 1)) {
    if (beforeRiver(row - 2) addToThreatRange(row - 2, col + 2, _dangerzones);
  }
}
