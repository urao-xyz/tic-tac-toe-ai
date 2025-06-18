#include "ai.h"
#include "tictactoe.h"
#include <limits>
#include <algorithm>

namespace {
int minimax(char board[3][3], bool isMaximizing, int alpha, int beta, int depth, int maxDepth) {
    char winner = getWinner(board);
    if (winner == 'O') return 10 - depth;
    if (winner == 'X') return depth - 10;
    if (isGameOver(board) || depth == maxDepth) return 0;

    if (isMaximizing) {
        int bestScore = std::numeric_limits<int>::min();
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'O';
                    int score = minimax(board, false, alpha, beta, depth + 1, maxDepth);
                    board[i][j] = ' ';
                    bestScore = std::max(bestScore, score);
                    alpha = std::max(alpha, score);
                    if (beta <= alpha)
                        return bestScore;
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
                    int score = minimax(board, true, alpha, beta, depth + 1, maxDepth);
                    board[i][j] = ' ';
                    bestScore = std::min(bestScore, score);
                    beta = std::min(beta, score);
                    if (beta <= alpha)
                        return bestScore;
                }
            }
        }
        return bestScore;
    }
}
} // namespace

int minimax(char board[3][3], bool isMaximizing, int alpha, int beta) {
    return minimax(board, isMaximizing, alpha, beta, 0, 9);
}


std::pair<int, int> getBestMove(char board[3][3], int maxDepth) {
    int bestScore = std::numeric_limits<int>::min();
    std::pair<int, int> bestMove = {-1, -1};

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == ' ') {
                board[i][j] = 'O';
                int score = minimax(board, false, std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), 1, maxDepth);
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
