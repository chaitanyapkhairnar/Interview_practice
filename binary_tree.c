/*
 * This file contains helper functions
 * for all the binary tree related operations.
 */

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
 * Insert node on left.
 */
bt_node* bt_insert_left(bt_node *root, int val) {
    bt_node *new_node;

    new_node = bt_new_node(val);
    if(!root->left) {
        root->left = new_node;
        return root;
    } else {
        new_node->left = root->left;
        root->left = new_node;
        return root;
    }
}

/*
 * Insert node on right.
 */
bt_node* bt_insert_right(bt_node *root, int val) {
    bt_node *new_node;

    new_node = bt_new_node(val);
    if(!root->right) {
        root->right = new_node;
        return root;
    } else {
        new_node->right = root->right;
        root->right = new_node;
        return root;
    }
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

/*
 * Height of the tree
 */
int bt_get_height(bt_node *root) {
    int left_height = 0, right_height = 0;
    if (root == NULL) {
        return 0;
    }
    left_height = bt_get_height(root->left);
    right_height = bt_get_height(root->right);

    if (left_height > right_height) {
        return left_height+1;
    } else {
        return right_height+1;
    }
}
