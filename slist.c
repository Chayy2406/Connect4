#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Include the linked list header file
#include "slist.h"

// This is a function to create a new node for the linked list
struct Node* createNode(char board[ROWS][COLS], char player, int column) {
    // Provide memory for a new node
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));


    // Copy the game board state, player, and column to the new node
    memcpy(newNode->board, board, sizeof(char) * ROWS * COLS);
    newNode->player = player;
    newNode->column = column;
    newNode->next = NULL; // Set the next pointer to NULL
    // Return the newly created node
    return newNode;
}

// Function to insert a new node at the end of the linked list
void insertNode(struct Node** head, char board[ROWS][COLS], char player, int column) {
    // Create a new node with the given data
    struct Node* newNode = createNode(board, player, column);
    if (*head == NULL) {
        // If the linked list is empty, set the new node as the head
        *head = newNode;
    } else {
        // If the linked list is not empty, traverse to the end and add the new node
        struct Node* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

// Function to free the memory allocated for the linked list
void freeList(struct Node** head) {
    struct Node* current = *head;
    while (current != NULL) {
        struct Node* next = current->next;
        free(current); // Free the memory of the current node
        current = next; // Move to the next node
    }
    *head = NULL; // Set the head pointer to NULL
}
