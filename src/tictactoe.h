#ifndef TICTACTOE
#define TICTACTOE

#include <__config>
#include <exception>
#include <iosfwd>
#include <stack>

#define GRID_SIZE 3

using namespace std;

class SquareNotEmpty : exception {
  public:
    virtual const char *what() const noexcept { return "square is not empty."; }
};

class EmptyHistory : exception {
  public:
    virtual const char *what() const noexcept { return "history is empty"; }
};

class GameIsOver : exception {
  public:
    virtual const char *what() const noexcept { return "The game is over"; }
};

enum Symbole {
    EMPTY,
    CROSS,
    CIRCLE,
};

struct coord {
    int row, col;
};

class Tictactoe {

  private:
    Symbole grid[GRID_SIZE][GRID_SIZE];
    bool lastIsX;
    stack<coord> history;
    bool isFull();
    void initGrid();
    bool winningMove(coord);

  public:
    Tictactoe();
    Symbole turn();
    bool isGameOver(Symbole *winner);
    void play(coord);
    string ascii();
    void undo();
    void autoPlay();
};

#endif
