#include <iostream>
#include <ctime>
#include "ai.h"
#include "player.h"
using namespace std;

char board[3][3] = {
    { ' ', ' ', ' ' },
    { ' ', ' ', ' ' },
    { ' ', ' ', ' ' }
};

void printBoard() {
    cout << "\n";
    for (int i = 0; i < 3; ++i) {
        cout << " ";
        for (int j = 0; j < 3; ++j) {
            cout << board[i][j];
            if (j < 2) cout << " | ";
        }
        cout << "\n";
        if (i < 2) cout << "---+---+---\n";
    }
    cout << "\n";
}

int main() {
    srand(time(0));

    Difficulty level;
    int choice;
    cout << "Choose AI Level (1-Easy, 2-Medium, 3-Hard): ";
    cin >> choice;
    level = static_cast<Difficulty>(choice - 1);

    char playerSymbol, aiSymbol;
    cout << "Do you want to be X or O? (X goes first): ";
    cin >> playerSymbol;
    playerSymbol = toupper(playerSymbol);
    aiSymbol = (playerSymbol == 'X') ? 'O' : 'X';

    char current = 'X';

    while (true) {
        printBoard();
        int score = evaluate(board, aiSymbol, playerSymbol);
        if (score == 10) { cout << "AI wins!\n"; break; }
        if (score == -10) { cout << "You win!\n"; break; }
        if (!isMovesLeft(board)) { cout << "It's a draw!\n"; break; }

        if (current == playerSymbol) {
            getHumanMove(board, playerSymbol);
            current = aiSymbol;
        } else {
            cout << "AI is making a move...\n";
            Move m = getAIMove(level, board, aiSymbol, playerSymbol);
            board[m.row][m.col] = aiSymbol;
            current = playerSymbol;
        }
    }

    printBoard();
    return 0;
}