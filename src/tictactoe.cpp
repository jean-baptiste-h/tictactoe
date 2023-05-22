#include "tictactoe.h"
#include <cstdlib>
#include <stdexcept>
#include <string>
#include <vector>

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

void Tictactoe::play(coord c) {
    if ((c.row < 0 || c.row >= GRID_SIZE) || (c.col < 0 || c.col >= GRID_SIZE))
        throw invalid_argument("x and y must be between 0 and 2 included.");
    if (grid[c.row][c.col] != EMPTY)
        throw SquareNotEmpty();
    grid[c.row][c.col] = turn();
    history.push(c);
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
    if (history.empty())
        throw EmptyHistory();
    coord c = history.top();
    grid[c.row][c.col] = EMPTY;
    history.pop();
    lastIsX = !lastIsX;
}

bool Tictactoe::winningMove(coord c) {
    bool res = false;
    Symbole winner;
    bool gameover;

    play(c);
    gameover = isGameOver(&winner);
    undo();
    if (gameover)
        if (winner == turn())
            res = true;

    return res;
}

void Tictactoe::autoPlay() {
    int i, j;
    coord c;
    bool found = false;
    Symbole winner;

    // check if I can win
    for (i = 0; i < GRID_SIZE && !found; i++) {
        for (j = 0; j < GRID_SIZE && !found; j++) {
            if (grid[i][j] == EMPTY) {
                c.row = i;
                c.col = j;
                if (winningMove(c))
                    found = true;
            }
        }
    }

    // check if the opponent can win
    if (!found) {
        lastIsX = !lastIsX;
        for (i = 0; i < GRID_SIZE && !found; i++) {
            for (j = 0; j < GRID_SIZE && !found; j++) {
                if (grid[i][j] == EMPTY) {
                    c.row = i;
                    c.col = j;
                    if (winningMove(c))
                        found = true;
                }
            }
        }
        lastIsX = !lastIsX;
    }

    if (!found) {
        // play in the center square if possible
        if (grid[1][1] == EMPTY) {
            c.row = 1;
            c.col = 1;
        } else {
            // play in a random square
            int n;
            vector<coord> emptySquares;
            for(i=0; i<GRID_SIZE; i++) {
                for(j=0; j<GRID_SIZE; j++) {
                    if(grid[i][j]==EMPTY) {
                        c.row = i;
                        c.col = j;
                        emptySquares.push_back(c);
                    }
                }
            }
            n = (rand()*emptySquares.size()) / RAND_MAX;
            c = emptySquares[n];
        }
    }

    play(c);
}
