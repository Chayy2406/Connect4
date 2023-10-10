#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Here, we are including the header file
#include "slist.h"


#define ROWS 6
#define COLS 7

/*-------------------------------------------------
 initializeBoard
 This function is used to create the board for the
 users to play on using the 2D arrays
 -------------------------------------------------*/
void initializeBoard(char board[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            board[i][j] = ' ';
        }
    }
}

/*-------------------------------------------------
 displayBoard
This function is used to display the board that was
created by using a for loop
 -------------------------------------------------*/
void displayBoard(char board[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
        	//Now we print the contents present in the array
            printf("|%c", board[i][j]);
        }

        printf("|\n");
    }
    //This string acts like a base to the board
    printf("===================\n");
}


/*-------------------------------------------------
 checkWin
This function checks to see if the tokens align diagonally,
vertically or horizontally to see if either of the player
has won the game or not.
 -------------------------------------------------*/
int checkWin(char board[ROWS][COLS], char player, int row, int col) {
    // Check horizontally
    int count = 0;
    for (int i = col - 3; i <= col + 3; i++) {
        if (i >= 0 && i < COLS && board[row][i] == player) {
            count++;
            if (count == 4) return 1;	//Makes sure that the player wins if 4 tokens are found in a row
        } else {
        	//if there are other tokens, then the streak breaks
            count = 0;
        }
    }

    // Check vertically
    count = 0;
    for (int i = row - 3; i <= row + 3; i++) {
        if (i >= 0 && i < ROWS && board[i][col] == player) {
            count++;
            if (count == 4) return 1; //Makes sure that the player wins if 4 tokens are found in a column
        } else {
        	//if there are other tokens, then the streak breaks
            count = 0;
        }
    }

    // Check diagonally (bottom-left to top-right)
    count = 0;
    for (int i = -3; i <= 3; i++) {
        int r = row + i;
        int c = col - i;
        if (r >= 0 && r < ROWS && c >= 0 && c < COLS && board[r][c] == player) {
            count++;
            if (count == 4) return 1; //Makes sure that the player wins if 4 tokens are found in a diagonal
        } else {
        	//if there are other tokens, then the streak breaks
            count = 0;
        }
    }

    // Check diagonally (top-left to bottom-right)
    count = 0;
    for (int i = -3; i <= 3; i++) {
        int r = row - i;
        int c = col - i;
        if (r >= 0 && r < ROWS && c >= 0 && c < COLS && board[r][c] == player) {
            count++;
            if (count == 4) return 1; //Makes sure that the player wins if 4 tokens are found in a diagonal
        } else {
        	//if there are other tokens, then the streak breaks
            count = 0;
        }
    }

    return 0;
}

/*-------------------------------------------------
 resetGame
This function is used to reset the game and always
assign the current player to be R
 -------------------------------------------------*/
void resetGame(char board[ROWS][COLS], struct Node** movesList, char* currentPlayer) {
    initializeBoard(board); //This is used to rewrite the game board all over again
    freeList(movesList);//This frees the linked list
    //This line ensures that the player who starts the game is always R
    *currentPlayer = (currentPlayer == 'R') ? 'R' : 'Y';
}

/*---------------------------------------------
main
This is where the whole code works. Inputting, calling
functions, etc.
--------------------------------------------- */
int main() {
    char board[ROWS][COLS];
    char currentPlayer = 'R'; // Start with 'R'
    int column;
    int moveCount = 0;
    //Now we initialize a linked list to store the moves.
    struct Node* movesList = NULL;

    printf("Welcome! Press any key to continue or 'q' to quit.\n");
    char startChoice;
    scanf(" %c", &startChoice);

    if (startChoice != 'q') {
        while (1) {
        	//This is where the game truly starts, with the loop
            initializeBoard(board); // Initialize a new game board
            displayBoard(board); //Now we display the board

            while (1) {
                printf("%c to play. Pick a column (1-7): ", currentPlayer);
                scanf("%d", &column);
                column--; // Adjust for 0-based indexing

                // Now we check if the column is valid and not full
                if (column < 0 || column >= COLS || board[0][column] != ' ') {
                    printf("Invalid move. Try again.\n");
                    continue;
                }

                // These lines of code try to find the empty rows to put the tokens in
                int row;
                for (row = ROWS - 1; row >= 0; row--) {
                    if (board[row][column] == ' ') {
                        board[row][column] = currentPlayer;
                        break;
                    }
                }

                // We now store this move in the linked lit
                insertNode(&movesList, board, currentPlayer, column);

                //Here we display the game board after a move was made
                displayBoard(board);

                // Check for a win
                if (checkWin(board, currentPlayer, row, column)) {
                    printf("You win, %c!\n", currentPlayer);
                    printf("Good game!\n");

                    // Now we ask if a player wants to quit, replay or start a new game
                    char choice;
                    printf("Press 'q' to quit, 'r' to replay, or any other key to continue: ");
                    scanf(" %c", &choice);

                    if (choice == 'q') {
                        freeList(&movesList); // Free the linked list
                        exit(0); // Quit the program
                    } else if (choice == 'r') {
                        //If the players want to go over their steps, they choose r
                        struct Node* currentMove = movesList;
                        while (currentMove != NULL) {
                            displayBoard(currentMove->board);
                            currentMove = currentMove->next;
                        }
                        printf("Press 'q' to quit or any other key to continue: ");
                        char replayChoice;
                        scanf(" %c", &replayChoice);
                        if (replayChoice == 'q') {
                            freeList(&movesList); // Free the linked list
                            exit(0); // Quit the program
                        }
                        resetGame(board, &movesList, &currentPlayer);
                        displayBoard(board);
                    } else {
                        resetGame(board, &movesList, &currentPlayer);
                        displayBoard(board);
                    }
                }

                // Switch players
                currentPlayer = (currentPlayer == 'R') ? 'Y' : 'R';
                moveCount++;

                // Check for a draw
                if (moveCount == ROWS * COLS) {
                    printf("It's a draw!\n");
                    break;
                }
            }
        }
    }

    return 0;
}
