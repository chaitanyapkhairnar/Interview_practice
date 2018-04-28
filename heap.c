/*
 * This source file contains all the operations relevant to Heap data structure.
 * A Binary Heap is a Binary tree with following properties:
 * 1. It is a complete tree. (All the levels of nodes are completely filled. Only last level
 * can be partially filled and there too, the nodes are as left as possible).
 * 2. The root of tree should have minimum value and recursively, root of each subtree should
 * follow this property. (This is called Min Heap. If root has max value, its called Max Heap)
 * Due to these properties, Heap can be easily represented by an Array by following below
 * A. The root of Heap is at 0th index.
 * B. For node at ith index, Its left child should be present at 2*i+1 and right child at 2*i+2
 * By following the above, The index of Parent of node at ith index is at (i-1)/2
 * Time complexity is O(log(n)) for insert, delete, decreasekey operations. O(1) to get min.
 */

#include <stdio.h>
#include <stdlib.h>

int *heap;      /* Array which stores the heap datastructure */
int capacity;   /* Max capacity of heap */
int heap_size;  /* Current size of heap */

void heapify(int);  /* Function to heapify the subtree with the given index of root */
int parent(int);    /* Function to return the index of parent of the given node index */
int right(int);     /* Function to return the index of the right child of given node index */
int left(int);      /* Function to return the index of the left child of given node index */
int getMin();       /* Function to get the minimum value present in the heap */
int extractMin();   /* Function to extract the root while maintaining the heap property */
void decreaseKey(int , int); /* Function to decrease the key value at index i to new_val */
void deleteKey(int);         /* Function to delete the key at given index */
void insertKey(int);         /* Insert a new key of given value at appropriate place */


/*
 * Initialize the heap by allocating memory to it
 */
void initialize_heap(void) {
    heap_size = 0;
    heap = (int*)malloc(sizeof(int)*capacity);
}

int parent(int index) {
    return (index-1)/2;
}

int left(int index) {
    return ((2*index)+1);
}

int right(int index) {
    return ((2*index)+2);
}

int getMin(void) {
    return heap[0];
}

void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

void insertKey(int val) {
    /* Check if we have remaining capacity */
    if(heap_size == capacity) {
        printf("No more capacity in Heap. Cannot insert.\n");
        return;
    }
    /* First insert the new element in the last index.
     * Then we will check if heap property is violated.
     * If yes, we will heapify the subtree by swapping
     * the new node with its parent node.
     */
    heap[heap_size] = val;
    int i = heap_size;
    int j = parent(i);
    heap_size++;

    /* If the new node is smaller than the parent, heap
     * property is violated. So swap the new node with
     * its parent and continue doing it recursively.
     */
    while(heap[i] < heap[j]) {
        if(i == 0) {
            break;
        }
        swap(&heap[i], &heap[j]);
        i=j;
        j=parent(i);
    }
}

void decreaseKey(int index, int val) {
    /* Modify the value at given index */
    heap[index] = val;

    /* Check if the heap property is violated.
     * If yes, restore it by swapping.
     */
    while(heap[index] < heap[parent(index)]) {
        if(index == 0) {
            break;
        }
        swap(&heap[index], &heap[parent(index)]);
        index = parent(index);
    }
}

int extractMin(void) {
    if(heap_size <= 0) {
        printf("Heap is empty\n");
        return -1;
    } else if (heap_size == 1) {
        heap_size--;
        return heap[0];
    }
    int val = heap[0];
    /* Put the last element in heap at 0th
     * index and reduce the heap size
     */
    heap[0] = heap[heap_size-1];
    heap_size--;

    /* Now call the heapify with root index 0
     * to heapify this entire heap.
     */
    heapify(0);

    return val;
}

void heapify(int index) {
    int l = left(index);
    int r = right(index);
    int min = index;

    /* Check if left or right child is less than
     * the node at index. If yes, then heap property
     * is violated. So we need to swap.
     */
    if((l < heap_size) && (heap[l] < heap[index])) {
        min = l;
    }
    if((r < heap_size) && (heap[r] < heap[index])) {
        min = r;
    }
    if(min != index) {
        swap(&heap[min], &heap[index]);
        heapify(min);
    }
}

void deleteKey(int index) {
    /* First decrease the value at this
     * index to -ve so that it becomes the root
     * of heap and goes to index 0
     */
    decreaseKey(index, -1);

    /* Now call extractMin to extract this min
     * value node out
     */
    extractMin();
}

int main(void) {
    printf("Enter the max capacity for Heap\n");
    scanf("%d", &capacity);
    initialize_heap();
    insertKey(3);
    insertKey(2);
    deleteKey(1);
    insertKey(15);
    insertKey(5);
    insertKey(4);
    insertKey(45);

    printf("The min value in heap is %d\n", extractMin());
    printf("The min value in heap is %d\n", getMin());

    return 0;
}
