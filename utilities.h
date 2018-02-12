/*
 *
 * Author: Chaitanya
 *
 * File: utilities.h
 *
 * Info: This is a utility header file containing basic
 *       structure definitions, function declarations
 *       and MACRO definitions.
 *
 */

#ifndef _utilities_h         // To avoid multiple inclusions of this header file
#define _utilities_h         // Use any name. using _<filename>_h to be unique

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
 * Linked List node
 */
typedef struct ll_node {
    int value;
    struct ll_node *next;
}ll_node;

/*
 * Queue data structure
 */
typedef struct queue {
    ll_node *front, *rear;
}queue;

/*
 * Binary Tree node
 */
typedef struct bt_node {
    int value;
    struct bt_node *left;
    struct bt_node *right;
}bt_node;

/* Function declarations */

ll_node* ll_add_node (int);
int ll_free_node (ll_node *);
ll_node* ll_insert_node (ll_node *, int, int);

queue* initialize_queue(void);
ll_node* new_queue_node(int);
void enqueue(queue *, int);
int dequeue(queue *);

bt_node* bt_new_node(int);
bt_node* bt_insert_left(bt_node *, int);
bt_node* bt_insert_right(bt_node *, int);
void preorder_traverse(bt_node *);
void inorder_traverse(bt_node *);
void postorder_traverse(bt_node *);
int bt_get_height(bt_node *);

#endif
