#include <stdio.h>
#include <stdlib.h>

/*
 * This is O(Log(n)) approach to find out missing element in the given sorted
 * array which has elements from range 1 to n. The size of array is n-1.
 *
 * We use binary search approach here. First we check if the missing element is in
 * the mid element by checking prev and next elements of mid. If yes, return. Then
 * we check if start = end-1. This is the last window to be checked for missing
 * element. Here, we check if end == size. This case will occur for non missing element
 * because for non missing element, we keep going right. Once these base cases are done,
 * we go to left subarray recursively if arr[mid] != mid+1 which means that an element
 * is already missing when we check mid element so it must be in left subarray. If not
 * then we check the right subarray.
 */
int missing_number(int *arr, int start, int end, int size) {
    if(start > end) {
        return -1;
    }

    if(start == (end - 1)) {
        if(arr[start] != start+1) {
            return (start+1);
        } else {
            if(end==size) {
                // No missing element
                return -2;
            }
            return (start+2);
        }
    }

    int mid = (start + end)/2;
    if(arr[mid] == mid+1) {
        // Check in right subarray
        return missing_number(arr, mid+1, end, size);
    } else {
        // Check if mid element is itself missing
        int prev = mid-1;
        int next = mid+1;
        if((arr[prev] == prev + 1) && (arr[next] != next+1)) {
            return (mid+1);
        }
        // Check in left subarray
        return missing_number(arr, start, mid-1, size);
    }
    // We will never reach here
    return -1;
}

int main(void) {
    int arr[10] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    int missing = missing_number(arr, 0, 10, 10);

    if(missing == -1) {
        printf("Invalid given array.\n");
    } else if(missing == -2) {
        printf("No missing element in the given array.\n");
    } else {
        printf("The missing element in the given array is %d\n", missing);
    }

    return 0;
}
