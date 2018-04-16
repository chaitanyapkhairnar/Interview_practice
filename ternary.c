#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    char data;
    struct node *left;
    struct node *right;
}node;

typedef struct stack_node {
    struct node *tree_node;
    struct stack_node *next;
}stack_node;

void stack_push(node *tree_node, stack_node **head) {
    stack_node *new_node = (stack_node*)malloc(sizeof(stack_node));
    new_node->tree_node = tree_node;
    if(*head == NULL) {
        new_node->next = NULL;
        *head = new_node;
    } else {
        new_node->next = *head;
        *head = new_node;
    }
}

node* stack_pop(stack_node **head) {
    if(*head == NULL) {
        return NULL;
    }
    stack_node *free_node = *head;
    node *temp = free_node->tree_node;
    *head = (*head)->next;
    free(free_node);
    return temp;
}

node* ternary_to_tree(char *str, int len, int start) {
    node *root, *temp;
    stack_node *head;
    if(start >= len) {
        return NULL;
    }
    root = (node*)malloc(sizeof(node));
    root->data = str[start];
    root->left = NULL;
    root->right = NULL;

    start++;

    if((start < len) && (str[start] == '?')) {
        stack_push(root, &head);
        root->left = ternary_to_tree(str, len, start+1);
    } else if((start<len) && (str[start] == ':')) {
        temp = stack_pop(&head);
        while(temp && (!temp->right)) {
            temp = stack_pop(&head);
        }
        if(!temp) {
            return NULL;
        } else {
            stack_push(temp, &head);
            temp->right = ternary_to_tree(str, len, start+1);
        }
    }
    return root;
}

void print_tree(node *root) {
    if(root == NULL) {
        return;
    }
    print_tree(root->left);
    printf("%c ", root->data);
    print_tree(root->right);
    return;
}

int main(void) {
    node *root;
    char str[6] = {'a', '?', 'b', ':', 'c'};
    root = ternary_to_tree(str, 5, 0);
    print_tree(root);
    printf("\n");

    return 0;
}
