//
// Created by ricky on 11/5/20.
// Edited by nicolas on 11/8/20.
// ^ I would remove this in future commits, git records for us
//

//#include "GameBoard.h"
#include "stdio.h"
#define gameBoardSize 3

// Method declarations
void initGameBoard();
int isValidMove(int i, int j, int k);
int isValidIndex(int i, int j, int k);
void printGameBoard();

// Numerical Gameboard
int gameboard [gameBoardSize][gameBoardSize][gameBoardSize];

// Print-friendly Gameboard
char gameDisplay[592] = "\
                                         C\n\
                                         I-----I-----I-----I\n\
                     B                   |  1  |  2  |  3  |\n\
                     I-----I-----I-----I I-----I-----I-----I\n\
A                    |  1  |  2  |  3  | |  4  |  5  |  6  |\n\
I-----I-----I-----I  I-----I-----I-----I I-----I-----I-----I\n\
|  1  |  2  |  3  |  |  4  |  5  |  6  | |  7  |  8  |  9  |\n\
I-----I-----I-----I  I-----I-----I-----I I-----I-----I-----I\n\
|  4  |  5  |  6  |  |  7  |  8  |  9  |\n\
I-----I-----I-----I  I-----I-----I-----I\n\
|  7  |  8  |  9  |\n\
I-----I-----I-----I";

// int slots[27] = {148, 154, 160, 270, 276, 282, 392, 398, 404
// 250, 256, 262, 372, 378, 384, 494, 500, 506
// 351, 357, 363, 473, 479, 485, 555, 561, 567};

// These are the positions on the gameboard TODO: Make an array of pointers instead.
int slots[gameBoardSize][gameBoardSize][gameBoardSize] = {
    {
        {351, 357, 363},
        {473, 479, 485},
        {555, 561, 567}
    },
    {
        {250, 256, 262},
        {372, 378, 384},
        {494, 500, 506}
    },
    {
        {148, 154, 160},
        {270, 276, 282},
        {392, 398, 404}
    }
};


// 0 represents no move
// 1 represents player 1
// 2 represents player 2
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
        k >= gameBoardSize || k < 0
            ) return 0;
    return 1;
}

// gameboard[i][j][k]
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
 
void displayBoard(){
     printf("%s\n", gameDisplay);
     //printf("%c", *(gameDisplay + 41)); // Location of C character
     //printf("%c", *(gameDisplay + 148)); // Location of C character
     //printf("%c", *(gameDisplay + 250)); // Location of C character
     //printf("%c", *(gameDisplay + 351)); // Location of C character
}

/**
void findLocations(){
    int values[3];
    int j = 0;
    char c;
    for(int i = 0; i < 592; i++){
        c = gameDisplay[i];
        if(c == '9'){
            values[j] = i;
            j++;
        }
    }
    for(int k = 0; k < 3; k++){
        printf("\n%d", values[k]);
    }
}
**/

void customEdit(){
    printf("\n%d", slots[0][0][0]);
    gameDisplay[slots[0][0][0]] = 'X';
}

// TODO 2d checkwin and 3d

int main(){
    initGameBoard();
    printGameBoard();
    customEdit();
    displayBoard();
}