#include "cannon.h"

Cannon::Cannon() : Unit() {
  unit_type = CANNON;
  text_icon = "_C_";
}

Cannon::Cannon(int _row, int _col, bool _black, Board* _ptr) :
  Unit(_row, _col, _black, _ptr) {
  unit_type = CANNON;
  if (is_black) {
    text_icon = "_C_";
  } else {
    text_icon = "*C*";
  }
}

Cannon::~Cannon() {}
std::string Cannon::name() const { return "Cannon"; }

bool Cannon::move(const int _rowsteps, const int _colsteps) {
  std::set<std::pair<int, int> > range;
  threatRange(range); moveRange(range);
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

void Cannon::threatRange(std::set<std::pair<int, int> >& _dangerzones) {
  int arow, acol; bool found_obstacle;
  for (arow = row, acol = col - 1, found_obstacle = false; acol >= 0; --acol) {
    if (!found_obstacle) {
      if (cellHasUnit(arow, acol)) found_obstacle = true;
      continue;
    } else {
      if (cellHasUnit(arow, acol)) {
	if (!cellHasAlly(arow, acol))
	  _dangerzones.insert(std::make_pair(arow, acol));
	break;
      }
    }
  }
  for (arow = row, acol = col + 1, found_obstacle = false; acol < NUMCOLS; ++acol) {
    if (!found_obstacle) {
      if (cellHasUnit(arow, acol)) found_obstacle = true;
      continue;
    } else {
      if (cellHasUnit(arow, acol)) {
	if (!cellHasAlly(arow, acol))
	  _dangerzones.insert(std::make_pair(arow, acol));
	break;
      }
    }
  }
  for (arow = row + 1, acol = col, found_obstacle = false; arow < NUMROWS; ++arow) {
    if (!found_obstacle) {
      if (cellHasUnit(arow, acol)) found_obstacle = true;
      continue;
    } else {
      if (cellHasUnit(arow, acol)) {
	if (!cellHasAlly(arow, acol))
	  _dangerzones.insert(std::make_pair(arow, acol));
	break;
      }
    }
  }
  for (arow = row - 1, acol = col, found_obstacle = false; arow >= 0; --arow) {
    if (!found_obstacle) {
      if (cellHasUnit(arow, acol)) found_obstacle = true;
      continue;
    } else {
      if (cellHasUnit(arow, acol)) {
	if (!cellHasAlly(arow, acol))
	  _dangerzones.insert(std::make_pair(arow, acol));
	break;
      }
    }
  }
}

void Cannon::moveRange(std::set<std::pair<int, int> >& _dangerzones) {
  int mrow, mcol;
  for (mrow = row, mcol = col - 1; mcol >= 0; --mcol) {
    if (cellHasUnit(mrow, mcol)) {
      break;
    } else {
      _dangerzones.insert(std::make_pair(mrow, mcol));
    }
  }
  for (mrow = row, mcol = col + 1; mcol < NUMCOLS; ++mcol) {
    if (cellHasUnit(mrow, mcol)) {
      break;
    } else {
      _dangerzones.insert(std::make_pair(mrow, mcol));
    }
  }
  for (mrow = row + 1, mcol = col; mrow < NUMROWS; ++mrow) {
    if (cellHasUnit(mrow, mcol)) {
      break;
    } else {
      _dangerzones.insert(std::make_pair(mrow, mcol));
    }
  }
  for (mrow = row - 1, mcol = col; mrow >= 0; --mrow) {
    if (cellHasUnit(mrow, mcol)) {
      break;
    } else {
      _dangerzones.insert(std::make_pair(mrow, mcol));
    }
  }
}
