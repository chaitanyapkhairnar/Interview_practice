/*
 *
 * Author: Chaitanya
 *
 * File: linked_list.c
 *
 * Info: This file contains all the operations
 *       related to linked lists. 
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "utilities.h"

/*
 * Info: Function to create a new linked list node
 * with the given value.
 *
 * Arguments: val - Value field of the new node
 *
 * Return type: ll_node - Newly created node
 */
ll_node* ll_add_node (int val) {
    ll_node *new_node = NULL;

    new_node = (ll_node*)malloc(sizeof(ll_node));
    if(!new_node) {
        printf("Failed to allocate memory to ll_node structure. Returning");
        return NULL;
    }
    new_node->value = val;
    new_node->next = NULL;
    return new_node;
}

/*
 * Info: Function to free memory of the given node.
 *
 * Arguments: node - ll_node type node which needs
 *                   to be freed.
 *
 * Return type: int - 0 if successfull -1 if error.
 */
int ll_free_node (ll_node *node) {
    if (!node) {
        printf("Given node does not exists. Returning error.");
        return -1;
    }
    free(node);
    node = NULL;
    return 0;
}

/*
 * Info: Function to insert a linked list node
 *       to the given list at given position.
 *
 * Arguments: head - ll_node type pointer to head of
 *                   list.
 *            pos - integer type variable for position.
 *            val - integer type value for new node.
 *
 * Return type: ll_node - Head node of the list.
 */
ll_node* ll_insert_node (ll_node *head, int pos, int val) {
    ll_node *new_node = NULL;

    if (!head) {
        printf("Head node is NULL. Returning.");
        return head;
    }
    if (pos < 0) {
        printf("Error. Invalid position to insert new node. Returning.");
        return head;
    }
    /* if pos is 0, that means add new node before
     * head node and make this new head.
     */
    if (pos == 0) {
        new_node = ll_add_node(val);
        if (!new_node) {
            printf("Error while adding new node. Returning.");
            return head;
        }
        new_node->next = head;
        head = new_node;
        return head;
    } else {
        ll_node *temp = head;
        int i = 1;
        for (;i<pos;i++) {
            temp = temp->next;
        }
        if (i < pos) {
            /* Length of Linked List is smaller
             * than then position. Print error
             * and return.
             */
            printf("Error. Linked list is small. Cannot insert. Returning");
            return head;
        }
        new_node = ll_add_node(val);
        if (!new_node) {
            printf("Error while adding new node. Returning.");
            return head;
        }
        new_node->next = temp->next;
        temp->next = new_node;
        return head;
    }
}
