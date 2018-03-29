/*
 * This file implements the function to solve
 * SUDOKU problem given a 2*2 grid which is
 * partially filled.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define N 9    //This is the size of grid

// Function to check if the given number is present in
// the given row.
bool isPresentInRow(int grid[N][N], int row, int number) {
    int column;
    for(column=0; column<N; column++) {
        if(grid[row][column] == number) {
            return true;
        }
    }
    return false;
}

// Function to check if the given number is present in
// the given column.
bool isPresetInColumn(int grid[N][N], int column, int number) {
    int row;
    for(row=0; row<N; row++) {
        if(grid[row][column] == number) {
            return true;
        }
    }
    return false;
}

// Function to check if the given number is present in
// the 3x3 box given the start index of box.
bool isPresentInBox(int grid[N][N], int x, int y, int number) {
    int row, column;
    for(row=x; row<(x+3); row++) {
        for(column=y; column<(y+3); column++) {
            if(grid[row][column] == number) {
                return true;
            }
        }
    }
    return false;
}

// Function to check if it is safe for the given number to
// be put at given location.
bool isSafe(int grid[N][N], int x, int y, int number) {
    if(isPresentInRow(grid, x, number) ||
       isPresetInColumn(grid, y, number) ||
       isPresentInBox(grid, (x-(x%3)), (y-(y%3)), number)) {    // Here x-x%3 will return the start x index
                                                                // of the box x belongs to. Same for y.
        return false;
    } else {
        return true;
    }
}

// Function to find the empty slot in the grid.
bool isEmptySlot(int grid[N][N], int *row, int *column) {
    for(int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            if(grid[i][j] == 0) {
                *row = i;
                *column = j;
                return true;
            }
        }
    }
    return false;
}

// Recursive Function to fill the grid to solve Sudoku.
// We use backtracking algorithm here.
// First we get a empty slot in the grid. Then for each possible
// number from 1 to 9, we check if this particular number is safe
// to be inserted at this particular location by checking if the 
// number is already not present in row, column, or the 3x3 box.
// If it is safe, we insert the number in the grid and recursively
// call the function to solve rest of the grid.
// If in future, there is no solution for this particular number
// insertion at this particular location, the recursive function calls
// will return false and so, we BACKTRACK by putting 0 again at this particular
// location and try with next number.
bool SolveSudoku(int grid[N][N]) {
    int row, column;
    if(isEmptySlot(grid, &row, &column)) {
        for(int number=1; number<=9; number++) {
            if(isSafe(grid, row, column, number)) {
                grid[row][column] = number;
                if(SolveSudoku(grid)) {
                    return true;
                } else {
                    grid[row][column] = 0;
                }
            }
        }
        return false;
    } else {
        return true;
    }
}

// Main driver function to check
int main(void) {
    int grid[N][N] = {{3, 0, 6, 5, 0, 8, 4, 0, 0},
                      {5, 2, 0, 0, 0, 0, 0, 0, 0},
                      {0, 8, 7, 0, 0, 0, 0, 3, 1},
                      {0, 0, 3, 0, 1, 0, 0, 8, 0},
                      {9, 0, 0, 8, 6, 3, 0, 0, 5},
                      {0, 5, 0, 0, 9, 0, 6, 0, 0},
                      {1, 3, 0, 0, 0, 0, 2, 5, 0},
                      {0, 0, 0, 0, 0, 0, 0, 7, 4},
                      {0, 0, 5, 2, 0, 6, 3, 0, 0}};

    printf("Welcome to Sudoku Solver\n");
    printf("The initial partial grid is: \n");
    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            printf("%d  ", grid[i][j]);
        }
        printf("\n");
    }
    if(SolveSudoku(grid)) {
        printf("Solution to above grid is: \n");
        for(int i=0; i<N; i++) {
            for(int j=0; j<N; j++) {
                printf("%d  ", grid[i][j]);
            }
            printf("\n");
        }
    } else {
        printf("There is no solution to the above grid.\n");
    }
    return 0;
}
