#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#define gameBoardSize 3

// Functions
void updatePosition(int x, int y, int z, char letter);
void displayBoard();
void testEdit();
void gameIntroduction();
char gameMenu();
void gameInstructions();
int * gameInput();

// Print-friendly Gameboard ---------------------------------------------------
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

// User Interface Library -----------------------------------------------------
void gameIntroduction(){
    printf("\nWelcome to 3D Tic-Tac-Toe!\n");
}

char gameMenu(){
    char request;
    // User Prompt
    printf("What would you like to do?\n");
    printf("Play against the AI: (A)\n");
    printf("Play against another player: (B)\n");
    printf("Read the instructions: (R)\n");
    printf("Quit: (Q)\n");
    //fflush(stdout);
    scanf("%c", &request);
    // Special Prompt for AI behavior
    if(request == 'A'){
            printf("\nWould you like to go first? (Y/N): ");
            scanf("%c", &request);
    }
    return toupper(request);
}

void gameInstructions(){
    printf("The goal of the game is to create a line of three in a row before your opponent.\n");
    printf("Unlike regular tic-tac-toe though, you'll be working with three dimensions,\n");
    printf("leading to more complex rows that can cross multiple planes. You can play the game");
    printf("with a friend, or play against our AI opponent\n");
}

int * gameInput(int turn){
    // Get the next move
    char depth;
    int pos;
    printf("\nYour turn, Player %d: ", (turn % 2));
    scanf("%c, %d", &depth, &pos);
    // Convert move into a valid position on the board
    int x,y,z;
    x = y = z = -1;
    switch(depth){
        case 'A':
        case 'a':
                x = 0;
                break;
        case 'B':
        case 'b':
                x = 1;
                break;
        case 'C':
        case 'c':
                x = 2;
                break;
    }
    // Find values for the 2d array
    if(pos > 0 && pos < 10){
        if(pos < 4){
            y = 0;
        } else if(pos < 7){
            y = 1;
        } else {
            y = 2;
        }
        z = (pos - 1) % 3;
    }
    //int arr[3] = {x,y,z};
    // using malloc to solve problems
    int* ptr = (int*) malloc(3 * sizeof(int));
    ptr[0] = x;
    ptr[1] = y;
    ptr[2] = z;
    return ptr;
}