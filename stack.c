/*
 * This file contains basic stack implementation using
 * Linked List as base datastructure.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* Node structure for linked list */
typedef struct node {
    int val;
    struct node *next;
}node;

/* Push function to push new value into stack */
void stack_push(node **head, int val) {
    node *new_node = (node *)malloc(sizeof(node));
    new_node->val = val;
    if(*head == NULL) {
        new_node->next = NULL;
        *head = new_node;
    } else {
        new_node->next = *head;
        *head = new_node;
    }
    return;
}

/* Pop function to pop topmost element from the stack */
int stack_pop(node **head) {
    int val;
    node *temp = *head;
    if(temp == NULL) {
        printf("Stack is already empty. Nothing to Pop\n");
        return -1;
    }
    *head = (*head)->next;
    val = temp->val;
    free(temp);
    return val;
}
/* Utility function to print the current stack */
void print_list(node *head) {
    printf("Current Stack is: \n");
    while(head) {
        printf("%d ", head->val);
        head = head->next;
    }
    printf("\n");
}

/* Main function */
int main(void) {
    node *head = NULL;
    stack_push(&head, 1);
    stack_push(&head, 2);
    stack_push(&head, 3);
    stack_push(&head, 4);
    print_list(head);
    printf("Popped %d\n", stack_pop(&head));
    printf("Popped %d\n", stack_pop(&head));
    print_list(head);
    stack_push(&head, 5);
    stack_push(&head, 6);
    printf("Popped %d\n", stack_pop(&head));
    printf("Popped %d\n", stack_pop(&head));
    printf("Popped %d\n", stack_pop(&head));
    printf("Popped %d\n", stack_pop(&head));
    printf("Popped %d\n", stack_pop(&head));
    print_list(head);
    stack_push(&head, 1);
    stack_push(&head, 2);
    stack_push(&head, 3);
    stack_push(&head, 4);
    stack_push(&head, 5);
    stack_push(&head, 6);
    print_list(head);
    return 0;
}
