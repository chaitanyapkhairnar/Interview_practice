/*
 * This file contains functions to rotate a 2d matrix.
 */
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define SIZE 5

void print_matrix(int matrix[SIZE][SIZE]) {
    for(int i=0; i<SIZE; i++) {
        for(int j=0; j<SIZE; j++) {
            if(matrix[i][j]/10 == 0) {
                printf("%d  ", matrix[i][j]);
            } else {
                printf("%d ", matrix[i][j]);
            }
        }
        printf("\n");
    }
}

void rotate_matrix(int matrix[SIZE][SIZE], int size) {
    /*
     * The idea here is to rotate the matrix clockwise by 1 element in place.
     * We do it layer by layer starting from outermost layer and going inward.
     * For each layer, we move elements first from top row, then last column,
     * then last row, then first column.
     *
     * For this, we use 2 variables for row namely row_start and row_end and same
     * for column. Initially start variables are at 0 and end are at size which is
     * 4 in this case. For each iteration, we move our iterator from start to end
     * and then either increment start or decrement end. We should also check that
     * while doing this, if at any time out start becomes > end.
     */
    int row_start = 0;
    int row_end = size;
    int column_start = 0;
    int column_end = size;
    int prev, curr;

    while((row_start < row_end) && (column_start < column_end)) {
        if((row_start+1 == row_end) || (column_start+1 == column_end)) {
            break;
        }
        
        /* First we move the top row which is represented by row_start */
        // Store the first element of next row as it will move to first element
        // of current row.
        prev = matrix[row_start+1][column_start];
        for(int i=column_start; i<column_end; i++) {
            curr = matrix[row_start][i];
            matrix[row_start][i] = prev;
            prev = curr;
        }
        row_start++;

        /* Now we have last column of row_start in prev. Now we move the last column
         * of matrix which is represented by column_end.
         */
        for(int i=row_start; i<row_end; i++) {
            curr = matrix[i][column_end-1];
            matrix[i][column_end-1] = prev;
            prev = curr;
        }
        column_end--;

        /* Now we do the same operations for last row which is represented by
         * row_end.
         */
        if(row_start < row_end) {
            for(int i=column_end-1; i>=column_start; i--) {
                curr = matrix[row_end-1][i];
                matrix[row_end-1][i] = prev;
                prev = curr;
            }
        }
        row_end--;

        /* Last we move elements of leftmost column which is represented by
         * column_start.
         */
        if(column_start < column_end) {
            for(int i=row_end-1; i>=row_start; i--) {
                curr = matrix[i][column_start];
                matrix[i][column_start] = prev;
                prev = curr;
            }
        }
        column_start++;
    }

    /* Now we print the result rotated array. */
    printf("The clockwise rotated array is:\n");
    print_matrix(matrix);
}

/*
 * TODO: Not working.
 * This function rotates the matrix by 90 degrees clockwise
 */
void rotate_matrix_ninety(int matrix[SIZE][SIZE], int size) {
    /* Now as we need to rotate the matrix by 90 degrees, we know that in
     * outermost layer, all the corner elements will change their positions
     * such that element from corner 0,0 will move to corner 0,3 and so on.
     * Similarly elements next to corner will move and so on. This happens
     * for each layer. In a 2d matrix of size MXM, number of layers is always
     * floor(M/2). So we iterate for each layer and then for each layer we
     * move all the elements in that layer to their correct position using
     * another for loop and a temp variable to store an element.
     */
    int layer = size/2;

    // For each layer in array
    for(int x=0; x<layer; x++) {
        // For each element within array
        for(int y=x; y<size-x-1; y++) {
            // Store the current element in temp
            int temp = matrix[x][y];

            // Move the value from bottom corner to current
            matrix[x][y] = matrix[size-1-x][y];

            // Move the value from bottom right to bottom left
            matrix[size-1-x][y] = matrix[size-y-1][size-1-x];

            // Move the value from left top to left bottom
            matrix[size-y-1][size-1-x] = matrix[x][size-y-1];

            // Finally move temp to top left
            matrix[x][size-y-1] = temp;
        }
    }

    /* Now we print the result rotated array. */
    printf("The 90 degree rotated array is:\n");
    print_matrix(matrix);
}

/*
 * This function rotates the matrix by 90 degrees inplace
 * without using any extra space. It is another option to the above algorithm.
 *
 * Here we first take the transpose of the given matrix and then reverse each
 * column of this transpose matrix.
 */

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to get the transpose of given matrix.
void transpose(int matrix[SIZE][SIZE]) {
    for(int i=0; i<SIZE; i++) {
        for(int j=i; j<SIZE; j++) {
            swap(&matrix[i][j], &matrix[j][i]);
        }
    }
}

// Function to reverse all the columns of the given matrix
// This is used to rotate matrix in anticlockwise direction
void reverseColumns(int matrix[SIZE][SIZE]) {
    int row_end = SIZE;
    for(int row=0; row<SIZE; row++) {
        if(row == row_end) {
            break;
        }
        for(int column=0; column<SIZE; column++) {
            swap(&matrix[row][column], &matrix[row_end-1][column]);
        }
        row_end--;
    }
}

// Function to reverse all the rows of the given matrix.
// This is used to rotate matrix in clockwise direction.
void reverseRows(int matrix[SIZE][SIZE]) {
    for(int row=0; row<SIZE; row++) {
        int column=0;
        int column_end = SIZE;
        while(column<column_end) {
            swap(&matrix[row][column], &matrix[row][column_end-1]);
            column_end--;
            column++;
        }
    }
}

// Function to reverse the matrix anticlockwise using transpose algo
void reverseMatrixAnticlock(int matrix[SIZE][SIZE]) {
    transpose(matrix);
    reverseColumns(matrix);
    printf("The rotated matrix in anticlockwise direction by 90 degrees is:\n");
    print_matrix(matrix);
}

// Function to reverse the matrix clockwise using transpose algo
void reverseMatrixClock(int matrix[SIZE][SIZE]) {
    transpose(matrix);
    reverseRows(matrix);
    printf("The rotated matrix in clockwise direction by 90 degrees is:\n");
    print_matrix(matrix);
}

int main(void) {
    int matrix[SIZE][SIZE] = {{1,2,3,4,5},
                              {6,7,8,9,10},
                              {11,12,13,14,15},
                              {16,17,18,19,20},
                              {21,22,23,24,25}};

    printf("The given matrix is: \n");
    print_matrix(matrix);

    rotate_matrix(matrix, SIZE);

//    reverseMatrixAnticlock(matrix);

//    reverseMatrixClock(matrix);
    
//    rotate_matrix_ninety(matrix, SIZE);

    return 0;
}
