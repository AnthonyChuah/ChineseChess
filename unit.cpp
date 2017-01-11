#include "includes.h"

Unit::Unit() : boardptr(NULL), row(-1), col(-1), is_black(true) {
  unit_type = UNIT;
  icon = "_U_";
}

Unit::Unit(int _row, int _col, bool _black, Board* _ptr) :
  boardptr(_ptr), row(_row), col(_col), is_black(_black) {
  unit_type = UNIT;
  if (is_black) {
    icon = "_U_";
  } else {
    icon = "*U*";
  }
}

Unit::~Unit() {}

std::string Unit::icon() { return text_icon; }

bool Unit::colour() { return is_black; }

int Unit::type() { return unit_type; }

std::string Unit::name() { return "Unit"; }

bool Unit::assessMove(const int _destrow, const int _destcol) {
  // Record the current row and col.
  int my_row = row, my_col = col;
  // Check if the destination has a unit. If so, make a temporary pointer to it.
  Unit* temp_ptr = NULL;
  if (boardptr->board[_destrow][_destcol] != NULL) {
    temp_ptr = boardptr->board[_destrow][_destcol];
  }
  // Move this unit into place, then assess if this places the unit's General in check.
  boardptr->board[_destrow][_destcol] = this;
  boardptr->board[my_row][my_col] = NULL;
  row = _destrow; col = _destcol;
  bool checkself = false;
  checkself = boardptr->assessCheck(is_black);
  // Revert the move. If you do check yourself, return false for an invalid move. Else, valid.
  boardptr->board[my_row][my_col] = this;
  if (temp_ptr == NULL) {
    boardptr->board[_destrow][_destcol] = NULL;
  } else {
    boardptr->board[_destrow][_destcol] = temp_ptr;
  }
  row = my_row; col = my_col;
  return (!checkself);
}

bool Unit::cellHasUnit(const int _row, const int _col) {
  return (boardptr->board[_row][_col] != NULL);
}

bool Unit::cellHasAlly(const int _row, const int _col) {
  return (boardptr->board[_row][_col]->colour() == is_black);
}

bool Unit::cellWithinBoard(const int _row, const int _col) {
  return (_row >= 0 && _row < NUMROWS && _col >= 0 && _col < NUMCOLS);
}

Unit* Unit::occupyCell(const int _row, const int _col) {
  Unit* temp_ptr = NULL;
  if (boardptr->board[_row][_col] != NULL) {
    temp_ptr = boardptr->board[_destrow][_destcol];
  }
  int prev_row = row, prev_col = col;
  boardptr->board[_row][_col] = this;
  row = _row; col = _col;
  boardptr->board[prev_row][prev_col] = NULL;
  return temp_ptr;
}

void Unit::addToThreatRange(int _row, int _col, std::set<std::pair<int, int> >& _dangerzones) {
  if (cellWithinBoard(_row, _col)) {
    if (cellHasUnit(_row, _col)) {
      if (!cellHasAlly(_row, _col)) {
	_dangerzones.insert(std::make_pair(_row, _col));
      }
    } else {
      _dangerzones.insert(std::make_pair(_row, _col));
    }
  }
}
