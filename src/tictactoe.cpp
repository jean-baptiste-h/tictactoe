#include "tictactoe.h"
#include <stdexcept>
#include <string>

Tictactoe::Tictactoe() {
    lastIsX = false;
    initGrid();
}

void Tictactoe::initGrid() {
    int i, j;

    for (i = 0; i < GRID_SIZE; i++) {
        for (j = 0; j < GRID_SIZE; j++) {
            grid[i][j] = EMPTY;
        }
    }
}

Symbole Tictactoe::turn() {
    Symbole res;
    if (lastIsX) {
        res = CIRCLE;
    } else {
        res = CROSS;
    }
    return res;
}

bool Tictactoe::isGameOver(Symbole *winner) {
    bool res = false;
    int i;

    *winner = EMPTY;

    for (i = 0; i < GRID_SIZE && !res; i++) {
        if (grid[i][0] != EMPTY) {
            if (grid[i][0] == grid[i][1] && grid[i][1] == grid[i][2]) {
                res = true;
                *winner = grid[i][0];
            }
        }
        if (!res && grid[0][i] != EMPTY) {
            if (grid[0][i] == grid[1][i] && grid[1][i] == grid[2][i]) {
                res = true;
                *winner = grid[0][i];
            }
        }
    }

    if (!res && grid[1][1] != EMPTY) {
        if ((grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2]) ||
            (grid[2][0] == grid[1][1] && grid[1][1] == grid[0][2])) {
            res = true;
            *winner = grid[1][1];
        }
    }

    return res || isFull();
}

void Tictactoe::play(int x, int y) {
    if ((x < 0 || x >= GRID_SIZE) || (y < 0 || y >= GRID_SIZE))
        throw invalid_argument("x and y must be between 0 and 2 included.");
    if (grid[x][y] != EMPTY)
        throw SquareNotEmpty();
    grid[x][y] = turn();
    history.push({x, y});
    lastIsX = !lastIsX;
}

string Tictactoe::ascii() {
    string res = "";
    int i, j;
    char c;

    for (i = 0; i < GRID_SIZE; i++) {
        for (j = 0; j < GRID_SIZE; j++) {
            switch (grid[i][j]) {
            case CROSS:
                c = 'X';
                break;
            case CIRCLE:
                c = 'O';
                break;
            default:
                c = ' ';
            }
            res += c;
            if (j < GRID_SIZE - 1)
                res += '|';
        }
        if (i < GRID_SIZE - 1)
            res += '\n';
    }

    return res;
}

bool Tictactoe::isFull() {
    bool res = true;
    int i, j;

    for (i = 0; i < GRID_SIZE && res; i++) {
        for (j = 0; j < GRID_SIZE && res; j++) {
            if (grid[i][j] == EMPTY)
                res = false;
        }
    }

    return res;
}

void Tictactoe::undo() {
    coord c = history.top();
    grid[c.row][c.col] = EMPTY;
    history.pop();
    lastIsX = !lastIsX;
}
