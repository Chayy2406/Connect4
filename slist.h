#ifndef SLIST_H
#define SLIST_H

//Defining the rows and columns for the game board
#define ROWS 6
#define COLS 7

//Now we define a structure to represent a node
struct Node {
    char board[ROWS][COLS]; //We look at the game board
    char player; //The player who makes the move
    int column; //The column where the player dropped the token
    struct Node* next; //This is a pointer to the next node
};
//Now we create a new node with the given rows, columns and players
struct Node* createNode(char board[ROWS][COLS], char player, int column);
//here we insert a new node at the beginning
void insertNode(struct Node** head, char board[ROWS][COLS], char player, int column);
//Now we free the memory
void freeList(struct Node** head);

#endif
