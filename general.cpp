#include "general.h"

General::General() : boardptr(NULL), row(-1), col(-1), is_black(true) {
  type = GENERAL;
  icon = "_G_";
}

General::General(int _row, int _col, bool _black, Board* _ptr) :
  boardptr(_ptr), row(_row), col(_col), is_black(_black) {
  type = GENERAL;
  if (is_black) {
    icon = "_G_";
  } else {
    icon = "*G*";
  }
}

General::~General() {}
std::string General::name() { return "General"; }
