#include <stdlib.h>
#include <__config>
#include <exception>
#include <iostream>
#include <limits>
#include <stdexcept>
#include "tictactoe.h"

using namespace std;

class InvalidInput : exception {
    const char *what() const throw() {
        return "input is not valid";
    }
};

int readInt();

int main() {
    int x, y;
    Symbole winner;
    Tictactoe tictactoe;

    cout << endl;
    cout << "===================" << endl;
    cout << "||  Tic-tac-toe  ||" << endl;
    cout << "===================" << endl;
    cout << endl;

    do {
        if (tictactoe.turn() == CROSS)
            cout << "X's turn !" << endl;
        else
            cout << "O's turn !" << endl;

        cout << tictactoe.ascii() << endl;
        
        try {
        cout << "Enter line number : ";
        x = readInt();

        cout << "Enter column number : ";
        y = readInt();
        } catch(const InvalidInput e) {
            cout << "You must enter a valid number !" << endl;
            continue;
        }

        try {
            tictactoe.play(x, y);
        } catch (const invalid_argument e) {
            cout << "Line and column number must be between 0 and 2 included !"
                 << endl;
        } catch (const SquareNotEmpty e) {
            cout << "This square is not empty." << endl;
        }

    } while (!tictactoe.isGameOver(&winner));

    cout << tictactoe.ascii() << endl;

    if (winner == EMPTY) {
        cout << "The game is a draw !" << endl;
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
