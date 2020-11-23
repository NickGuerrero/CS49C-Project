#ifndef _GAMEDISPLAY_H_
#define _GAMEDISPLAY_H_

// Defined Global variables
extern int PlayerOutput[3];

// Main display functions
void resetDisplay();
void updateDisplay(int gameboard[3][3][3]);
void updatePosition(int x, int y, int z, char letter);
void displayBoard();

// Other display functions
void gameIntroduction();
char gameMenu();
void gameInstructions();
void gameInput();
bool turnOrder();
void playerWin(int num);
void aiWin();
#endif