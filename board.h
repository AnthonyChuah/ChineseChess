#ifndef BOARD_H
#define BOARD_H

class Unit;

class Board {
 public:
  Board();
  ~Board();
  // submitMove attempts to move a unit from a location to another location.
  bool submitMove(const int _fromrow, const int _fromcol, const int _torow, const int _tocol);
  void resetBoard(); // Clear all units, place them into starting positions, make it Red's turn.
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
  void mainloopGUI();
  bool initGraphics();
  bool loadMedia();
  void closeGraphics();
  void render(int _x, int _y, SDL_Rect* _clip);
 private:
  void handleMouseEvent(SDL_Event* e); // Handles mouse event.
  void drawMouseOver();
  void drawMouseClick();
  void renderSprite(int _x, int _y);
  void renderUnits();
  void renderText(std::string _text);
  void initSetup(); // Helper function places units into start positions.
  bool black_turn; // true if it is black player's turn.
  bool black_in_check; // true if black is in check.
  bool red_in_check; // true if red is in check.
  int consec_checks_black; // It can go from 0 to 1 to 2, but 3 means an instant loss for checking player!
  int consec_checks_red;
  Unit* board[NUMROWS][NUMCOLS];
  // Fixed-size 2d array of pointers to Unit objects, but Unit is abstract parent class.
  // All calls to board[row][col]->function will be polymorphic.
  SDL_Window* gWindow;
  SDL_Renderer* gRenderer;
  SDL_Texture* gSpritesTexture;
  SDL_Texture* gBoardTexture;
  SDL_Texture* gTextTexture;
  TTF_Font* gFont;
  SDL_Rect gSpriteClips[NUM_SPRITES];
  SDL_Rect upperViewport;
  SDL_Rect lowerViewport;
  SDL_Color textColor;
  bool isMouseOver; // Whether the mouse is over the board.
  bool isMouseDown;
  std::pair<int, int> mousedSquare; // Board (not pixel!) coordinates of moused over square.
  // However, swapped x and y coords to match the graphics coords system.
  bool isSelectedSquare; // Whether a square has been selected.
  std::pair<int, int> selectedSquare; // Board (not pixel!) coordinates of selected square.
  // However, swapped x and y coords to match the graphics coords system.
  std::string textDisplay; // Text to display in the lower viewport.
};

#endif
