#include <iostream>
#include <sqlite3.h>
#include "tictactoe.h"
#include "ai.h"
#include "scoreboard.h"
#include <cstdlib>
#include <ctime>
#include <string>
#include <limits>

void logMove(sqlite3 *db, int gameId, int player, int row, int col) {
    std::string query = "INSERT INTO moves (game_id, player, row, col) VALUES (" +
                        std::to_string(gameId) + ", " +
                        std::to_string(player) + ", " +
                        std::to_string(row) + ", " +
                        std::to_string(col) + ");";

    char *errMsg = nullptr;
    if (sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::cerr << "Erreur SQL : " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
}

void logGameResult(sqlite3 *db, int gameId, int winner, int totalMoves) {
    std::string query = "UPDATE games SET winner = " +
                        std::to_string(winner) + ", total_moves = " +
                        std::to_string(totalMoves) +
                        " WHERE game_id = " + std::to_string(gameId) + ";";

    char *errMsg = nullptr;
    if (sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::cerr << "Erreur SQL : " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
}

int main(int argc, char* argv[]) {
    // Initialiser SQLite
    sqlite3 *db;
    if (sqlite3_open("tictactoe.db", &db) != SQLITE_OK) {
        std::cerr << "Impossible d'ouvrir la base de données." << std::endl;
        return 1;
    }

    // Créer les tables si elles n'existent pas déjà
    const char *createMovesTable = R"(
        CREATE TABLE IF NOT EXISTS moves (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            game_id INTEGER,
            player INTEGER,
            row INTEGER,
            col INTEGER
        );
    )";

    const char *createGamesTable = R"(
        CREATE TABLE IF NOT EXISTS games (
            game_id INTEGER PRIMARY KEY,
            winner INTEGER, -- 1 = Joueur, 2 = IA, 0 = Match nul
            total_moves INTEGER
        );
    )";

    char *errMsg = nullptr;
    if (sqlite3_exec(db, createMovesTable, nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::cerr << "Erreur SQL (moves) : " << errMsg << std::endl;
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 1;
    }
    if (sqlite3_exec(db, createGamesTable, nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::cerr << "Erreur SQL (games) : " << errMsg << std::endl;
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 1;
    }

    int searchDepth = 9;
    std::string diff;
    if (argc > 1) {
        diff = argv[1];
    } else {
        std::cout << "Choisissez la difficulté (easy/medium/hard) : ";
        std::cin >> diff;
    }
    if (diff == "easy") searchDepth = 1;
    else if (diff == "medium") searchDepth = 3;
    else searchDepth = 9;

    bool playAgain = true;
    while (playAgain) {
        if (sqlite3_exec(db, "INSERT INTO games (winner, total_moves) VALUES (NULL, NULL);", nullptr, nullptr, &errMsg) != SQLITE_OK) {
            std::cerr << "Erreur SQL (insert game) : " << errMsg << std::endl;
            sqlite3_free(errMsg);
            break;
        }
        int gameId = static_cast<int>(sqlite3_last_insert_rowid(db));
        int totalMoves = 0;

        char board[3][3];
        initializeBoard(board);
        char currentPlayer = 'X';

        while (!isGameOver(board)) {
            printBoard(board);
            int row, col;

            if (currentPlayer == 'O') {
                std::pair<int, int> move = getBestMove(board, searchDepth);
                row = move.first;
                col = move.second;
            } else {
                std::cout << "Entrez votre coup (ligne et colonne) : ";
                std::cin >> row >> col;
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Entrée invalide.\n";
                    continue;
                }

                if (!isValidMove(board, row, col)) {
                    std::cout << "Coup invalide. Réessayez.\n";
                    continue;
                }
            }

            board[row][col] = currentPlayer;
            logMove(db, gameId, currentPlayer == 'X' ? 1 : 2, row, col);
            totalMoves++;
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        }

        printBoard(board);
        char winner = getWinner(board);
        int winnerCode = (winner == 'X') ? 1 : (winner == 'O') ? 2 : 0;
        logGameResult(db, gameId, winnerCode, totalMoves);

        if (winnerCode == 1) {
            std::cout << "Vous avez gagné !\n";
        } else if (winnerCode == 2) {
            std::cout << "L'IA a gagné.\n";
        } else {
            std::cout << "Match nul !\n";
        }

        displayScoreboard(db);

        std::cout << "Rejouer ? (y/n) : ";
        char choice;
        std::cin >> choice;
        while (std::cin.fail() || (choice != 'y' && choice != 'n')) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Entrez y ou n : ";
            std::cin >> choice;
        }
        playAgain = (choice == 'y');
    }

    sqlite3_close(db);
    return 0;
}