/*
 *
 * Author: Chaitanya
 *
 * File: algorithms.c
 *
 * Info: This file contains different algorithms
 *       for searching, sorting, greedy algorithms,
 *       dynamic programming, etc.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

/***********************************************/

/*
 * Searching Algorithms
 */

/***********************************************/

/*
 * 1. Linear Search
 *    This algorithm searches an array element by element
 *    Complexity: O(n)
 */
int linear_search(int *arr, int len, int key) {
    /* Traverse the entire length of array */
    for(int i=0; i<len; i++) {
        /* If element found, return the index of array */
        if(arr[i] == key) {
            return i;
        }
    }
    /* If element not found in the array, return -1 */
    return -1;
}

/*
 * 2. Binary Search
 *    This algorithm takes sorted array as input
 *    and searches for the element by dividing
 *    the array into halves. If element is in
 *    the range of first half, recursively search in
 *    first half or array or else do it for second half.
 *    Complexity: O(Log(n)). Here Log to base 2
 */
int binary_search(int *arr, int first, int last, int key) {
    /* This is recursive function. For the first call, 
     * first is 0 and last is length of array-1.
     */
    if(first <= last) {
        int mid = (first + last)/2;
        /* If key found, return index */
        if(key == arr[mid]) {
            return mid;
        }
        /* If key belongs to first half check in array from
         * first to mid-1 as we already checked mid. */
        if(key < arr[mid]) {
            return binary_search(arr, first, mid-1, key);
        /* If key belongs to second half check in array from
         * mid+1 to last. */
        } else {
            return binary_search(arr, mid+1, last, key);
        }
    }
    /* End of array and element not found. */
    return -1;
}

/*
 * Binary search iterative function to avoid O(Log(n)) extra space
 * we used in recursive approach.
 */
int binary_search_iterative(int *arr, int first, int last, int key) {
    while(first <= last) {
        int mid = (first+last)/2;
        if(key == arr[mid]) {
            return mid;
        }
        if(key < arr[mid]) {
            last = mid-1;
        } else {
            first = mid+1;
        }
    }
    return -1;
}

/*
 * 3. Jump Search
 *    The idea is to get a block size 'm' in argument and
 *    first search only o, m, 2m, 3m, ... elements of array
 *    and when we get the range arr[km] < key < arr[(k+1)m]
 *    then do linear search for key in this range.
 *    Complexity: O(sqrroot(n)) where n is length of array.
 *    In worst case we do n/m operations to get the range
 *    and then m-1 linear searches. So its (n/m)+(m-1).
 *    To have this value at minimum, m should be sqrroot(n).
 */
int jump_search(int *arr, int block, int len, int key) {
    for(int i=0; i<len; i++) {
        if(key == arr[i]) {
            return i;
        }
        if(key < arr[i]) {
            for(int j=(i-block); j<i; j++) {
                if(key == arr[j]) {
                    return j;
                }
            }
            return -1;
        }
        i = i + block;
    }
    return -1;
}


/***********************************************/

/*
 * Sorting Algorithms
 */

/***********************************************/

/*
 * 1. Bubble Sort
 *    Repeatedly swap adjascent elements if they are in
 *    wrong order.
 *    Complexity: O(n^2)
 *    Best case complexity: O(n) when array is already sorted.
 */
int* bubble_sort(int *arr, int len) {
    /* Number of passes */
    for(int i=0;i<len-1;i++) {
        /* For each pass, compare adjascent elements
         * traversing entire array. For each pass, j
         * goes from 0 to len-i because after 1st pass,
         * largest element will be in the last position,
         * after 2nd pass, 2nd largest element will be
         * in 2nd last position and so on. So we need
         * not to compare again with these last elements.
         */
        for(int j=0;j<len-1-i;j++) {
            if(arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
    return arr;
}

/*
 * 2. Selection Sort
 *    Divide the array into 2 subarrays sorted and unsorted.
 *    For each pass, get the minimum element from unsorted
 *    subarray and put it in sorted subarray.
 *    In short, for each pass, we put minimum element in first
 *    position. In bubble sort, we were putting max element in
 *    last position.
 *    Complexity: O(n^2)
 *    Pro: In any case, it does not make more than O(n) swaps.
 */
int* selection_sort(int *arr, int len) {
    int min_index;
    /* Move the boundry of unsorted array one by one.
     * For 1st pass, it is 0 to len-1, for 2nd pass,
     * it is from 1 to len-1 and so on.
     */
    for(int i=0;i<len-1;i++) {
        /* For each unsorted subarray, find the min element
         * by parsing through the entire length of subarray
         * and then swap ith element with this min element.
         */
        for(int j=i+1;j<len;j++) {
            min_index = i;
            if(arr[min_index]>arr[j]) {
                min_index = j;
            }
        }
        /* Swap the ith element with min_index element */
        int temp = arr[i];
        arr[i] = arr[min_index];
        arr[min_index] = temp;
    }
    return arr;
}

/*
 * 3. Insertion Sort
 *    Start from the second element and for each pass, check
 *    if it is less than the subarray to its left. If yes,
 *    insert it in appropriate position by moving the elements
 *    in the left subarray to right and make place for this
 *    insertion.
 *    Complexity: O(n^2)
 *    Pro: Used in cases where there is large array and most of
 *    the elements are sorted but only few needs to be sorted.
 */
int* insertion_sort(int *arr, int len) {
    for(int i=1;i<len;i++) {
        int key=arr[i];
        int j=i-1;
        while(j>=0 && arr[j]>key) {
            /*If arr[j] is greater than key, shift it to right.
             * We already have the value of arr[j+1] in key
             * so dont worry about overwriting j+1 element.
             */
            arr[j+1] = arr[j];
            j--;
        }
        /* Inser key once we shifted all the elements which
         * were greater than key to right.
         */
        arr[j+1] = key;
    }
    return arr;
}

/*
 * 4. Merge Sort
 *    Divide the array into 2 subarrays recursively until
 *    we have single elements in both subarrays. Then merge
 *    the 2 subarrays in sorted order. The assumption of merge
 *    is the 2 subarrays it gets in argument are already sorted
 *    and it merges these sorted subarrays together so new array
 *    is also sorted.
 *    Complexity: O(nLog(n)) as it divides the array into halves
 *                (O(Log(n))) and then for each of these iterations,
 *                it takes linear time to merge the subarrays (O(n)).
 *    Extra Space: O(n)
 */
void merge(int *arr, int left, int mid, int right) {
    /* we got 2 subarrays in argument. arr[left, mid]
     * and arr[mid+1, right]. And these are already sorted.
     * We need to merge these two so that the array[left, right]
     * is also sorted.
     */
    int left_len, right_len, i, j, k;
    /* Calculate the lengths for left and right subarrays */
    left_len = (mid-left)+1;
    right_len = (right-mid); /* right subarray is from mid+1 to right */

    /* Create two temp arrays to hold the data from arr */
    int left_arr[left_len], right_arr[right_len];

    /* Flood the left subarray */
    k=left;
    for(i=0;i<left_len;i++) {
        left_arr[i] = arr[k];
        k++;
    }
    /* Flood the right subarray */
    for(j=0;j<right_len;j++) {
        right_arr[j] = arr[k];
        k++;
    }

    /* Now that we have arr split into left and right
     * subarrays, we start the merge process.
     */
    k=left;
    i=0;
    j=0;

    while(i<left_len && j<right_len) {
        if(left_arr[i] <= right_arr[j]) {
            arr[k] = left_arr[i];
            i++;
        } else {
            arr[k] = right_arr[j];
            j++;
        }
        k++;
    }

    /* It may be the case when left array is exhausted
     * and we till have elements in right array and vice versa.
     * So add the remaining elements in arr
     */
    while(i<left_len) {
        arr[k] = left_arr[i];
        i++;
        k++;
    }

    while(j<right_len) {
        arr[k] = right_arr[j];
        j++;
        k++;
    }

    /* Now we have arr sorted from left to right index. 
     * So return.*/
}

void merge_sort(int *arr, int left, int right) {
    if(left < right) {
        int mid = (left + right)/2;
        /* We should have done mid = (left + (right-left)/2)
         * to avoid overflow when left and right are large enough
         * so that left+right goes beyond the range of int.
         * If this overflow happens, calculated mid value is
         * incorrect.
         */
        merge_sort(arr, left, mid);
        merge_sort(arr, mid+1, right);
        merge(arr, left, mid, right);
    }
}

/*
 * Iterative Merge Sort.
 *
 * The idea is to update the merge_sort function above to make
 * it iterative. We first divide the array into subarrays of size
 * 1 each and use the same merge function to merge them. We do this
 * for entire length of given array. Then we divide this update array
 * into subarrays of size 2 and merge them. The we continue the process
 * for subarray of size 4, 8 ...
 */

void merge_sort_iterative(int *arr, int len) {
    int current_size, left;

    for(current_size=1; current_size<len; current_size=2*current_size) {
        /* Now we pick the left starting point for each subarray of
         * current_size. Then we calculate the mid and right_end for
         * subarrays from current_size variable.
         */
        for(left=0;left<len-1;left=left + 2*current_size) {
            int mid = left+current_size-1;
            int right = min(left+2*current_size-1, len-1);

            /* Merge these subarrays */
            merge(arr, left, mid, right);
        }
    }
}

/*
 * 5. Quick Sort
 *    We first select a pivot element in the given array.
 *    In this implementation, we are selecting the last
 *    element as pivot element.
 *    Now we partition the array into 2 subarrays such that
 *    the selected pivot element is in the correct position
 *    in the array as it would in the sorted array and all
 *    the elements smaller than pivot element are to its left
 *    and larger elements to its right.
 *    Now we recursively call the quick_sort function for these
 *    two partitioned subarrays, low to pivot-1 and pivot+1 to high.
 *    We dont take pivot element as it is already in its correct
 *    position.
 *
 *    Complexity: O(nLog(n)) for average case. O(n^2) for worst case
 *                worst case is when pivot element selected is always
 *                largest or smallest element.
 *
 */

int partition(int *arr, int low, int high) {
    /* Get last index element as pivot element. */
    int pivot = arr[high];

    /* Traverse the entire array and maintain a min_element
     * index.
     * Compare each element with the pivot element.
     * If it is  than the pivot element, place it
     * at the position next to min_element and continue.
     * In the end, put the pivot element next to the min_element
     * index. This is the correct position of pivot element and
     * this way, all elements smaller that pivot element are to
     * its left and higher to its right.
     */
    
    /* initialize min_index */
    int min_index = low-1;
    for(int j=low; j<high-1; j++) {
        /* If the current element is < pivot,
         * swap it with the element next to min_index.
         */
        if(arr[j] <= pivot) {
            min_index++;
            int temp = arr[min_index];
            arr[min_index] = arr[j];
            arr[j] = temp;
        }
    }

    /* put the pivot element to its correct place */
    min_index++;
    int temp = arr[min_index];
    arr[min_index] = arr[high];
    arr[high] = temp;

    /* Return the index of pivot element. */
    return min_index;
}

void quick_sort(int *arr, int low, int high) {
    if(low < high) {
        /* First partition the array so that we have
         * two subarrays. Left subarray will have all elements
         * smaller than pivot element and Right subarray will
         * have all elements greater than Pivot element.
         */
        int pivot_index = partition(arr, low, high);

        /* Now recursively call quick_sort for the 2 subarrays. */
        quick_sort(arr, low, pivot_index-1);
        quick_sort(arr, pivot_index+1, high);
    }
}



int main(void) {
    int *arr = (int *)malloc(sizeof(int)*100);
    printf("The given array is: \n");
    for(int i=0;i<100;i++) {
        /* generate a random number in range 0 to 200 */
        arr[i] = (rand())%200;
        printf("%d ", arr[i]);
    }
    printf("\n");

    /* Sort the array with different algorithms. */




    return 0;
}
