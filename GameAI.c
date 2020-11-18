// TODO: Everything
// In all seriousness, go to the header file for required functions
#include "stdio.h"

#include <stdlib.h>
#include "GameAI.h"
#define gameBoardSize 3
#define player1 -1
#define player2 -2

int front[gameBoardSize][gameBoardSize];
int back[gameBoardSize][gameBoardSize];
int left[gameBoardSize][gameBoardSize];
int right[gameBoardSize][gameBoardSize];
int top[gameBoardSize][gameBoardSize];
int bottom[gameBoardSize][gameBoardSize];

// transfers game data to faces
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

// find if there is a possible win
int * primitiveCheck(int face[gameBoardSize][gameBoardSize], int player) {
    //check for win
    int TL_BR = 0;
    int TR_BL = 0;

    for (int i = 0; i < gameBoardSize; i++) {
        int horiz = 0;
        int vert = 0;
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
        if (face[i][i] == player || face[i][i] == 0) {TL_BR++;}
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

// individual checks for each direction to find index
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

// returns a random number between 0 < max
static int randomIntGen(int max) {
    return (rand() % max);
}

// TEST ME
void main() {
    //test face
    //    . . .
    //    x o o
    //    x . o

    int face[3][3] = {
            { 0,       0,       0},
            { player1, player2, player2},
            { player1, 0,       player2}
    };

    int * indices = primitiveCheck(face, player1);
    printf("%d %d", indices[0], indices[1]);

    indices = primitiveCheck(face, player2);
    printf("\n%d %d", indices[0], indices[1]);

}
