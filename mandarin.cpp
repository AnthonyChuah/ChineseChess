#include "mandarin.h"

Mandarin::Mandarin() : boardptr(NULL), row(-1), col(-1), is_black(true) {
  type = MANDARIN;
  icon = "_M_";
}

Mandarin::Mandarin(int _row, int _col, bool _black, Board* _ptr) :
  boardptr(_ptr), row(_row), col(_col), is_black(_black) {
  type = MANDARIN;
  if (is_black) {
    icon = "_M_";
  } else {
    icon = "*M*";
  }
}

Mandarin::~Mandarin() {}
std::string Mandarin::name() { return "Mandarin"; }
