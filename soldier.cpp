#include "soldier.h"

Soldier::Soldier() : Unit() {
  unit_type = SOLDIER;
  text_icon = "_S_";
}

Soldier::Soldier(int _row, int _col, bool _black, Board* _ptr) :
  Unit(_row, _col, _black, _ptr) {
  unit_type = SOLDIER;
  if (is_black) {
    text_icon = "_S_";
  } else {
    text_icon = "*S*";
  }
}

Soldier::~Soldier() {}
std::string Soldier::name() const { return "Soldier"; }

bool Soldier::move(const int _rowsteps, const int _colsteps) {
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

void Soldier::threatRange(std::set<std::pair<int, int> >& _dangerzones) {
  if (colour() == BLACK) {
    addToThreatRange(row + 1, col, _dangerzones); // If it's black you can attack downwards.
  } else {
    addToThreatRange(row - 1, col, _dangerzones); // If it's red you can attack upwards.
  }
  if (!beforeRiver(row)) {
    addToThreatRange(row, col - 1, _dangerzones);
    addToThreatRange(row, col + 1, _dangerzones);
  }
}

bool Soldier::beforeRiver(const int _row) {
  if (colour() == BLACK) {
    return (_row <= BLACK_PAST_RIVER);
  }
  return (_row >= RED_PAST_RIVER);
}
