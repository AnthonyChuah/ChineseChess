#include "includes.h"

Board::Board() : black_turn(false), black_in_check(false), red_in_check(false),
		 consec_checks_black(0), consec_checks_red(0) {
  initSetup();
  std::cout << "Insert Flavour Text Intro here.\n";
}

Board::~Board() {
  for (int i = 0; i < NUMROWS; ++i) {
    for (int j = 0; j < NUMCOLS; ++j) {
      delete board[i][j];
    }
  }
}

bool Board::submitMove(const int _fromrow, const int _fromcol, const int _torow, const int _tocol) {
  // Check if: (1) any coordinate is outside of the confines of the board.
  if (_fromrow < 0 || _fromrow >= NUMROWS || _fromcol < 0 || _fromcol >= NUMCOLS) {
    std::cout << "The FROM coordinates fell outside of the board. Try again.\n";
    return false;
  } else if (_torow < 0 || _torow >= NUMROWS || _tocol < 0 || _tocol >= NUMCOLS) {
    std::cout << "The TO coordinates fell outside of the board. Try again.\n";
    return false;
  }
  // Check if: (1) unit exists in from location, (2) unit corresponds to player's colour.
  if (board[_fromrow][_fromcol] == NULL) {
    std::cout << "The FROM coordinate specifies a blank square that has no unit. Try again.\n";
    return false;
  } else if (board[_fromrow][_fromcol]->colour() != black_turn) {
    std::cout << "It is not ";
    if (!black_turn) {
      std::cout << "Black";
    } else {
      std::cout << "Red";
    }
    std::cout << "'s turn to move!\n";
    return false;
  }
  // Calculate the relative-movement in terms of row and col offsets.
  int rowstep = _torow - _fromrow; int colstep = _tocol - _fromcol;
  std::string mover_name = board[_fromrow][_fromcol]->name();
  std::string victim_name;
  bool commit_murder = false;
  if (board[_torow][_tocol] != NULL) {
    commit_murder = true;
    victim_name = board[_torow][_tocol]->name();
  }
  std::string player_name, opponent_name;
  if (black_turn) {
    player_name = "Black";
    opponent_name = "Red";
  } else {
    player_name = "Red";
    opponent_name = "Black";
  }
  // Call the unit's movement function polymorphically.
  if (board[_fromrow][_fromcol]->move(rowstep, colstep)) {
    std::cout << player_name << "'s " << mover_name << " moved from R" << _fromrow << "C" << _fromcol << " to R"
	      << _torow << "C" << _tocol;
    if (commit_murder) {
      std::cout << " murdering " << opponent_name << "'s " << victim_name;
    }
    std::cout << "\n";
  } else {
    std::cout << player_name << "'s " << mover_name << " cannot move from R" << _fromrow << "C" << _fromcol
	      << " to R" << _torow << "C" << _tocol << "! Try again.\n";
    return false;
  }
  // Uncheck the active player, if it was in check.
  if (black_turn) {
    black_in_check = false;
  } else {
    red_in_check = false;
  }
  // Assess if opponent is in checkmate.
  if (assessCheck(!black_turn)) {
    // If it's black's turn, this calls the assessment for red.
    if (black_turn) {
      std::cout << "Red is in check";
      red_in_check = true;
      if (++consec_checks_red >= 3) {
	std::cout << "\nBlack has placed Red in check for 3 turns, and therefore loses. Red wins!\n";
	exit(1);
      }
    } else {
      std::cout << "Black is in check";
      black_in_check = true;
      if (++consec_checks_black >= 3) {
	std::cout << "\nRed has placed Black in check for 3 turns, and therefore loses. Black wins!\n";
	exit(1);
      }
    }
  } else {
    if (black_turn) {
      red_in_check = false;
      consec_checks_red = 0;
    } else {
      black_in_check = false;
      consec_checks_black = 0;
    }
  }
  // Assess if opponent is in check.
  if (assessMate(!black_turn)) {
    // This means that the opponent is in checkmate.
    std::cout << "mate\n";
    exit(1);
  } else {
    if (red_in_check || black_in_check) {
      // This means the opponent is in check but not checkmate.
      std::cout << "\n";
    }
  }
  // Assess if opponent is in stalemate.
  if (black_turn && !red_in_check) {
    // Check if Red is in stalemate.
    if (assessStale(!black_turn)) {
      std::cout << "Red is in stalemate\n";
      exit(1);
    }
  } else if (!black_turn && !black_in_check) {
    // Check if Black is in stalemate.
    if (assessStale(!black_turn)) {
      std::cout << "Black is in stalemate\n";
      exit(1);
    }
  }
  if (consec_checks_black) {
    std::cout << "Black has been checked consecutively for " << consec_checks_black
	      << " turns. The rules forbid repetitive checking for 3 turns consecutively.\n"
	      << "It is up to the players to decide what constitutes repetitive checking.\n";
  }
  if (consec_checks_red) {
    std::cout << "Red has been checked consecutively for " << consec_checks_red
	      << " turns. The rules forbid repetitive checking for 3 turns consecutively.\n"
	      << "It is up to the players to decide what constitutes repetitive checking.\n";
  }
  // Change turns to the other player.
  black_turn = !black_turn;
  return true;
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
  _outs << "    0   1   2   3   4   5   6   7   8  \n";
  _outs << "  +---+---+---+---+---+---+---+---+---+\n";
  for (int i = 0; i < NUMROWS; ++i) {
    _outs << i << " |";
    for (int j = 0; j < NUMCOLS; ++j) {
      if (board[i][j] == NULL) {
	_outs << "   ";
      } else {
	_outs << board[i][j]->icon();
      }
      _outs << "|";
    }
    _outs << "\n";
    _outs << "  +---+---+---+---+---+---+---+---+---+\n";
  }
  if (black_turn) {
    _outs << "It is BLACK's turn.\n";
  } else {
    _outs << "It is RED's turn.\n";
  }
  if (black_in_check) {
    _outs << "BLACK is in CHECK!\n";
  } else if (red_in_check) {
    _outs << "RED is in CHECK!\n";
  }
}

void Board::initSetup() {
  for (int i = 0; i < NUMROWS; ++i) {
    for (int j = 0; j < NUMCOLS; ++j) {
      board[i][j] = NULL;
    }
  }
  Soldier* soldierb; Soldier* soldierr;
  for (int i = 0; i < 5; ++i) {
    soldierb = new Soldier(3, i*2, true, this);
    board[3][i*2] = soldierb;
    soldierr = new Soldier(6, i*2, false, this);
    board[6][i*2] = soldierr;
  }
  Cannon* cannonb1; Cannon* cannonb2; Cannon* cannonr1; Cannon* cannonr2;
  cannonb1 = new Cannon(2, 1, true, this); board[2][1] = cannonb1;
  cannonb2 = new Cannon(2, 7, true, this); board[2][7] = cannonb2;
  cannonr1 = new Cannon(7, 1, false, this); board[7][1] = cannonr1;
  cannonr2 = new Cannon(7, 7, false, this); board[7][7] = cannonr2;
  Chariot* chariotb1; Chariot* chariotb2; Chariot* chariotr1; Chariot* chariotr2;
  chariotb1 = new Chariot(0, 0, true, this); board[0][0] = chariotb1;
  chariotb2 = new Chariot(0, 8, true, this); board[0][8] = chariotb2;
  chariotr1 = new Chariot(9, 0, false, this); board[9][0] = chariotr1;
  chariotr2 = new Chariot(9, 8, false, this); board[9][8] = chariotr2;
  Horseman* horsemanb1; Horseman* horsemanb2; Horseman* horsemanr1; Horseman* horsemanr2;
  horsemanb1 = new Horseman(0, 1, true, this); board[0][1] = horsemanb1;
  horsemanb2 = new Horseman(0, 7, true, this); board[0][7] = horsemanb2;
  horsemanr1 = new Horseman(9, 1, false, this); board[9][1] = horsemanr1;
  horsemanr2 = new Horseman(9, 7, false, this); board[9][7] = horsemanr2;
  Elephant* elephantb1; Elephant* elephantb2; Elephant* elephantr1; Elephant* elephantr2;
  elephantb1 = new Elephant(0, 2, true, this); board[0][2] = elephantb1;
  elephantb2 = new Elephant(0, 6, true, this); board[0][6] = elephantb2;
  elephantr1 = new Elephant(9, 2, false, this); board[9][2] = elephantr1;
  elephantr2 = new Elephant(9, 6, false, this); board[9][6] = elephantr2;
  Mandarin* mandarinb1; Mandarin* mandarinb2; Mandarin* mandarinr1; Mandarin* mandarinr2;
  mandarinb1 = new Mandarin(0, 3, true, this); board[0][3] = mandarinb1;
  mandarinb2 = new Mandarin(0, 5, true, this); board[0][5] = mandarinb2;
  mandarinr1 = new Mandarin(9, 3, false, this); board[9][3] = mandarinr1;
  mandarinr2 = new Mandarin(9, 5, false, this); board[9][5] = mandarinr2;
  General* generalb; General* generalr;
  generalb = new General(0, 4, true, this); board[0][4] = generalb;
  generalr = new General(9, 4, false, this); board[9][4] = generalr;
}

bool Board::assessCheck(bool _black) {
  // Asks the question: is player in check? If _black true, then asks if black is in check.
  int general_row = -1, general_col = -1;
  std::set<std::pair<int, int> > enemy_range;
  for (int i = 0; i < NUMROWS; ++i) {
    for (int j = 0; j < NUMCOLS; ++j) {
      if (board[i][j] == NULL) {
	continue;
      } else if (board[i][j]->colour() != _black) {
	board[i][j]->threatRange(enemy_range);
      } else if (board[i][j]->type() == GENERAL) {
        general_row = i; general_col = j;
      } // Else, it's an allied non-general unit and no threat range needs to be calculated for it.
    }
  }
  // Now check if the threat range includes the position occupied by the General.
  std::pair<int, int> general_loc(general_row, general_col);
  std::set<std::pair<int, int> >::iterator it = enemy_range.find(general_loc);
  if (it == enemy_range.end()) {
    return false; // Then the general is not within the enemy's threat range.
  } else {
    return true; // Ach! The general is in the enemy's threat range!
  }
}

bool Board::assessStale(bool _black) {
  // Same reasoning as assessCheck, but now assessing Stalemate instead.
  for (int i = 0; i < NUMROWS; ++i) {
    for (int j = 0; j < NUMCOLS; ++j) {
      if (board[i][j] == NULL) {
	continue;
      } else if (board[i][j]->colour() == _black) {
	// Now check for _black's unit, whether he can make a move that does not check himself.
	std::set<std::pair<int, int> > unit_range;
	board[i][j]->threatRange(unit_range);
	std::set<std::pair<int, int> >::iterator it;
	for (it = unit_range.begin(); it != unit_range.end(); ++it) {
	  int try_row = it->first; int try_col = it->second;
	  if (board[i][j]->assessMove(try_row, try_col)) {
	    return false; // Returns false, signalling that there is no stalemate for _black.
	  }
	}
      }
    }
  }
  return true;
}

bool Board::assessMate(bool _black) {
  // Same reasoning as assessCheck, but now assessing Checkmate instead.
  if (_black && black_in_check) {
    return assessStale(_black);
  } else if (!_black && red_in_check) {
    return assessStale(!_black);
  }
  return false; // If neither pair of conditions hold, it is not a checkmate.
}
