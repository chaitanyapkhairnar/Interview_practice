/*
 * This file contains the problems which use heap for their solutions.
 */

/*
 * We will use below functions related to heap
 *
 * heap_add() - To add element to heap and heapify it
 * heap_get_min() - To get the min element from heap
 * heap_extract_min() - To extract the min element from heap and heapify it
 */

/*
 * 1. Merge K sorted arrays: We are given K sorted arrays of length N each.
 *    We have to merge these into a single array of size KN which is also sorted.
 *
 *    We use min heap of size K here. We first store the first element of all the
 *    K given arrays into heap. We initialize a result array of size KN. Then until
 *    this result array is filled, we extract min element from the heap and put it
 *    in result array. And we replace this element from the next element in that
 *    array in the heap. If that array is out of elements, we replace it with
 *    some max value. This is O(KN*log(K)) approach as for each insertion to heap
 *    we take log(K) time and there are total KN elements.
 */
#define INF INT_MAX

typedef struct heap_node {
    int value;        /* Value of element to be added to heap */
    int array_id;     /* ID of array to which this element belongs to */
    int element_id;   /* Index in that array at which next element is present */
}heap_node;

void mergeKsorted(int **arr, int K, int N, int *result) {

    /* Our heap will be an array of above structure of size K */
    heap_node heap[K];

    result = malloc(sizeof(int)*N*K);

    /* We initially fill 1st element of all the K arrays in heap */
    for(int i=0; i<K; i++) {
        /* heap_add adds node element in heap array at index 0 and calls
         * heapify
         */
        heap_node node;
        node.value = arr[i][0];
        node.array_id = i;
        node.element_id = 1;
        heap_add(&heap, node);
    }

    /* Now we start filling the result array */
    for(int count=0; count<K*N; count++) {
        heap_node temp = heap_extract_min(&heap);
        result[count] = temp.value;

        if(temp.element_id < N) {
            temp.value = arr[array_id][element_id];
            temp.element_id++;
        } else {
            temp.value = INF;
        }
        heap_add(&heap, temp);
    }
    return;
}

/*
 * 2. Get Median from the running stream of integers:
 *    We have a running stram of integers and for each new integer
 *    we encounter, we have to return the median uptil now.
 */

/* We use 2 heaps here. 1 is minHeap and 1 is maxHeap. We use maxHeap for left
 * half of numbers and minHeap for right half. At all times, we maintain a
 * restriction that these heaps can differ in size atmost by 1. So when we have
 * a new element to add, we check the sizes of heap and add element to the
 * heap accordingly. This is O(Nlog(N)) approach.
 */

void printMedians(void) {
    int a[12] = {5, 15, 1, 3, 2, 8, 7, 9, 10, 6, 11, 4};
    int median = 0;  /* Effective median initialized to 0 */

    int *minHeap, *maxHeap;

    createHeap(minHeap, 12);
    createHeap(maxHeap, 12);

    for(int i=0; i<12; i++) {
        getMedian(a[i], minHeap, maxHeap, &median);
        printf("Median uptill %d is %d\n", i, median);
    }
}

void getMedian(int num, int *minHeap, int *maxHeap, int *median) {
    int lSize = getSize(maxHeap);
    int rSize = getSize(minHeap);

    /* If both heaps are of same size */
    if(lSize == rSize) {
        /* If this num belongs to left heap */
        if(num < *median) {
            maxHeapAdd(maxHeap, num);
            *median = maxHeapGetTop(maxHeap);
        } else {
            minHeapAdd(minHeap, num);
            *median = minHeapGetTop(minHeap);
        }
    } else if(lSize > rSize) {
        /* If this num belongs to left heap */
        if(num < *median) {
            /* We first extract top element from left heap and put it in
             * right heap so that the size difference is not violated */
            minHeapAdd(maxHeapExtractTop(maxHeap));

            /* Now add the num to left heap */
            maxHeapAdd(maxHeap, num);
        } else {
            minHeapAdd(minHeap, num);
        }

        /* Now the size of both heaps are same. So this is case of even
         * number of elements. So, we get average of middle two elements
         * to get the median. In our case, the middle two elements are the
         * top elements in both the heaps.
         */
        int num1 = maxHeapGetTop(maxHeap);
        int num2 = minHeapGetTop(minHeap);
        *median = (num1+num2)/2;
    } else {    /* Right heap is larger in size */
        /* If this num belongs to left heap */
        if(num < *median) {
            maxHeapAdd(maxHeap, num);
        } else {
            maxHeapAdd(minHeapExtractTop(minHeap));
            minHeapAdd(minHeap, num);
        }
        int num1 = maxHeapGetTop(maxHeap);
        int num2 = minHeapGetTop(minHeap);
        *median = (num1+num2)/2;
    }
    return;
}
