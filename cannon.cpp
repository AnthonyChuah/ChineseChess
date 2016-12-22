#include "cannon.h"

Cannon::Cannon() : boardptr(NULL), row(-1), col(-1), is_black(true) {
  type = CANNON;
  icon = "_C_";
}

Cannon::Cannon(int _row, int _col, bool _black, Board* _ptr) :
  boardptr(_ptr), row(_row), col(_col), is_black(_black) {
  type = CANNON;
  if (is_black) {
    icon = "_C_";
  } else {
    icon = "*C*";
  }
}

Cannon::~Cannon() {}
std::string Cannon::name() { return "Cannon"; }
