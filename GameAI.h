#ifndef _GAMEAI_H_
#define _GAMEAI_H_

// Defined functions
int evaluate(int board[][3][3]);
int randPick(int positions[]);
void defPos(int board[][3][3]);
void offPos(int board[][3][3]);

void updateFaces(int board[3][3][3]);
int * primitiveCheck(int face[3][3], int player);
static int * findHorizIndex(int face[3][3], int row);
static int * findVertIndex(int face[3][3], int col);
static int * findTL_BRIndex(int face[3][3]);
static int * findTR_BLIndex(int face[3][3]);
#endif