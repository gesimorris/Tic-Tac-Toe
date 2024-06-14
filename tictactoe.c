#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define SIZE 3

// Function headers
void showInstructions();
void initializeTable();
void playGame();
bool checkDraw(char board[SIZE][SIZE]);
bool checkWin(char board[SIZE][SIZE], char sign);
bool placeSign(char board[SIZE][SIZE], int x, int y, char sign);
void updateTable();
void showBoard(char board[SIZE][SIZE]);
void cpuMove(char board[SIZE][SIZE]);

// Variables
char board[SIZE][SIZE]; // Game board
int x, y;   // User and CPU signs
char comma;
int coordinates;
bool gameWon = false;
bool gameDraw = false;

int main(){
    
    showInstructions();
    playGame();
}

void showInstructions(){
    
    char name[] = "";
    
    printf("%s","***************************\n");
    printf("%s","Tic Tac Toe\n");
    printf("%s","COMP 2130 Winter 2024\n");
    printf("%s","You will be playing against the computer\n");
    printf("%s","***************************\n\n");
    
    
    // Ask user for name and print instructions for the game
    printf("%s","What is your name?\n");
    scanf("%s",&name);
    printf("\nHello %s ... Lets have fun !!! You = X | Computer = O",name);
    printf("%s","\nIndexing starts at 0");
    
    initializeTable();
}

void playGame(){
    
    int turn = 0;
    
    // Loop until the someone has won or the game is a draw
    while(!gameWon && !gameDraw){
        
        // Users turn to play
        if (turn == 0){
            updateTable();
            
            // Check if a sign has been placed already in a cell when placing a sign
            if(!placeSign(board,x,y,'X')){
                printf("Cell already occupied. Please try again.\n");
                continue;
            }
        }
        
        // Computers turn to play
        else {
            cpuMove(board);
        }
        
        // Stop loop if someone has won
        gameWon = checkWin(board, turn == 0 ? 'X' : 'O');
        
        // Stop loop is game ends in a draw
        gameDraw = checkDraw(board);
        
        // Alternate turns until the end of the game
        turn = (turn + 1) % 2;
        
        showBoard(board);
    }
    
    
    
    // Show that the user has won
    if (gameWon && !turn % 2 == 0) {
        printf("********\n");
        printf("You Won!\n");
        printf("********\n");
    
    // Show that CPU has won
    } 
    else if(gameWon && turn % 2 == 0){
        printf("********\n");
        printf("CPU Won!\n");
        printf("********\n");
    }
    
    // Show that it is a draw
    else {
        printf("************\n");
        printf("It's a draw!\n");
        printf("************\n");
    }
    
    showBoard(board);
    
}

// Function that returns true if game ends in a draw
bool checkDraw(char board[SIZE][SIZE]){
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == ' ') return false;
        }
    }
    return true;
}

// Function that returns true if someone has won
bool checkWin(char board[SIZE][SIZE], char sign){
    // Check rows and columns
    for (int i = 0; i < SIZE; i++) {
        if ((board[i][0] == sign && board[i][1] == sign && board[i][2] == sign) ||
            (board[0][i] == sign && board[1][i] == sign && board[2][i] == sign)) {
            return true;
        }
    }
    // Check diagonals
    if ((board[0][0] == sign && board[1][1] == sign && board[2][2] == sign) ||
        (board[0][2] == sign && board[1][1] == sign && board[2][0] == sign)) {
        return true;
    }
    return false;
}

// Function that prompts the user to enter coordinates to place the sign
void updateTable(){
     while (1) {
        // Prompt user to enter coordinates
        printf("Enter coordinates in the form X,Y: ");

        // Read the input including the comma
        coordinates = scanf("%d %c %d", &x, &comma, &y);

        // Clear the input buffer to handle any extra invalid input
        while (getchar() != '\n');  
        
        if (x < 0 || x >= SIZE || y < 0 || y >= SIZE) {
            printf("Coordinates out of range. Please try again.\n");
            continue;
        }

        // Check if the input was valid
        if (coordinates == 3 && comma == ',') {
            // Valid input, break the loop
            break;
        }
        
        // Invalid input, inform the user
        printf("Invalid input. Please enter in the form X,Y.\n");
    }
}

// Function that places the sign 
bool placeSign(char board[SIZE][SIZE], int x, int y, char sign){
    if(board[x][y] != ' ') return false;
    board[x][y] = sign;
    return true;
        
}
// Function that shows the board after a turn
void showBoard(char board[SIZE][SIZE]) {
    printf("\n");
    for (int i = 0; i < SIZE; i++) 
    {
        for (int j = 0; j < SIZE; j++) 
        {
            printf(" %c ", board[i][j]);
            if (j < SIZE - 1) printf("|");
        }
        printf("\n");
        if (i < SIZE - 1) printf("---|---|---\n");
    }
    printf("\n");
}
// Function that shows the table and how to place a sign
void initializeTable(){
    printf("\n");
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            board[i][j] = ' ';
            printf(" %c ", board[i][j]);
            if (j < SIZE - 1) printf("|");
            
        }
        printf("\n");
        if (i < SIZE - 1) printf("---|---|---\n");
    }
    printf("\n");
}

// Function that uses random numbers to simulate the computer's turn
void cpuMove(char board[SIZE][SIZE]) {
    int tempx, tempy;
    
    while (board[tempx][tempy] != ' '){
        tempx = rand() % SIZE;
        tempy = rand() % SIZE;
    }
    
    board[tempx][tempy] = 'O';
    printf("CPU O placed at %d,%d\n", tempx, tempy);
}



