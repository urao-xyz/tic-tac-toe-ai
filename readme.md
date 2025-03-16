# Tic-Tac-Toe AI

Ce projet implémente un jeu de Tic-Tac-Toe avec une IA utilisant l'algorithme Minimax. Le jeu enregistre également les mouvements et les résultats des parties dans une base de données SQLite.

## Prérequis

- C++ Compiler
- SQLite3

## Installation

1. Clonez le dépôt :
    ```sh
    git clone <URL_DU_DEPOT>
    cd tic-tac-toe-ai
    ```

2. Compilez le projet :
    ```sh
    g++ -o tictactoe main.cpp tictactoe.cpp ai.cpp -lsqlite3
    ```

## Utilisation

1. Exécutez le programme :
    ```sh
    ./tictactoe
    ```

2. Suivez les instructions à l'écran pour jouer contre l'IA.

## Structure du projet

- `main.cpp` : Contient la logique principale du jeu et l'intégration avec SQLite.
- `tictactoe.cpp` : Contient les fonctions de gestion du plateau de jeu.
- `ai.cpp` : Contient l'implémentation de l'algorithme Minimax pour l'IA.
- `tictactoe.h` et `ai.h` : Contiennent les déclarations des fonctions utilisées dans `tictactoe.cpp` et `ai.cpp`.

## Auteur

- [urao-xyz].
