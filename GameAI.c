#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "GameAI.h"

#define gameBoardSize 3
#define FACES 6
#define CENTER -3

// Output coordinates
int AIOutput[3];

// player1 or player2 should be used
#define player1 -1
#define player2 -2

// 3d matrix
int aiBoard[gameBoardSize][gameBoardSize][gameBoardSize];

// 6 faces
int * front[gameBoardSize][gameBoardSize];
int * back[gameBoardSize][gameBoardSize];
int * left[gameBoardSize][gameBoardSize];
int * right[gameBoardSize][gameBoardSize];
int * top[gameBoardSize][gameBoardSize];
int * bottom[gameBoardSize][gameBoardSize];
int *(*faces[6])[3] = {front, back, left, right, top, bottom};

// Function declarations
void determine(int gameboard[gameBoardSize][gameBoardSize][gameBoardSize], int aiPlayer, int oppPlayer, char aiName);
void evaluate(int * face[gameBoardSize][gameBoardSize], int aiPlayer, int offScale, int oppPlayer, int defScale);
void calculate(int * face[gameBoardSize][gameBoardSize], int row, int col, int scale);
bool primitiveCheck(int * face[3][3], int player, int primitiveNum);
int findMarker(int ai, int player);
int * searchCoordinates(int req, int * coor);
void buildBoard(int gameboard[gameBoardSize][gameBoardSize][gameBoardSize]);
void updateFaces();

// Static Function Declarations
static int * findHorizIndex(int *face[3][3], int row);
static int * findVertIndex(int *face[3][3], int col);
static int * findTL_BRIndex(int *face[3][3]);
static int * findTR_BLIndex(int *face[3][3]);
static int randomIntGen(int max);

/**
 * Determine a move based on the board position
 * The selected AI determines a move based on positions. It starts by checking for obvious plays, like
 * winning the game, or preventing an opponent win. If there aren't any, an evaluation algorithm is run,
 * and the ai will randomly pick one from the set of highest options
 * @param gameboard The gameboard, w/ aiPlayer and oppPlayer values markers, and CENTER marking the center
 * @param aiPlayer The number representing the AI
 * @param oppPlayer The number representing the opponent
 * @param aiName The ai used to calculate the board position
 * Output is stored in AIOutput
 * */
void determine(int gameboard[gameBoardSize][gameBoardSize][gameBoardSize], int aiPlayer, int oppPlayer, char aiName){
    // Determine who is playing this game
    printf("\nDetermining player...\n");
    int primitiveNum = findMarker(aiPlayer, oppPlayer);
    int att, def;
    switch(aiName){
        case 'B': // Blinky 
            att = 9;
            def = 8;
            break;
        case 'P': // Pinky
            att = 3;
            def = 2;
            break;
        case 'I': // Inky
            att = 2;
            def = 3;
            break;
        default: // Clyde
            att = 1;
            def = 1;
    }

    // Prepare the AI's board view
    buildBoard(gameboard);
    updateFaces();

    // Primitive Check: Check for the winning move (AI win)
    printf("Checking for obvious moves...\n");
    bool prim = false;

    int index = 0;
    while(index < FACES && !prim){
        prim = primitiveCheck(faces[index], aiPlayer, primitiveNum);
        index++;
    }
    if(prim){
        // Search for the negative number
        int temp[gameBoardSize];
        searchCoordinates(primitiveNum, temp);
        AIOutput[0] = temp[0];
        AIOutput[1] = temp[1];
        AIOutput[2] = temp[2];
        return;
    }

    // Primitive Check: Check for the required move (Player win)
    prim = false;
    index = 0;
    while(index < FACES && !prim){
        prim = primitiveCheck(faces[index], oppPlayer, primitiveNum);
        index++;
    }
    if(prim){
        // Search for the negative number
        int temp[gameBoardSize];
        searchCoordinates(primitiveNum, temp);
        AIOutput[0] = temp[0];
        AIOutput[1] = temp[1];
        AIOutput[2] = temp[2];
        return;
    }

    // Evaluate if no obvious options are possible
    printf("Evaluating a position...\n");
    for(int i = 0; i < FACES; i++){
        evaluate(faces[i], aiPlayer, att, oppPlayer, def);
    }

    // Search for and return the given coordinates
    int temp[gameBoardSize];
    searchCoordinates(primitiveNum, temp);
    AIOutput[0] = temp[0];
    AIOutput[1] = temp[1];
    AIOutput[2] = temp[2];

    printf("Position decided!\n");
    return;
}

/**
 * Create a deep copy of the provided gameboard
 * Generates a ai specific gameboard that will be modified during primitive
 * checks and evaluation algorithms. The ai and player identifiers can be
 * swapped here.
 * @param The gameboard being copied
 * The output is stored on the global aiBoard
 **/
void buildBoard(int gameboard[gameBoardSize][gameBoardSize][gameBoardSize]){
    // Use aiBoard[3][3][3] to build the board
    for(int i = 0; i < gameBoardSize; i++){
        for(int j = 0; j < gameBoardSize; j++){
            for(int k = 0; k < gameBoardSize; k++){
                aiBoard[i][j][k] = gameboard[i][j][k];
            }
        }
    }
    aiBoard[1][1][1] = CENTER;
}

/**
 * Takes 3d array and transforms it into 6 2d arrays excluding the center index i.e. [1][1][1]
 * @param gameboard 3 dimensional array
 */
void updateFaces() {
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

/**
 * Evaluates a game face
 * Goes through the face and determines the priority of it's adjacent spaces. These
 * values appear on the the ai gameboard through the face pointers
 * @param face: A 2x2 array of int pointers that is being checked
 * @param aiPlayer: The int representation of the ai player
 * @param offScale: The weight of ai moves (aggressive plays)
 * @param oppPlayer: The int representation of the opponent
 * @param defScale: The weight of opponent moves
 * No output, all calculations are saved on the ai global gameboard
 **/
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

/**
 * Calculates the rows, columns, and diagonals for a given element
 * Goes through adjacent elements of the provided one to calculate the
 * priority of given spaces. Scale determines by how much priority to add
 * @param face: A 2x2 array of int pointers that is being checked
 * @param row: The row of our current element
 * @param col: The column of our current element
 * @param scale: The amount of priority to add for adjacent elements
 * No output, all calculations are saved on the ai global gameboard
 **/
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

/**
 * Search for the highest priority space and set the global to return it
 * @param req: The highest priority space, return immediately
 * @return A int[3] array that gives the ai's coordinates 
 **/
int * searchCoordinates(int req, int * coor) {
    // Search the global ai board to find the correct coordinate
    int current = -1;
    coor[0] = -1;
    coor[1] = -1;
    coor[2] = -1;
    for(int i = 0; i < gameBoardSize; i++){
        for(int j = 0; j < gameBoardSize; j++){
            for(int k = 0; k < gameBoardSize; k++){
                if(aiBoard[i][j][k] == req){
                    // Check if there's an important space to choose (Primtive answer)
                    coor[0] = i;
                    coor[1] = j;
                    coor[2] = k;
                    return coor;
                } else if(aiBoard[i][j][k] > current){
                    // Check if there's a better option (Evaluate)
                    current = aiBoard[i][j][k];
                    coor[0] = i;
                    coor[1] = j;
                    coor[2] = k;
                } else if(aiBoard[i][j][k] == current && randomIntGen(2) > 0){
                    // Randomly guess whether we should replace our current answer (Evaluate + Random)
                    current = aiBoard[i][j][k];
                    coor[0] = i;
                    coor[1] = j;
                    coor[2] = k;
                }

            }
        }
    }
    return coor;
}

/**
 * Finds a unique number to mark the urgent number
 * Generates a unique int identifier to set an element on the ai gameboard
 * to the highest priority. This function prevents collisions in the ai.
 * @param ai: The ai int identifier
 * @param player: The player identifier
 * */
int findMarker(int ai, int player){
    int mark = -1;
    while(mark == ai || mark == player || mark == CENTER){
        mark--;
    }
    return mark;
}

/**
 * looks for a potential win based on player. Since player2 is assumed as AI
 * You should run this for both player1 and player2 to check for possible wins/losses
 * @param face 2d array to look for win
 * @param player should be either player1 or player2 (-1 and -2 respectively)
 * @param primitiveNum indicates the potential win, w/ number marking it on the matrix
 * @return int[2] representing index of a win on a face
 * returns -1, -1 when no winning moves are found
 */
bool primitiveCheck(int * face[3][3], int player, int primitveNum) {
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
            if (*face[i][j] == player) horiz++;
            if (*face[j][i] == player) vert++;
        }
        // horizontal check
        if (horiz == 2) {
            int * indices =  findHorizIndex(face, i);
            if (indices[1] != -1) {
                *face[indices[0]][indices[1]] = primitveNum;
                return true;
            }
        }

        // vert check
        if (vert == 2) {
            int * indices = findVertIndex(face, i);
            if (indices[0] != -1) {
                *face[indices[0]][indices[1]] = primitveNum;
                return true;
            }
        }

        // Diagonal increment
        if (*face[i][i] == player) TL_BR++;
        if (*face[i][gameBoardSize-1-i] == player) TR_BL++;
    }

    // top left -> down right check
    if (TL_BR == 2) {
        int * indices = findTL_BRIndex(face);
        if (indices[0] != -1) {
            *face[indices[0]][indices[1]] = primitveNum;
            return true;
        }
    }
    // top right -> down left check
    if (TR_BL == 2) {
        int * indices = findTR_BLIndex(face);
        if (indices[0] != -1) {
            *face[indices[0]][indices[1]] = primitveNum;
            return true;
        }
    }
    return false;
}

// helper methods for finding correct index
static int * findHorizIndex(int * face[gameBoardSize][gameBoardSize], int row) {
    static int indices[2];
    int col = -1;
    for (int i = 0; i < gameBoardSize; i++) {
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
        if (*face[i][col] == 0) row = i;
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
        if (*face[i][i] == 0) {
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
        if (*face[i][gameBoardSize-1-i] == 0) {
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
static int randomIntGen(int max) {
    return (rand() % max);
}