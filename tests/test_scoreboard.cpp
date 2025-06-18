#include <cassert>
#include "scoreboard.h"
#include <sqlite3.h>

int main() {
    sqlite3* db;
    sqlite3_open(":memory:", &db);
    const char* create = "CREATE TABLE games (game_id INTEGER PRIMARY KEY, winner INTEGER, total_moves INTEGER);";
    sqlite3_exec(db, create, nullptr, nullptr, nullptr);
    sqlite3_exec(db, "INSERT INTO games (winner,total_moves) VALUES (1,5);", nullptr, nullptr, nullptr);
    sqlite3_exec(db, "INSERT INTO games (winner,total_moves) VALUES (2,5);", nullptr, nullptr, nullptr);
    sqlite3_exec(db, "INSERT INTO games (winner,total_moves) VALUES (0,9);", nullptr, nullptr, nullptr);
    sqlite3_exec(db, "INSERT INTO games (winner,total_moves) VALUES (1,7);", nullptr, nullptr, nullptr);

    int p,a,d;
    getScoreCounts(db, p,a,d);
    assert(p==2);
    assert(a==1);
    assert(d==1);
    sqlite3_close(db);
    return 0;
}
