#include "player.h"
#include <iostream>
using namespace std;

void getHumanMove(char board[3][3], char symbol) {
    int r, c;
    while (true) {
        cout << "Enter your move (row col 0 to 2): ";
        cin >> r >> c;
        if (r >= 0 && r < 3 && c >= 0 && c < 3 && board[r][c] == ' ') {
            board[r][c] = symbol;
            break;
        } else {
            cout << "Invalid move. Try again.\n";
        }
    }
}
