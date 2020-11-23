#ifndef _GAMEAI_H_
#define _GAMEAI_H_

// Defined global variables
extern int AIOutput[3];

// Defined functions
//int randPick(int positions[]);
void defPos(int board[][3][3]);
void offPos(int board[][3][3]);
void updateFaces();
void buildBoard();
//void calculate();
//void determine(int gameboard[3][3][3], int aiPlayer, int oppPlayer, char aiName);

void determine(int gameboard[3][3][3], int aiPlayer, int oppPlayer, char aiName);
void evaluate(int * face[3][3], int aiPlayer, int offScale, int oppPlayer, int defScale);
void calculate(int * face[3][3], int row, int col, int scale);
bool primitiveCheck(int * face[3][3], int player, int primitiveNum);
int findMarker(int ai, int player);
int * searchCoordinates(int req, int * coor);

//void updateFaces(int board[3][3][3]);
//bool primitiveCheck(int * face[3][3], int player);

// If they're static methods, don't declare them, C can figure it out
//static int * findHorizIndex(int face[3][3], int row);
//static int * findVertIndex(int face[3][3], int col);
//static int * findTL_BRIndex(int face[3][3]);
//static int * findTR_BLIndex(int face[3][3]);
#endif