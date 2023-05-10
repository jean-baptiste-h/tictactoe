#include "tictactoe.h"
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

int main() {
    int x, y;
    Symbole winner;
    Tictactoe tictactoe;

    cout << tictactoe.ascii() << endl;

    do {
        cout << "Enter line number : ";
        cin >> x;

        cout << "Enter column number : ";
        cin >> y;

        try {
            tictactoe.play(x, y);
        } catch (const invalid_argument e) {
            cout << "Line and column number must be between 0 and 2 included !"
                 << endl;
        } catch (const SquareNotEmpty e) {
            cout << "This square is not empty." << endl;
        }

        cout << tictactoe.ascii() << endl;
    } while (!tictactoe.isGameOver(&winner));

    if (winner == EMPTY) {
        cout << "The game is a draw !" << endl;
    } else {
        cout << "The " << ((winner == CROSS) ? 'X' : 'O') << " have won !"
             << endl;
    }

    return EXIT_SUCCESS;
}
