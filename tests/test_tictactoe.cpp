#include <cassert>
#include "tictactoe.h"

int main() {
    char winX[3][3] = {
        {'X','X','X'},
        {'O','O',' '},
        {' ',' ',' '}
    };
    assert(getWinner(winX) == 'X');
    assert(isGameOver(winX));

    char winO[3][3] = {
        {'X',' ',' '},
        {'O','O','O'},
        {'X',' ',' '}
    };
    assert(getWinner(winO) == 'O');
    assert(isGameOver(winO));

    char draw[3][3] = {
        {'X','O','X'},
        {'X','O','O'},
        {'O','X','X'}
    };
    assert(getWinner(draw) == ' ');
    assert(isGameOver(draw));

    char ongoing[3][3] = {
        {'X',' ',' '},
        {'O',' ',' '},
        {' ',' ',' '}
    };
    assert(getWinner(ongoing) == ' ');
    assert(!isGameOver(ongoing));

    return 0;
}
