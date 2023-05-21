#ifndef TICTACTOE
#define TICTACTOE

#include <__config>
#include <exception>
#include <iosfwd>
#include <stack>

#define GRID_SIZE 3

using namespace std;

class SquareNotEmpty: exception {
    public:
        const char* what() {
            return "square is not empty.";
        }
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
        bool isFull();
        void initGrid();
        stack<coord> history;

    public:
        Tictactoe();
        Symbole turn();
        bool isGameOver(Symbole *winner);
        void play(int x, int y);
        string ascii();
        void undo();

};

#endif
