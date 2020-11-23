#ifndef _GAMEDISPLAY_H_
#define _GAMEDISPLAY_H_

// Defined Global variables
extern int PlayerOutput[3];

// Defined functions
void updatePosition(int x, int y, int z, char letter);
void displayBoard();
void testEdit();
void gameIntroduction();
char gameMenu();
void gameInstructions();
void gameInput();
bool turnOrder();
void playerWin(int num);
void aiWin();
void updateDisplay(int gameboard[3][3][3]);
void resetDisplay();

#endif