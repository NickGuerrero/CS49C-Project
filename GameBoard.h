//
// Created by ricky on 11/19/20.
//

#ifndef INC_49CPROJECT_GAMEBOARD_H
#define INC_49CPROJECT_GAMEBOARD_H

// Base functionality
void initGameBoard();
int isValidMove(int i, int j, int k);
int isValidIndex(int i, int j, int k);
void printGameBoard();

// Checking win conditions
bool checkWin(int player);
bool horizontalCheck(int player);
bool verticalCheck(int player);
bool diagFrontBackCheck(int player);
bool diagTopBotCheck(int player);
bool diagLeftRightCheck(int player);
bool sideFaceCheck(int player);

// Gameplay functions
bool playHumanGame();
bool playAIGame(bool first, char aiName);
#endif //INC_49CPROJECT_GAMEBOARD_H
