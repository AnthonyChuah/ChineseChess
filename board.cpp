#include "includes.h"

Board::Board() : black_turn(false), black_in_check(false), red_in_check(false) {
  initSetup();
  std::cout << "A new day has begun. The morning sun rises slowly over the parched earth.\n"
	    << "Spanning this arid expanse are two opposing armies, spears and axes sharpened to kill.\n"
	    << "Before this day ends, the blood of legions will water the earth like so much rainfall.\n"
	    << "The carnage will be savage and legendary. Slaughter, or be slaughtered.\n"
	    << "May you rip your foe's heart out of his chest and hew his limbs in twain.\n"
	    << "Drive your foes before you, and hear the lamentations of their women and children.\n"
	    << "May your roar of triumph shake the heavens.\n"
	    << "Good luck, commander.\n\n";
}

Board::~Board() {
  for (int i = 0; i < NUMROWS; ++i) {
    for (int j = 0; j < NUMCOLS; ++j) {
      delete board[i][j];
    }
  }
}

bool Board::submitMove(const std::pair<int, int> _from, const std::pair<int, int> _to) {
  // Check if: (1) any coordinate is outside of the confines of the board.
  // Check if: (1) unit exists in from location, (2) unit corresponds to player's colour.
  // Calculate the relative-movement in terms of row and col offsets.
  // Call the unit's movement function polymorphically.
  // Uncheck the active player, if it was in check.
  // Assess if opponent is in checkmate.
  // Assess if opponent is in check.
  // Assess if opponent is in stalemate.
  // Swap the turn over to the other player.
}

void Board::resetBoard() {
  for (int i = 0; i < NUMROWS; ++i) {
    for (int j = 0; j < NUMCOLS; ++j) {
      delete board[i][j];
      board[i][j] = NULL;
    }
  }
  black_turn = false; black_in_check = false; red_in_check = false;
  initSetup();
  std::cout << "You turn Hermione Granger's Time-Turner and go back to the morning before the battle began.\n";
}

void Board::displayBoard(std::ostream& _outs) {
  // Tediously and nicely output an ASCII-formatted board.
}

void Board::initSetup() {
  // Set up all the pieces using new operator to allocate heap memory for them.
}

bool Board::assessCheck(bool _black) {
  // Asks the question: is player in check? If _black true, then asks if black is in check.
}

bool Board::assessStale(bool _black) {
  // Same reasoning as assessCheck, but now assessing Stalemate instead.
}

bool Board::assessMate(bool _black) {
  // Same reasoning as assessCheck, but now assessing Checkmate instead.
}
