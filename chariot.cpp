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
