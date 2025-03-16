#ifndef TICTACTOE_H
#define TICTACTOE_H

void initializeBoard(char board[3][3]);
void printBoard(const char board[3][3]);
bool isValidMove(const char board[3][3], int row, int col);
bool isGameOver(const char board[3][3]);
char getWinner(const char board[3][3]);
#endif