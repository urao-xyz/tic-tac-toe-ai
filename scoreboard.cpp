#include "scoreboard.h"
#include <iostream>

int getScoreCounts(sqlite3* db, int& playerWins, int& aiWins, int& draws) {
    const char* query = "SELECT winner, COUNT(*) FROM games GROUP BY winner;";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
        return 0;
    }
    playerWins = aiWins = draws = 0;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int winner = sqlite3_column_int(stmt, 0);
        int count = sqlite3_column_int(stmt, 1);
        if (winner == 1) playerWins = count;
        else if (winner == 2) aiWins = count;
        else if (winner == 0) draws = count;
    }
    sqlite3_finalize(stmt);
    return 1;
}

void displayScoreboard(sqlite3* db) {
    int playerWins, aiWins, draws;
    if (!getScoreCounts(db, playerWins, aiWins, draws)) {
        std::cerr << "Erreur lors de la r\xC3\xA9cup\xC3\xA9ration du score." << std::endl;
        return;
    }
    std::cout << "Scoreboard - Joueur: " << playerWins
              << " | IA: " << aiWins
              << " | Nuls: " << draws << std::endl;
}
