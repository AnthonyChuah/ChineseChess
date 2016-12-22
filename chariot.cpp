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
  if (boardptr->board[destrow][destcol] != NULL) {
    // The threatRange() function will NOT allow the murder of an ally, so no need to check for it.
    // First assess if this move puts self in check.
    if (!(Unit::assessMove(destrow, destcol))) {
      return false;
    } else {
      delete boardptr->board[destrow][destcol]; // Delete the enemy piece.
      boardptr->board[destrow][destcol] = this;
      boardptr->board[row][col] = NULL;
      row = destrow; col = destcol;
    }
  } else {
    if (!(Unit::assessMove(destrow, destcol))) {
      return false;
    } else {
      // Walk into the empty spot.
      boardptr->board[destrow][destcol] = this;
      boardptr->board[row][col] = NULL;
      row = destrow; col = destcol;
    }
  }
  return true;
}

void Chariot::threatRange(std::set<std::pair<int, int> >& _dangerzones) {
  // The "threat range" of a unit is the squares it may ATTACK into. This is used for evaluating Checks.
  int searchrow = row, searchcol = col-1;
  // Search leftwards and append coordinates which are valid for this Chariot to reach to _dangerzones.
  while (searchcol >= 0) {
    if (boardptr->board[searchrow][searchcol] != NULL) {
      if (boardptr->board[searchrow][searchcol]->colour() != is_black) {
	std::pair<int, int> coords(searchrow, searchcol);
	_dangerzones.insert(coords); // If it is of a different colour, you can move there by murdering it.
      }
      break; // The square has a blocking unit. Break the while loop.
    } // Else, it is an empty zone.
    std::pair<int, int> coords(searchrow, searchcol);
    _dangerzones.insert(coords); // Tagged this as a threat zone.
    searchcol--;
  }
  searchrow = row; searchcol = col+1; // Search rightwards.
  while (searchcol <= 7) {
    if (boardptr->board[searchrow][searchcol] != NULL) {
      if (boardptr->board[searchrow][searchcol]->colour() != is_black) {
	std::pair<int, int> coords(searchrow, searchcol);
	_dangerzones.insert(coords); // If it is of a different colour, you can move there by murdering it.
      }
      break; // The square has a blocking unit. Break the while loop.
    } // Else, it is an empty zone.
    std::pair<int, int> coords(searchrow, searchcol);
    _dangerzones.insert(coords); // Tagged this as a threat zone.
    searchcol++;
  }
  searchrow = row+1; searchcol = col; // Search upwards.
  while (searchrow <= 7) {
    if (boardptr->board[searchrow][searchcol] != NULL) {
      if (boardptr->board[searchrow][searchcol]->colour() != is_black) {
	std::pair<int, int> coords(searchrow, searchcol);
	_dangerzones.insert(coords); // If it is of a different colour, you can move there by murdering it.
      }
      break; // The square has a blocking unit. Break the while loop.
    } // Else, it is an empty zone.
    std::pair<int, int> coords(searchrow, searchcol);
    _dangerzones.insert(coords); // Tagged this as a threat zone.
    searchrow++;
  }
  searchrow = row-1; searchcol = col; // Search downwards.
  while (searchrow >= 0) {
    if (boardptr->board[searchrow][searchcol] != NULL) {
      if (boardptr->board[searchrow][searchcol]->colour() != is_black) {
	std::pair<int, int> coords(searchrow, searchcol);
	_dangerzones.insert(coords); // If it is of a different colour, you can move there by murdering it.
      }
      break; // The square has a blocking unit. Break the while loop.
    } // Else, it is an empty zone.
    std::pair<int, int> coords(searchrow, searchcol);
    _dangerzones.insert(coords); // Tagged this as a threat zone.
    searchrow--;
  }
}
