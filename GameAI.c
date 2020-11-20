// TODO: Everything
// In all seriousness, go to the header file for required functions
// #include "stdio.h"
#include <stdlib.h>
#include "GameAI.h"
#define gameBoardSize 3

// Output coordinates
int AIOutput[gameBoardSize];

// Function declarations
void updateFaces(int gameboard[gameBoardSize][gameBoardSize][gameBoardSize]);
int * primitiveCheck(int face[gameBoardSize][gameBoardSize], int player);
static int * findHorizIndex(int face[gameBoardSize][gameBoardSize], int row);
static int * findVertIndex(int face[gameBoardSize][gameBoardSize], int col);
static int * findTL_BRIndex(int face[gameBoardSize][gameBoardSize]);
static int * findTR_BLIndex(int face[gameBoardSize][gameBoardSize]);

// player1 or player2 should be used
#define player1 -1
#define player2 -2

// 3d matrix
// For 3D matrix reference, here's how we'll refer to spots on the board
// 1 2 3    11 12 13    21 22 23
// 4 5 6    14 15 16    24 25 26
// 7 8 9    17 18 19    27 28 29
int globalBoard[gameBoardSize][gameBoardSize][gameBoardSize];

// 6 implicit faces
// You MUST typecast the pointers before using them, C doesn't know what type of data the
// pointers are referring to: (int *) front[0][0] and use * (int *) front[0][0] to dereference
// TODO: Create a better solution that doesn't use as many hard-coded values. @Nicolas Guerrero

// Front Face
// 1 2 3
// 4 5 6
// 7 8 9
void * front[gameBoardSize][gameBoardSize] = {
    {&globalBoard[0][0][0], &globalBoard[0][0][1], &globalBoard[0][0][2]},
    {&globalBoard[0][1][0], &globalBoard[0][1][1], &globalBoard[0][1][2]},
    {&globalBoard[0][2][0], &globalBoard[0][2][1], &globalBoard[0][2][2]}
};

// Back Face
// 21 22 23
// 24 25 26
// 27 28 29
void * back[gameBoardSize][gameBoardSize] = {
    {&globalBoard[2][0][0], &globalBoard[2][0][1], &globalBoard[2][0][2]},
    {&globalBoard[2][1][0], &globalBoard[2][1][1], &globalBoard[2][1][2]},
    {&globalBoard[2][2][0], &globalBoard[2][2][1], &globalBoard[2][2][2]}
};

// Left Face
// 21 11 1
// 24 14 4
// 27 17 7
void * left[gameBoardSize][gameBoardSize] = {
    {&globalBoard[2][0][0], &globalBoard[1][0][0], &globalBoard[0][0][0]},
    {&globalBoard[2][1][0], &globalBoard[1][1][0], &globalBoard[0][1][0]},
    {&globalBoard[2][2][0], &globalBoard[1][2][0], &globalBoard[0][2][0]}
};

// Right Face
// 3 13 23
// 6 16 26
// 9 19 29
void * right[gameBoardSize][gameBoardSize] = {
    {&globalBoard[0][0][2], &globalBoard[1][0][2], &globalBoard[2][0][2]},
    {&globalBoard[0][1][2], &globalBoard[1][1][2], &globalBoard[2][1][2]},
    {&globalBoard[0][2][2], &globalBoard[1][2][2], &globalBoard[2][2][2]}
};

// Top Face
// 21 22 23
// 11 12 13
// 1  2  3
void * top[gameBoardSize][gameBoardSize] = {
    {&globalBoard[2][0][0], &globalBoard[2][0][1], &globalBoard[2][0][2]},
    {&globalBoard[1][0][0], &globalBoard[1][0][1], &globalBoard[1][0][2]},
    {&globalBoard[0][0][0], &globalBoard[0][0][1], &globalBoard[0][0][2]}
};

// Bottom Face
// 7  8  9
// 17 18 19
// 27 28 29
void * bottom[gameBoardSize][gameBoardSize] = {
    {&globalBoard[0][2][0], &globalBoard[0][2][1], &globalBoard[0][2][2]},
    {&globalBoard[1][2][0], &globalBoard[1][2][1], &globalBoard[1][2][2]},
    {&globalBoard[2][2][0], &globalBoard[2][2][1], &globalBoard[2][2][2]}
};

// 6 faces
//int front[gameBoardSize][gameBoardSize];
//int back[gameBoardSize][gameBoardSize];
//int left[gameBoardSize][gameBoardSize];
//int right[gameBoardSize][gameBoardSize];
//int top[gameBoardSize][gameBoardSize];
//int bottom[gameBoardSize][gameBoardSize];

/**
 * Takes 3d array and transforms it into 6 2d arrays excluding the center index i.e. [1][1][1]
 * @param gameboard 3 dimensional array
 */
void updateFaces(int gameboard[gameBoardSize][gameBoardSize][gameBoardSize]) {
    for (int i = 0; i < gameBoardSize; i++) {
        for (int j = 0; j < gameBoardSize; j++) {
            front[i][j] = gameboard[0][i][j];
            back[i][j] = gameboard[2][i][j];

            top[i][j] = gameboard[i][0][j];
            bottom[i][j] = gameboard[i][2][j];

            left[i][j] = gameboard[i][j][0];
            right[i][j] = gameboard[i][j][2];
        }
    }
}

/**
 * looks for a potential win based on player. Since player2 is assumed as AI
 * You should run this for both player1 and player2 to check for possible wins/losses
 * @param face 2d array to look for win
 * @param player should be either player1 or player2 (-1 and -2 respectively)
 * @return int[2] representing index on face to input,
 * returns -1, -1 when no winning moves are found
 */
int * primitiveCheck(int face[gameBoardSize][gameBoardSize], int player) {
    /*
     * increments a directional value every time a player move matches
     * so on if a player has two moves on a horizontal linem horiz will be value 2.
     */

    int TL_BR = 0; // topLeft->botRight diagonal
    int TR_BL = 0; // topRight->botLeft diagonal

    for (int i = 0; i < gameBoardSize; i++) {
        int horiz = 0; // horizontal direction
        int vert = 0; // vertical direction
        for (int j = 0; j < gameBoardSize; j++) { // find how many "O" in a vert/horiz line
            if (face[i][j] == player) horiz++;
            if (face[j][i] == player) vert++;
        }
        // horizontal check
        if (horiz == 2) {
            int * indices =  findHorizIndex(face, i);
            if (indices[1] != -1) return indices;
        }

        // vert check
        if (vert == 2) {
            int * indices = findVertIndex(face, i);
            if (indices[0] != -1) return indices;
        }

        // Diagonal increment
        if (face[i][i] == player) {TL_BR++;}
        if (face[i][gameBoardSize-1-i] == player) {TR_BL++;}
    }

    // top left -> down right check
    if (TL_BR == 2) {
        int * indices = findTL_BRIndex(face);
        if (indices[0] != -1) return indices;
    }
    // top right -> down left check
    if (TR_BL == 2) {
        int * indices = findTR_BLIndex(face);
        if (indices[0] != -1) return indices;
    }

    // no valid move
    static int noMove[2];
    noMove[0] = -1;
    noMove[1] = -1;
    return noMove;
}

// helper methods for finding correct index
static int * findHorizIndex(int face[gameBoardSize][gameBoardSize], int row) {
    static int indices[2];
    int col = -1;
    for (int i = 0; i < gameBoardSize; i++) {
        if (face[row][i] == 0) col = i;
    }

    indices[0] = row;
    indices[1] = col;
    return indices;
}

static int * findVertIndex(int face[gameBoardSize][gameBoardSize], int col) {
    static int indices[2];
    int row = -1;
    for (int i = 0; i < gameBoardSize; i++) {
        if (face[i][col] == 0) row = i;
    }

    indices[0] = row;
    indices[1] = col;
    return indices;
}

static int * findTL_BRIndex(int face[gameBoardSize][gameBoardSize]) {
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

static int * findTR_BLIndex(int face[gameBoardSize][gameBoardSize]) {
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
