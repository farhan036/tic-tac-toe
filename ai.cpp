#include "ai.h"
#include <vector>
#include <cstdlib>
#include <algorithm>

const int SIZE = 3;

bool isMovesLeft(char board[3][3]) {
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            if (board[i][j] == ' ') return true;
    return false;
}

int evaluate(char board[3][3], char aiSymbol, char humanSymbol) {
    for (int i = 0; i < SIZE; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            if (board[i][0] == aiSymbol) return +10;
            else if (board[i][0] == humanSymbol) return -10;
        }
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
            if (board[0][i] == aiSymbol) return +10;
            else if (board[0][i] == humanSymbol) return -10;
        }
    }
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        if (board[0][0] == aiSymbol) return +10;
        else if (board[0][0] == humanSymbol) return -10;
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        if (board[0][2] == aiSymbol) return +10;
        else if (board[0][2] == humanSymbol) return -10;
    }
    return 0;
}

int minimax(char board[3][3], int depth, bool isMax, int alpha, int beta, char aiSymbol, char humanSymbol) {
    int score = evaluate(board, aiSymbol, humanSymbol);
    if (score == 10 || score == -10) return score;
    if (!isMovesLeft(board)) return 0;

    if (isMax) {
        int best = -1000;
        for (int i = 0; i < SIZE; ++i)
            for (int j = 0; j < SIZE; ++j)
                if (board[i][j] == ' ') {
                    board[i][j] = aiSymbol;
                    best = std::max(best, minimax(board, depth + 1, false, alpha, beta, aiSymbol, humanSymbol));
                    board[i][j] = ' ';
                    alpha = std::max(alpha, best);
                    if (beta <= alpha) return best;
                }
        return best;
    } else {
        int best = 1000;
        for (int i = 0; i < SIZE; ++i)
            for (int j = 0; j < SIZE; ++j)
                if (board[i][j] == ' ') {
                    board[i][j] = humanSymbol;
                    best = std::min(best, minimax(board, depth + 1, true, alpha, beta, aiSymbol, humanSymbol));
                    board[i][j] = ' ';
                    beta = std::min(beta, best);
                    if (beta <= alpha) return best;
                }
        return best;
    }
}

Move getRandomMove(char board[3][3]) {
    std::vector<Move> moves;
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            if (board[i][j] == ' ')
                moves.push_back({ i, j });
    return moves[rand() % moves.size()];
}

Move getBestMove(char board[3][3], char aiSymbol, char humanSymbol) {
    int bestVal = -1000;
    Move bestMove = {-1, -1};
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            if (board[i][j] == ' ') {
                board[i][j] = aiSymbol;
                int moveVal = minimax(board, 0, false, -1000, 1000, aiSymbol, humanSymbol);
                board[i][j] = ' ';
                if (moveVal > bestVal) {
                    bestMove = { i, j };
                    bestVal = moveVal;
                }
            }
    return bestMove;
}

Move getAIMove(Difficulty level, char board[3][3], char aiSymbol, char humanSymbol) {
    if (level == EASY) return getRandomMove(board);
    if (level == MEDIUM) return (rand() % 2 == 0) ? getRandomMove(board) : getBestMove(board, aiSymbol, humanSymbol);
    return getBestMove(board, aiSymbol, humanSymbol);
}