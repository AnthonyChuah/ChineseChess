#include "includes.h"

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cout << "You have to specify 'text' or 'gui' when calling the executable, "
	      << "like this: ./game text\n";
    return 1;
  }
  std::string arg1 = argv[1];
  if (arg1 == "text") {
    std::cout << "Chinese Chess Game in ASCII\n";    
    Board game; int from_row, from_col, to_row, to_col;
    while (true) {
      game.displayBoard(std::cout);
      std::cout << "Select cell to move from, using (zero-indexed) row and col separated by whitespace, e.g. 0 1.\n";
      std::cin >> from_row;
      std::cin >> from_col;
      std::cout << "Select cell to move to, using (zero-indexed) row and col separated by whitespace, e.g. 2 2.\n";
      std::cin >> to_row;
      std::cin >> to_col;
      game.submitMove(from_row, from_col, to_row, to_col);
    }
  } else if (arg1 == "gui") {
    std::cout << "Launching Chinese Chess Game with SDL2 graphics\n";
    Board game;
    game.mainloopGUI();
  } else {
    std::cout << "Invalid argument in calling executable. Use 'text' or 'gui'.\n";
    return 1;
  }
  return 0;
}
