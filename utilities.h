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

/*
 * Linked List node
 */
typedef struct ll_node {
    int value;
    struct ll_node *next;
}ll_node;

/*
 * Binary Tree node
 */
typedef struct bt_node {
    int value;
    struct bt_node *left;
    struct bt_node *right;
}bt_node;

#endif
