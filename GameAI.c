// TODO: Everything
// In all seriousness, go to the header file for required functions
// #include "stdio.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "GameAI.h"
#define gameBoardSize 3

// Output coordinates
int AIOutput[gameBoardSize];

// player1 or player2 should be used
#define player1 -1
#define player2 -2

// 3d matrix
// For 3D matrix reference, here's how we'll refer to spots on the board
// 1 2 3    11 12 13    21 22 23
// 4 5 6    14 15 16    24 25 26
// 7 8 9    17 18 19    27 28 29
int aiBoard[gameBoardSize][gameBoardSize][gameBoardSize];

// 6 faces
int * front[gameBoardSize][gameBoardSize];
int * back[gameBoardSize][gameBoardSize];
int * left[gameBoardSize][gameBoardSize];
int * right[gameBoardSize][gameBoardSize];
int * top[gameBoardSize][gameBoardSize];
int * bottom[gameBoardSize][gameBoardSize];
int ** faces[6] = {front, back, left, right, top, bottom};

// prevent compilation warnings, still need to be declared before being called
static int * findHorizIndex(int *face[3][3], int row);
static int * findVertIndex(int *face[3][3], int col);
static int * findTL_BRIndex(int *face[3][3]);
static int * findTR_BLIndex(int *face[3][3]);

void determine(int gameboard[gameBoardSize][gameBoardSize][gameBoardSize], int aiPlayer, int oppPlayer, char aiName){
    // Determine who is playing this game
    int att, def;
    switch(aiName){
        case 'b': // Blinky 
            att = 9;
            def = 8;
            break;
        case 'p': // Pinky
            att = 3;
            def = 2;
            break;
        case 'i': // Inky
            att = 2;
            def = 3;
            break;
        default: // Clyde
            att = 0;
            def = 0;
    }

    // Prepare the AI's board view
    buildBoard(gameboard);
    updateFaces();
    // aiOutput
    
    // Primitive Check: Check for the winning move
    bool prim = false;
    {
        int i = 0;
        while(i < 6 && !prim){
            prim = primitiveCheck(faces[i], aiPlayer);
        }
    }
    if(prim){
        // Search for the negative number
        return;
    }

    // Primitive Check: Check for the required move
    prim = false;
    {
        int i = 0;
        while(i < 6 && !prim){
            prim = primitiveCheck(faces[i], aiPlayer);
        }
    }

    // Evaluate if no obvious options are possible
}

void buildBoard(int gameboard[gameBoardSize][gameBoardSize][gameBoardSize]){
    // Use aiBoard[3][3][3] to build the board
    for(int i = 0; i < gameBoardSize; i++){
        for(int j = 0; j < gameBoardSize; j++){
            for(int k = 0; k < gameBoardSize; k++){
                aiBoard[i][j][k] = gameboard[i][j][k];
            }
        }
    }
}

/**
 * Takes 3d array and transforms it into 6 2d arrays excluding the center index i.e. [1][1][1]
 * @param gameboard 3 dimensional array
 */
void updateFaces() {
    // TODO: Transfer data to aiBoard
    //buildBoard(gameboard);
    for (int i = 0; i < gameBoardSize; i++) {
        for (int j = 0; j < gameBoardSize; j++) {
            front[i][j] = &aiBoard[0][i][j];
            back[i][j] = &aiBoard[2][i][j];

            top[i][j] = &aiBoard[i][0][j];
            bottom[i][j] = &aiBoard[i][2][j];

            left[i][j] = &aiBoard[i][j][0];
            right[i][j] = &aiBoard[i][j][2];
        }
    }
}
// void updateFaces(int gameboard[gameBoardSize][gameBoardSize][gameBoardSize]) {

void evaluate(int * face[gameBoardSize][gameBoardSize], int aiPlayer, int offScale, int oppPlayer, int defScale){
    for(int i = 0; i < gameBoardSize; i++){
        for(int j = 0; j < gameBoardSize; j++){
            if(*face[i][j] == aiPlayer){
                calculate(face, i, j, offScale);
            } else if(*face[i][j] == oppPlayer){
                calculate(face, i, j, defScale);
            }
        }
    }
}

void calculate(int * face[gameBoardSize][gameBoardSize], int row, int col, int scale){
    // Horizontal calculation
    for(int i = 0; i < gameBoardSize; i++){
        if(*face[row][i] >= 0){
            *face[row][i] += scale;
        }
    }

    // Vertical calculation
    for(int j = 0; j < gameBoardSize; j++){
        if(*face[j][col] >= 0){
            *face[j][col] += scale;
        }
    }

    // Check if we need a diagonal calculation
    if(abs(row - col) % 2 == 0){
        // Check top-left to bottom-right
        if(col == row){
            for(int k = 0; k < gameBoardSize; k++){
                if(*face[k][k] >= 0){
                    *face[k][k] += scale;
                }
            }
        }
        // Check bottom-left to top-right
        if(col != row || col == 1){
            for(int k = 0; k < gameBoardSize; k++){
                if(*face[k][2 - k] >= 0){
                    *face[k][2 - k] += scale;
                }
            }
        }
    }
}

int * searchCoordinates(){
    // Search global
    int current = 0;
    int coor[3];
    for(int i = 0; i < gameBoardSize; i++){
        for(int j = 0; j < gameBoardSize; j++){
            for(int k = 0; k < gameBoardSize; k++){

            }
        }
    }
}

/**
 * looks for a potential win based on player. Since player2 is assumed as AI
 * You should run this for both player1 and player2 to check for possible wins/losses
 * @param face 2d array to look for win
 * @param player should be either player1 or player2 (-1 and -2 respectively)
 * @return int[2] representing index of a win on a face
 * returns -1, -1 when no winning moves are found
 */
bool primitiveCheck(int * face[3][3], int player) {
    /*
     * increments a directional value every time a player move matches
     * so on if a player has two moves on a horizontal linem horiz will be value 2.
     */

    int TL_BR = 0; // topLeft->botRight diagonal
    int TR_BL = 0; // topRight->botLeft diagonal

    /**
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d", *face[i][j]);
        }
        printf("\n");
    } */

    for (int i = 0; i < gameBoardSize; i++) {
        int horiz = 0; // horizontal direction
        int vert = 0; // vertical direction
        for (int j = 0; j < gameBoardSize; j++) { // find how many "O" in a vert/horiz line
            if (*face[i][j] == player) horiz++;
            if (*face[j][i] == player) vert++;
        }
        // horizontal check
        if (horiz == 2) {
            int * indices =  findHorizIndex(face, i);
            if (indices[1] != -1) {
                *face[indices[0]][indices[1]] = -3;
                return true;
            }
        }

        // vert check
        if (vert == 2) {
            int * indices = findVertIndex(face, i);
            if (indices[0] != -1) {
                *face[indices[0]][indices[1]] = -3;
                return true;;
            }
        }

        // Diagonal increment
        if (*face[i][i] == player) {TL_BR++;}
        if (*face[i][gameBoardSize-1-i] == player) {TR_BL++;}
    }

    // top left -> down right check
    if (TL_BR == 2) {
        int * indices = findTL_BRIndex(face);
        if (indices[0] != -1) {
            *face[indices[0]][indices[1]] = -3;
            return true;
        }
    }
    // top right -> down left check
    if (TR_BL == 2) {
        int * indices = findTR_BLIndex(face);
        if (indices[0] != -1) {
            *face[indices[0]][indices[1]] = -3;
            return true;
        }
    }

    // no valid move
    //static int noMove[2];
    //noMove[0] = -1;
    //noMove[1] = -1;
    //return noMove;
    return false;
}

// helper methods for finding correct index
static int * findHorizIndex(int * face[gameBoardSize][gameBoardSize], int row) {
    static int indices[2];
    int col = -1;
    for (int i = 0; i < gameBoardSize; i++) {
        //printf("%d", *face[row][i]);
        if (*face[row][i] == 0) col = i;
    }

    indices[0] = row;
    indices[1] = col;
    return indices;
}

static int * findVertIndex(int * face[gameBoardSize][gameBoardSize], int col) {
    static int indices[2];
    int row = -1;
    for (int i = 0; i < gameBoardSize; i++) {
        if (* face[i][col] == 0) row = i;
    }

    indices[0] = row;
    indices[1] = col;
    return indices;
}

static int * findTL_BRIndex(int *face[gameBoardSize][gameBoardSize]) {
    static int indices[2];
    int row = -1;
    int col = -1;
    for (int i = 0; i < gameBoardSize; i++) {
        if (face[i][i] == 0) {
            row = i;
            col = i;
        }
    }
    indices[0] = row;
    indices[1] = col;
    return indices;
}

static int * findTR_BLIndex(int *face[gameBoardSize][gameBoardSize]) {
    static int indices[2];
    int row = -1;
    int col = -1;
    for (int i = 0; i < gameBoardSize; i++) {
        if (face[i][gameBoardSize-1-i] == 0) {
            row = i;
            col = i;
        }
    }
    indices[0] = row;
    indices[1] = col;
    return indices;
}

/**
 * Returns a random int between 0 < max
 * @param max maximum int of random number, non-inclusive
 * @return int
 */
//static int randomIntGen(int max) {
//    return (rand() % max);
//}

//// TEST ME
//void main() {
//    //test face
//    //    . . .
//    //    x o o
//    //    x . o
//
//    int face[3][3] = {
//            { 0,       0,       0},
//            { player1, player2, player2},
//            { player1, 0,       player2}
//    };
//
//    int * indices = primitiveCheck(face, player1);
//    printf("%d %d", indices[0], indices[1]);
//
//    indices = primitiveCheck(face, player2);
//    printf("\n%d %d", indices[0], indices[1]);
//}
