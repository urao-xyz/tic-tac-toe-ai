#include <cassert>
#include "tictactoe.h"
#include "ai.h"

int main() {
    // Scenario: AI should win
    char board1[3][3] = {
        {'O','O',' '},
        {'X','X',' '},
        {' ',' ',' '}
    };
    auto move1 = getBestMove(board1);
    assert(move1.first == 0 && move1.second == 2);

    // Scenario: AI should block player's win
    char board2[3][3] = {
        {'X','X',' '},
        {'O',' ',' '},
        {' ',' ',' '}
    };
    auto move2 = getBestMove(board2);
    assert(move2.first == 0 && move2.second == 2);

    // Scenario: evaluation used at depth limit
    char board3[3][3] = {
        {'O',' ',' '},
        {'X',' ',' '},
        {' ',' ',' '}
    };
    auto move3 = getBestMove(board3, 1);
    assert(move3.first == 1 && move3.second == 1);

    return 0;
}
