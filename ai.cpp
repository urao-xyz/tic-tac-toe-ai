#include "ai.h"
#include "tictactoe.h"
#include <limits>
#include <algorithm>


int minimax(char board[3][3], bool isMaximizing) {
    char winner = getWinner(board);
    if (winner == 'O') return 10;
    if (winner == 'X') return -10;
    if (isGameOver(board)) return 0;

    if (isMaximizing) {
        int bestScore = std::numeric_limits<int>::min();
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'O';
                    bestScore = std::max(bestScore, minimax(board, false));
                    board[i][j] = ' ';
                }
            }
        }
        return bestScore;
    } else {
        int bestScore = std::numeric_limits<int>::max();
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'X';
                    bestScore = std::min(bestScore, minimax(board, true));
                    board[i][j] = ' ';
                }
            }
        }
        return bestScore;
    }
}

std::pair<int, int> getBestMove(char board[3][3]) {
    int bestScore = std::numeric_limits<int>::min();
    std::pair<int, int> bestMove = {-1, -1};

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == ' ') {
                board[i][j] = 'O';
                int score = minimax(board, false);
                board[i][j] = ' ';
                if (score > bestScore) {
                    bestScore = score;
                    bestMove = {i, j};
                }
            }
        }
    }
    return bestMove;
}
