#include <stdio.h>
#define gameBoardSize 3

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

void updatePosition(int x, int y, int z, char letter){
    gameDisplay[slots[x][y][z]] = letter;
}

void displayBoard(){
    printf("%s\n", gameDisplay);
}

void testEdit(){
    printf("\n%d", slots[0][0][0]);
    gameDisplay[slots[0][0][0]] = 'X';
}