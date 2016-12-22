#include "elephant.h"

Elephant::Elephant() : boardptr(NULL), row(-1), col(-1), is_black(true) {
  type = ELEPHANT;
  icon = "_E_";
}

Elephant::Elephant(int _row, int _col, bool _black, Board* _ptr) :
  boardptr(_ptr), row(_row), col(_col), is_black(_black) {
  type = ELEPHANT;
  if (is_black) {
    icon = "_E_";
  } else {
    icon = "*E*";
  }
}

Elephant::~Elephant() {}
std::string Elephant::name() { return "Elephant"; }
