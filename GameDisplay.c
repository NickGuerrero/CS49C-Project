#include <stdio.h>
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
void gameInput();
bool turnOrder();
void playerWin(int num);

// Global variable
int PlayerOutput[3];

// Print-friendly Gameboard ---------------------------------------------------
char gameDisplay[592] = "\
                                         C\n\
                                         I-----I-----I-----I\n\
                     B                   |  1  |  2  |  3  |\n\
                     I-----I-----I-----I I-----I-----I-----I\n\
A                    |  1  |  2  |  3  | |  4  |  5  |  6  |\n\
I-----I-----I-----I  I-----I-----I-----I I-----I-----I-----I\n\
|  1  |  2  |  3  |  |  4  |  N  |  6  | |  7  |  8  |  9  |\n\
I-----I-----I-----I  I-----I-----I-----I I-----I-----I-----I\n\
|  4  |  5  |  6  |  |  7  |  8  |  9  |\n\
I-----I-----I-----I  I-----I-----I-----I\n\
|  7  |  8  |  9  |\n\
I-----I-----I-----I";

// These are the positions on the gameboard
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

void resetDisplay(){
    for(int i = 0; i < gameBoardSize; i++){
        int num = 1;
        for(int j = 0; j < gameBoardSize; j++){
            for(int k = 0; k < gameBoardSize; k++){
                updatePosition(i, j, k, num + '0');
                num++;
            }
        }
    }
    updatePosition(1,1,1,'N');
}

void updateDisplay(int gameboard[gameBoardSize][gameBoardSize][gameBoardSize]){
    for(int i = 0; i < gameBoardSize; i++){
        for(int j = 0; j < gameBoardSize; j++){
            for(int k = 0; k < gameBoardSize; k++){
                switch(gameboard[i][j][k]){
                    case -1:
                        updatePosition(i, j, k, 'X');
                        break;
                    case -2:
                        updatePosition(i, j, k, 'O');
                        break;
                }
            }
        }
    }
}

void updatePosition(int x, int y, int z, char letter){
    gameDisplay[slots[x][y][z]] = letter;
}

void displayBoard(){
    printf("%s\n", gameDisplay);
}

// User Interface Library -----------------------------------------------------
void gameIntroduction(){
    printf("Welcome to 3D Tic-Tac-Toe!\n");
}

void playerWin(int num){
    if(num != 0){
        printf("Player %d won!\n\n", num);
    } else {
        printf("The player won!\n\n");
    }
}

void aiWin(){
    printf("The AI won!\n\n");
}

char gameMenu(){
    char request;
    // User Prompt
    printf("What would you like to do?\n");
    printf("Play against the AI: (A)\n");
    printf("Play against another player: (V)\n");
    printf("Read the instructions: (R)\n");
    printf("Quit: (Q)\n");
    scanf(" %c", &request);

    // Choose the opponent
    if(request == 'A' || request == 'a'){
        printf("\nWho would you like to face against: Blinky (B), Inky (I), Pinky (P), or Clyde (C): ");
        scanf(" %c", &request);
    }
    return toupper(request);
}

bool turnOrder(){
    // Determine turn order
    bool active = false;
    char choice;
    while(!active){
        printf("\nWould you like to go first? (Y/N): ");
        scanf(" %c", &choice);
        switch(choice){
            case 'y':
            case 'Y':
                printf("\n");
                return true;
                break;
            case 'n':
            case 'N':
                printf("\n");
                return false;
                break;
        }
    }
    return false;
}

void gameInstructions(){
    printf("\nThe goal of the game is to create a line of three in a row before your opponent.\n");
    printf("Unlike regular tic-tac-toe though, you'll be working with three dimensions,\n");
    printf("leading to more complex rows that can cross multiple planes. You can play the game\n");
    printf("with a friend, or play against our AI opponent\n\n");
}

void gameInput(int turn){
    // Get the next move
    char depth = 'd';
    int pos = -1;
    printf("\nYour turn, Player %d: ", turn);
    scanf(" %c %d", &depth, &pos);
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

    // Store the value
    PlayerOutput[0] = x;
    PlayerOutput[1] = y;
    PlayerOutput[2] = z;
    return;
}