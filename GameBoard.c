#include <stdio.h>
#include <stdbool.h>
#include "GameDisplay.h"
//#include "GameAI.h"
#define gameBoardSize 3

// Method declarations
void initGameBoard();
int isValidMove(int i, int j, int k);
int isValidIndex(int i, int j, int k);
void printGameBoard();

// Numerical Gameboard
int gameboard [gameBoardSize][gameBoardSize][gameBoardSize];

// 0 represents no move
// -1 represents player 1
// -2 represents player 2
// TODO: Represent the center node as 3 or something
void initGameBoard() {
    for (int i = 0; i < gameBoardSize; i++) {
        for (int j = 0; j < gameBoardSize; j++) {
            for (int k = 0; k < gameBoardSize; k++) {
                gameboard[i][j][k] = 0;
            }
        }
    }
}

int isValidMove(int i, int j, int k) {
    if (isValidIndex(i, j, k) == 0) return 0; // index check

    if (gameboard[i][j][k] == 0) return 1; // check if spot is empty
    return 0;
}

// check if input is outside of index range
int isValidIndex(int i, int j, int k) {
    if (i >= gameBoardSize || i < 0 ||
        j >= gameBoardSize || j < 0 ||
        k >= gameBoardSize || k < 0 ||
        (i == 1 && j == 1 && k == 1) // center of 3d cube
            ) return 0; // return false;
    return 1; // return true;
}

// gameboard[i][j][k]
// but loop is j i k
void printGameBoard() {
    for (int j = 0; j < gameBoardSize; j++) {
        for (int i = 0; i < gameBoardSize; i++) {
            for (int k = 0; k < gameBoardSize; k++) {
                int move = gameboard[i][j][k];
                if (move == 1) printf("x");
                else if (move == 2) printf("o");
                else printf("-");
            }
            printf("\t");
        }
        printf("\n");
    }
}

// Main Game Application
int main(){
    bool active = true;
    initGameBoard();
    gameIntroduction();
    char player;

    // Set active game
    while(active){
        player = gameMenu();

        switch(player){
            case 'Y':
                // start ai game, user first
                break;
            case 'N':
                // start ai game, ai first
                break;
            case 'B':
                // start 2 player game
                break;
            case 'R':
                gameInstructions();
                break;
            case 'Q':
                active = false;
                printf("Goodbye\n");
                break;
            default:
                printf("Sorry, that request is not undestood.\n");
        }
    }
}
