/*
 * This file contains helper functions
 * for all the binary tree related operations.
 */

#include <stdio.h>
#include "utilities.h"

/*
 * Create a new tree node.
 */
bt_node* bt_new_node(int val) {
    bt_node *new_node = NULL;

    new_node = (bt_node*)malloc(sizeof(bt_node));
    if (!new_node) {
        printf("Error in allocating memory to new node. Returning.");
        return NULL;
    }
    new_node->value = val;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

/*
 * Preorder tree traversal
 */
void preorder_traverse(bt_node *root) {
    if (root == NULL) {
        return;
    }
    printf("%d ", root->value);
    preorder_traverse(root->left);
    preorder_traverse(root->right);
}

/*
 * Inorder tree traversal
 */
void inorder_traverse(bt_node *root) {
    if (root == NULL) {
        return;
    }
    inorder_traverse(root->left);
    printf("%d ", root->value);
    inorder_traverse(root->right);
}

/*
 * Postorder tree traversal
 */
void postorder_traverse(bt_node *root) {
    if (root == NULL) {
        return;
    }
    postorder_traverse(root->left);
    postorder_traverse(root->right);
    printf("%d ", root->value);
}

