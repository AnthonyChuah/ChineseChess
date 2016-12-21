#include "horseman.h"

Horseman::Horseman() : boardptr(NULL), row(-1), col(-1), is_black(true) {
  type = HORSEMAN;
  icon = "_H_";
}

Horseman::Horseman(int _row, int _col, bool _black, Board* _ptr) :
  boardptr(_ptr), row(_row), col(_col), is_black(_black) {
  type = HORSEMAN;
  if (is_black) {
    icon = "_H_";
  } else {
    icon = "*H*";
  }
}

Horseman::~Horseman() {}
std::string Horseman::name() { return "Horseman"; }
