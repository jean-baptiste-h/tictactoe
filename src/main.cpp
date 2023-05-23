#include "tictactoe.h"
#include <__config>
#include <exception>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <stdlib.h>

using namespace std;

enum Mode { ONE_PLAYER, TWO_PLAYER };

class InvalidInput : exception {
    const char *what() const throw() { return "input is not valid"; }
};

int readInt();
void readCoord(coord *);
Mode menu();

int main() {
    coord c;
    Symbole winner;
    Tictactoe tictactoe;
    Mode mode;
    Symbole autoSymbole = EMPTY;

    cout << endl;
    cout << "===================" << endl;
    cout << "||  Tic-tac-toe  ||" << endl;
    cout << "===================" << endl;
    cout << endl;

    mode = menu();

    if (mode == ONE_PLAYER) {
        char rep;
        do {
            cout << "Do you want to play first ? [y/n] ";
            cin >> rep;
        } while (rep != 'y' && rep != 'n');
        autoSymbole = (rep == 'y') ? CIRCLE : CROSS;
    }

    do {
        if ((mode == ONE_PLAYER) && (autoSymbole == tictactoe.turn())) {
            tictactoe.autoPlay();
        } else {
            // print status and grid
            if (tictactoe.turn() == CROSS)
                cout << "X's turn !" << endl;
            else
                cout << "O's turn !" << endl;

            cout << tictactoe.ascii() << endl;

            // input square position
            readCoord(&c);

            // play at the position
            try {
                tictactoe.play(c);
            } catch (const invalid_argument e) {
                cout << "Line and column number must be between 0 and 2 "
                        "included !"
                     << endl;
            } catch (const SquareNotEmpty e) {
                cout << "This square is not empty." << endl;
            }
        }
    } while (!tictactoe.isGameOver(&winner));

    cout << tictactoe.ascii() << endl;

    if (winner == EMPTY) {
        cout << "The game is a draw!" << endl;
    } else {
        cout << "The " << ((winner == CROSS) ? 'X' : 'O') << " have won !"
             << endl;
    }

    return EXIT_SUCCESS;
}

int readInt() {
    int n;

    cin >> n;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        throw InvalidInput();
    }
    return n;
}

void readCoord(coord *c) {
    bool valid = false;
    do {
        try {
            cout << "Enter row number : ";
            c->row = readInt();
            cout << "Enter column number : ";
            c->col = readInt();
            valid = true;
        } catch (InvalidInput e) {
            cout << "You must enter a number !";
        }
    } while (!valid);
}

Mode menu() {
    int n;
    Mode res;
    do {
        cout << "1) One player" << endl;
        cout << "2) Two players" << endl;
        cout << "3) Quit" << endl;
        cout << "What do you want to do? ";

        try {
            n = readInt();
        } catch (InvalidInput e) {
            cout << "You must enter a valid number!" << endl;
            n = -1;
        }
    } while (n < 1 || n > 3);

    switch (n) {
    case 1:
        res = ONE_PLAYER;
        break;
    case 2:
        res = TWO_PLAYER;
        break;
    case 3:
        exit(EXIT_SUCCESS);
    }

    return res;
}
