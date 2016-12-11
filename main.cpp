#include "includes.h"

int main() {
  std::cout << "Chinese Chess Game in ASCII\n";
  Board game;
  game.displayBoard(std::cout);
  int from_row, from_col, to_row, to_col;
  while (true) {
    std::cout << "Select cell to move from, using (zero-indexed) row and col separated by whitespace, e.g. 0 1.\n";
    std::cin >> from_row;
    std::cin >> from_col;
    std::cout << "Select cell to move to, using (zero-indexed) row and col separated by whitespace, e.g. 2 2.\n";
    std::cin >> to_row;
    std::cin >> to_col;
    game.submitMove(from_row, from_col, to_row, to_col);
    game.displayBoard(std::cout);
  }
  return 0;
}
