#include "ai.h"
#include "tictactoe.h"
#include <limits>
#include <algorithm>
#include <cstring>

int evaluateBoard(const char board[3][3]) {
    char winner = getWinner(board);
    if (winner == 'O') return 10;
    if (winner == 'X') return -10;

    auto evalLine = [](char a, char b, char c) {
        int score = 0;
        int o = (a == 'O') + (b == 'O') + (c == 'O');
        int x = (a == 'X') + (b == 'X') + (c == 'X');
        if (o > 0 && x == 0) score += o;
        if (x > 0 && o == 0) score -= x;
        return score;
    };

    int score = 0;
    for (int i = 0; i < 3; ++i) {
        score += evalLine(board[i][0], board[i][1], board[i][2]);
        score += evalLine(board[0][i], board[1][i], board[2][i]);
    }
    score += evalLine(board[0][0], board[1][1], board[2][2]);
    score += evalLine(board[0][2], board[1][1], board[2][0]);
    return score;
}

namespace {
int minimax(char board[3][3], bool isMaximizing, int alpha, int beta, int depth, int maxDepth) {
    char winner = getWinner(board);
    if (winner == 'O') return 10 - depth;
    if (winner == 'X') return depth - 10;
    if (depth == maxDepth) return evaluateBoard(board);
    if (isGameOver(board)) return 0;

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
