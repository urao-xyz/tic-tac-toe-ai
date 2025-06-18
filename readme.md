# Tic-Tac-Toe AI

Ce projet implémente un jeu de Tic-Tac-Toe avec une IA utilisant l'algorithme Minimax. Le jeu enregistre également les mouvements et les résultats des parties dans une base de données SQLite.

## Prérequis

- C++ Compiler
- SQLite3

## Installation

1. Clonez le dépôt :
    ```sh
    git clone https://github.com/urao-xyz/tic-tac-toe-ai
    cd tic-tac-toe-ai
    ```

2. Compilez le projet avec `make` :
    ```sh
    make
    ```

## Utilisation

1. Exécutez le programme :
    ```sh
    ./tictactoe
    ```
    Vous pouvez aussi passer la difficulté en argument (`easy`, `medium` ou `hard`).

2. Suivez les instructions à l'écran pour jouer contre l'IA. A la fin de chaque partie, un tableau des scores cumulés est affiché et vous pouvez choisir de rejouer.

## Structure du projet

- `main.cpp` : Logique principale et intégration avec SQLite.
- `tictactoe.cpp` : Contient les fonctions de gestion du plateau de jeu.
- `ai.cpp` : Contient l'implémentation de l'algorithme Minimax pour l'IA.
- `tictactoe.h` et `ai.h` : Contiennent les déclarations des fonctions utilisées dans `tictactoe.cpp` et `ai.cpp`.
- `scoreboard.cpp` et `scoreboard.h` : fonctions d'affichage du tableau des scores.

## Tests

Pour compiler et exécuter les tests :

```sh
make run-tests
```

## Auteur

- [urao-xyz].
