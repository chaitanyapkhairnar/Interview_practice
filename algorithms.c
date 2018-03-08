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
        if(key < array[mid]) {
            return binary_search(arr, first, mid-1, key);
        /* If key belongs to second half check in array from
         * mid+1 to last. */
        } else {
            return binary_search(arr, mid+1, last, key);
        }
    }
    /* End of array and element not found. */
    return -1
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
            for(int j=(i-m); j<i; j++) {
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

