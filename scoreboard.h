#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <sqlite3.h>

int getScoreCounts(sqlite3* db, int& playerWins, int& aiWins, int& draws);
void displayScoreboard(sqlite3* db);

#endif
