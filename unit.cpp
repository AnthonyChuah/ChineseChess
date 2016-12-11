#include "unit.h"

Unit::Unit() : boardptr(NULL), row(-1), col(-1), is_black(true) {
  type = UNIT;
  icon = "_U_";
}

Unit::Unit(int _row, int _col, bool _black, Board* _ptr) :
  boardptr(_ptr), row(_row), col(_col), is_black(_black) {
  type = UNIT;
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
