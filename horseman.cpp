#include "horseman.h"

Horseman::Horseman() : Unit() {
  unit_type = HORSEMAN;
  text_icon = "_H_";
}

Horseman::Horseman(int _row, int _col, bool _black, Board* _ptr) :
  Unit(_row, _col, _black, _ptr) {
  unit_type = HORSEMAN;
  if (is_black) {
    text_icon = "_H_";
  } else {
    text_icon = "*H*";
  }
}

Horseman::~Horseman() {}
std::string Horseman::name() const { return "Horseman"; }

bool Horseman::move(const int _rowsteps, const int _colsteps) {
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

void Horseman::threatRange(std::set<std::pair<int, int> >& _dangerzones) {
  // Lazy-evaluation should short-circuit the conditional, so no potential segfault.
  if (cellWithinBoard(row + 1, col) && !cellHasUnit(row + 1, col)) {
    addToThreatRange(row + 2, col - 1, _dangerzones);
    addToThreatRange(row + 2, col + 1, _dangerzones);
  }
  if (cellWithinBoard(row - 1, col) && !cellHasUnit(row - 1, col)) {
    addToThreatRange(row - 2, col - 1, _dangerzones);
    addToThreatRange(row - 2, col + 1, _dangerzones);
  }
  if (cellWithinBoard(row, col + 1) && !cellHasUnit(row, col + 1)) {
    addToThreatRange(row - 1, col + 2, _dangerzones);
    addToThreatRange(row + 1, col + 2, _dangerzones); 
  }
  if (cellWithinBoard(row, col - 1) && !cellHasUnit(row, col - 1)) {
    addToThreatRange(row - 1, col - 2, _dangerzones);
    addToThreatRange(row + 1, col - 2, _dangerzones);
  }
}
