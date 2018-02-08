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

#ifndef _utilities.h
#define _utilities.h

/*
 * Linked List node
 */
typedef struct ll_node {
    int value;
    ll_node *next;
}ll_node;

/*
 * Binary Tree node
 */
typedef struct bt_node {
    int value;
    bt_node *left;
    bt_node *right;
}bt_node;

#endif
