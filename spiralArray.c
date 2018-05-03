/* This file contains code to print a 2d
 * array in spiral form.
 */
#include <stdio.h>
#include <stdlib.h>

void printSpiral(int arr[4][4], int row_len, int column_len) {
    if(!arr) {
        return;
    }

    /*
     * We do it similar to rotating a 2d array.
     * We do it layer by layer starting from 0,0 the going to right
     * then going down and then to left and then to up.
     */
    int row_start = 0, row_end = row_len;
    int column_start = 0, column_end = column_len;

    while(row_start < row_end && column_start < column_end) {
        /* First start with row_start and traverse all columns of this
         * row towards right
         */
        for(int i=column_start; i<column_end; i++) {
            printf("%d ", arr[row_start][i]);
        }
        row_start++;

        /* 
         * Now print the last column from top to down.
         */
        for(int i=row_start; i<row_end; i++) {
            printf("%d ", arr[i][column_end-1]);
        }
        column_end--;

        /* Now check if row_start has not reached row_end and then print
         * last row from right to left.
         */
        if(row_start < row_end) {
            for(int i=column_end-1; i>=column_start; i--) {
                printf("%d ", arr[row_end-1][i]);
            }
        }
        row_end--;

        /* Now check if column_start has not reached column_end and then
         * print the first column from bottom to top.
         */
        if(column_start < column_end) {
            for(int i=row_end-1; i>=row_start; i--) {
                printf("%d ", arr[i][column_start]);
            }
        }
        column_start++;
    }
    printf("\n");
}

int main(void) {
    int arr[4][4] = {{1,2,3,4},
                     {5,6,7,8},
                     {9,10,11,12},
                     {13,14,15,16}};
    printf("The given array is :\n");
    for(int i=0; i<4; i++) {
        for(int j=0; j<4; j++) {
            printf("%d ",arr[i][j]);
        }
    }
    printf("\n The array printed in spiral format is:\n");
    printSpiral(arr, 4, 4);
    return 0;
}

