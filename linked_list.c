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
    node->next = NULL;
    free(node);
    node = NULL;
    return 0;
}

/*
 * Function to insert node at the front of list
 */
void ll_insert_front(ll_node **head, int val) {
    ll_node *new_node;
    new_node = ll_add_node(val);

    new_node->next = *head;
    *head = new_node;
    return;
}

/*
 * Function to insert node after the node with given value
 */
void ll_insert_after_position(ll_node *head, int new_val, int search_val) {
    if(head == NULL) {
        printf("List is empty.\n");
        return;
    }
    ll_node *new_node, *temp_node;
    new_node = ll_add_node(new_val);
    temp_node = head;

    while(temp_node->value != search_val) {
        temp_node = temp_node->next;
        if (temp_node == NULL) {
            printf("Node with given value not present in the List.\n");
            return;
        }
    }
    /* We found the node with the search_val. Now add new_node after this node. */
    new_node->next = temp_node->next;
    temp_node->next = new_node;
    return;
}

/*
 * Function to insert node at the end of the list.
 */
void ll_insert_at_end(ll_node **head, int val) {
    ll_node *new_node, *temp_node;
    new_node = ll_add_node(val);
    temp_node = *head;

    if(*head == NULL) {
        *head = new_node;
        return;
    }
    while(temp_node->next) {
        temp_node = temp_node->next;
    }
    /* We are at the last node. Insert after this node. */
    temp_node->next = new_node;
    return;
}

/*
 * Function to delete node with given value from the list.
 */
void ll_delete_node_with_value(ll_node **head, int val) {
    if(*head == NULL) {
        printf("List is empty. Nothing to delete.\n");
        return;
    }
    ll_node *delete_node;
    if(*head->val == val) {
        /* We need to delete the head node. */
        delete_node = *head;
        *head = (*head)->next;
        if(!ll_free_node(delete_node)) {
            printf("Some error while freeing the node.\n");
        }
        return;
    }

    ll_node *temp = *head;
    while(temp->next->value != val) {
        temp = temp->next;
        if(temp == NULL) {
            printf("Value not found in the list.\n");
            return;
        }
    }
    /* We found the previous node of the node to be deleted. */
    delete_node = temp->next;
    temp->next = delete_node->next;
    if(!ll_free_node(delete_node)) {
        printf("Some error while freeing the node.\n");
    }
    return;
}

/*
 * Function to delete node at the given position.
 * Position 0 means head node.
 */
void ll_delete_node_at_position(ll_node *head, int pos) {
    if(head == NULL) {
        printf("The list is empty.\n");
        return;
    }
    ll_node *temp = head;
    if(pos == 0) {
        /* Delete the head node */
        head = temp->next;
        if(!ll_free_node(temp)) {
            printf("Some error while freeing the node.\n");
        }   
        return;
    }
    int count = 0;
    ll_node *prev = NULL;
    while(temp) {
        prev = temp;
        temp = temp->next;
        count++;
        if(count == pos) {
            break;
        }
    }
    if (temp == NULL) {
        /* List is smaller than the given position. Nothing to delete. */
        printf("Given position is larger than the list size. Not deleting\n");
        return;
    }
    /* Now we have reference to the node to be deleted and its previous node. */
    prev->next = temp->next;
    if(!ll_free_node(temp)) {
        printf("Some error while freeing the node.\n");
    }
    return;
}

/*
 * Function to find the length of list iteratively
 */
int ll_get_len_iteratively(ll_node *head) {
    int count = 0;
    ll_node *temp = head;
    
    while(temp) {
        temp = temp->next;
        count++;
    }
    return count;
}

/*
 * Function to find the length of list recursively
 */
int ll_get_len_recursively(ll_node *head) {
    if(head == NULL) {
        return 0;
    }
    return (ll_get_len_recursively(head->next) + 1);
}

/*
 * Function to search an element in list iteratively.
 * Return true if node found else return false.
 */
bool ll_search_iteratively(ll_node *head, int val) {
    ll_node *temp = head;
    while(temp) {
        if(temp->value == val) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

/* 
 * Function to search an element in list recursively.
 */
bool ll_search_recursively(ll_node *head, int val) {
    if(head == NULL) {
        return false;
    }
    if(head->value == val) {
        return true;
    }
    return ll_search_recursively(head->next, val);
}

/*
 * Function to swap two elements in the list.
 */
void ll_swap_nodes(ll_node *head, int val1, int val2) {
    if(head == NULL || val1 == val2) {
        printf("List is empty. Returning.\n");
        return;
    }
    ll_node *temp = head;
    ll_node *node1_prev = NULL, *node2_prev = NULL;
    ll_node *node1_curr = NULL, *node2_curr = NULL;
    while(temp->next) {
        if(temp->next->value == val1) {
            node1_prev = temp;
            node1_curr = node1_prev->next;
        } else if(temp->next->value == val2) {
            node2_prev = temp;
            node2_curr = node2_prev->next;
        }
        if(node1_curr && node2_curr) {
            break;
        }
        temp = temp->next;
    }
    if(head->value == val1) {
        node1_curr = head;
    } else if (head->value == val2) {
        node2_curr = head;
    }
    if(node1_curr == NULL || node2_curr == NULL) {
        printf("Nodes to be swapped not found. Returning\n");
        return;
    }
    /* We found both the nodes to be swapped */

    /*
     * eg1. We have to swap 3 with 5                                    eg2. We have to swap head and 5
     *
     * 1 -> 2 -> 3 -> 4 -> 5 -> NULL                                    1 - 2 - 3 - 4 - 5 - NULL
     * h   n1p  n1c  n2p  n2c                                           n1c        n2p n2c
     *
     * Step 1: After swapping the next pointers of node1_prev and node2_prev
     *                                n1c     n2p                       n1c         n2p   n2c
     * 1  ->  2  ->  5  ->  NULL       3  ->  4                          1 - 2 - 3 - 4     5 - NULL
     * h     n1p    n2c                ^      |                          ^           |
     *                                 |      |                          |           |
     *                                 +------+                          +-----------+
     *
     * Step 2: After swapping the next pointers of node1_curr and node2_curr
     *
     * 1  ->  2  ->  5  ->  4  ->  3  ->  NULL                           5 - 2 - 3 - 4 - 1 - NULL
     * h     n1p    n2c    n2p    n1c                                   n2c         n2p n1c
     *
     */

    /* First swap the next pointers of node1_prev and node2_prev */
    if(node1_prev) {
        node1_prev->next = node2_curr;
    }
    if(node2_prev) {
        node2_prev->next = node1_curr;
    }

    /* Now swap the next pointers of node1_curr and node2_curr */
    ll_node *temp1 = node1_curr->next;
    node1_curr->next = node2_curr->next;
    node2_curr->next = temp1;

    /* Adjust the head if any of the nodes swapped was a head node. */
    if(!node1_prev) {
        head = node2_curr;
    }
    if(!node2_prev) {
        head = node1_curr;
    }
    return;
}

/* 
 * Function to get the Nth node from start of list iteratively.
 * head is the 0th node.
 */
ll_node* ll_get_nth_start(ll_node *head, int val) {
    if(head == NULL) {
        printf("Empty list.");
        return NULL;
    }
    int count = 0;
    ll_node *temp = head;
    while(temp && (count != val)) {
        temp = temp->next;
        count++;
    }
    if(temp == NULL) {
        printf("Linked list does not have %dth node.\n", val);
        return NULL;
    }
    return temp;
}

/*
 * Function to get the Nth node from start of list recursively.
 * head is the 0th node.
 */
ll_node* ll_get_nth_start_recursively(ll_node *head, int val) {
    if(head == NULL) {
        return NULL;
    }
    int count = 0;
    if(count == val) {
        return head;
    }
    return ll_get_nth_start_recursively(head->next, val-1);
}

/*
 * Function to get the middle node of the list.
 * If list is of even length, get the second middle element.
 */
ll_node* ll_get_middle_node(ll_node *head) {
    if(head == NULL) {
        printf("List is empty.\n");
        return NULL;
    }
    ll_node *first, *second;
    first = head;
    second = head;
/*
 * We use two pointers. one traverses 1 step and another traverses 2 steps.
 * So when the second pointer reaches end, first should be at middle.
 * 
 * eg1. 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> NULL
 *
 * at the end of while loop, second will point at 7 and first will point at 4
 * so first is the middle node.
 *
 * eg2. 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> 8 -> NULL
 *
 * at the end of while loop, second will point at NULL and first will point at 5
 * 4 and 5 are the 2 middle nodes and we want the second one which is 5 and we got it.
 */
    while(second && second->next) {
        first = first->next;
        second = second->next->next;
    }
    return first;
}

/*
 * Function to get nth node from the end of the list.
 * last node is the 1st node from the end.
 */
ll_node* ll_get_nth_end(ll_node *head, int pos) {
    if(head == NULL) {
        printf("Empty list.\n");
        return NULL;
    }
    int i;
    ll_node *back = head;
    ll_node *front = head;
    while(front) {
        for(i=0;i<pos;i++) {
            front = front->next;
            if(front == NULL) {
                printf("List is small.\n");
                return NULL;
            }
        }
        back = back->next;
        front = front->next;
    }
    return back;
}

/*
 * Function to delete the entire list
 */
void ll_delete_all(ll_node *head) {
    if(head == NULL) {
        printf("List is empty.\n");
        return;
    }
    ll_node *temp = head->next;
    while(temp) {
        ll_free_node(head);
        head = temp;
        temp = temp->next;
    }
    ll_free_node(head);
    return;
}

/*
 * Function to count the number of occurances of given key in list
 */
int ll_count_occurances(ll_node *head, int key) {
    if(head == NULL) {
        printf("List is empty.\n");
        return 0;
    }
    ll_node *temp = head;
    int count = 0;
    while(temp) {
        if(temp->value == key) {
            count++;
        }
        temp = temp->next;
    }
    return count;
}

/*
 * Function to count the number of occurances of given key in list recursively
 */
int ll_count_occurances_recursively(ll_node *head, int key) {
    int count = 0;
    if(head == NULL) {
        return 0;
    }
    if(head->value == key) {
        count++;
    }
    return count + ll_count_occurances_recursively(head->next, key);
}

/*
 * Function to reverse the list
 */
ll_node* ll_reverse(ll_node *head) {
    if(head == NULL) {
        printf("List is empty.\n");
        return NULL;
    }
    ll_node *prev = NULL, *curr = NULL, *next = NULL;
    curr = head;

    while(curr) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    head = prev;
    return head;
}

/*
 * Function to reverse the list recursively
 * TODO: Verify this.
 */
void ll_reverse_recursive(ll_node *head) {
    if(head == NULL) {
        return;
    }
    ll_node *first;
    ll_node *rest;

    first = head;
    rest = first->next;

    if(rest == NULL) {
        return;
    }
    ll_reverse_recursive(rest);
    first->next->next = first;
    first->next = NULL;
    head = rest;
}

/*
 * Function to detect loop in the list
 * returns true if loop found, else false.
 */
bool ll_find_loop(ll_node *head) {
    if(head == NULL) {
        printf("List is empty.\n");
        return false;
    }
    ll_node *slow = head, *fast = head;
    while(slow && fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if(slow == fast) {
            return true;
        }
    }
    return false;
}

/*
 * Function to merge two sorted lists together
 */
ll_node* ll_merge_sorted_lists(ll_node *list1, ll_node *list2) {


}
