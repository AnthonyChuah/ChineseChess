#ifndef BOARD_H
#define BOARD_H

class Unit;

class Board {
 public:
  Board();
  ~Board();
  // submitMove attempts to move a unit from a location to another location.
  bool submitMove(const std::pair<int, int> _from, const std::pair<int, int> _to);
  void resetBoard(); // Clear all units, place all units into starting positions, make it Red's turn.
  void displayBoard(std::ostream& _outs); // Displays the current chess board to the output stream.
  bool assessCheck(bool _black); // Verify if _black is in check.
  bool assessStale(bool _black); // Verify if _black is stalemated.
  bool assessMate(bool _black); // Verify if _black is in checkmate.
  friend class Unit;
  friend class Soldier;
  friend class Cannon;
  friend class Chariot;
  friend class Horseman;
  friend class Elephant;
  friend class Mandarin;
  friend class General;
 private:
  void initSetup(); // Helper function places units into start positions.
  bool black_turn; // true if it is black player's turn.
  bool red_in_check; // true if red is in check.
  bool black_in_check; // true if black is in check.
  Unit* board[NUMROWS][NUMCOLS];
  // Fixed-size 2d array of pointers to Unit objects, but Unit is abstract parent class.
  // All calls to board[row][col]->function will be polymorphic.
};

#endif
