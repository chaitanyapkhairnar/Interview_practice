/*
 * This file contains queue related operations.
 */

#include "utilities.h"

/*
 * initialize a new queue
 */
queue* initialize_queue(void) {
    queue *q = (queue*)malloc(sizeof(queue));
    q->front = q->rear = NULL;
    return q;
}

/*
 * create a new queue node
 */
ll_node* new_queue_node(int val) {
    ll_node *new_node;
    new_node = (ll_node*)malloc(sizeof(ll_node));
    new_node->next = NULL;
    new_node->value = val;
    return new_node;
}

/*
 * enqueue operation
 * We add new node on the rear and shift rear pointer to left
 */
void enqueue(queue *q, int val) {
    ll_node *temp;
    temp = new_queue_node(val);

    /* Check if queue is empty. */
    if(q->rear == NULL) {
        q->front = q->rear = temp;
        return;
    } else {
        /* Add this new node to rear and move rear pointer */
        q->rear->next = temp;
        q->rear = temp;
        return;
    }
}

/*
 * dequeue operation
 * We remove the node from the front and shift front pointer to left
 */
int dequeue(queue *q) {
    ll_node *temp;
    int value;

    /* Handle empty queue condition */
    if(q->front == NULL) {
        printf("The queue is empty. Returning error.\n");
        return -1;
    }
    temp = q->front;
    q->front = temp->next;
    /* Handle condition where there was only 1 node
     * in the queue and so after we dequeue, q->front
     * now becomes NULL. So make q->rear also NULL.
     */
    if(q->front == NULL) {
        q->rear = NULL;
    }
    value = temp->value;
    temp->next = NULL;
    free(temp);
    return value;
}
