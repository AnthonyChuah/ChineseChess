#include "soldier.h"

Soldier::Soldier() : boardptr(NULL), row(-1), col(-1), is_black(true) {
  type = SOLDIER;
  icon = "_S_";
}

Soldier::Soldier(int _row, int _col, bool _black, Board* _ptr) :
  boardptr(_ptr), row(_row), col(_col), is_black(_black) {
  type = SOLDIER;
  if (is_black) {
    icon = "_S_";
  } else {
    icon = "*S*";
  }
}

Soldier::~Soldier() {}
std::string Soldier::name() { return "Soldier"; }
