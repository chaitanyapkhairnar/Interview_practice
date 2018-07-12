/*
 * This source code implements the queen problem. Given a 8X8 chessboard, we
 * have to place 8 queens on the board such that no queen can invade each other.
 *
 * It also implements knight problem where given a 8X8 chessboard, we have to
 * fill a solution array of 8X8 which has the move number for a knight such
 * that the knight covers the entire board. If its not possible, then return
 * false.
 */
#include <stdio.h>
#include <stdlib.h>

/*
 * We have to return all possible ways to place 8 queens such that no one kills
 * any other. We maintain an array to store the positions of queens placed till
 * now. We will use this to find the position to place new queen such that it
 * is not being killed by any previous queens. We write a recursive function
 * which takes row number as argument and for that row, it traverses all
 * possible columns and tries to place a queen on that column. Base case
 * is if we reach last row, then all queens are placed, so we increment the
 * count.
 */
#define GRID_SIZE 8

void placeQueen(int row, int* prevQueenPos, int *count) {
    // Main function will call this with row=0.
    // prevQueenPos is a array which holds the column number of prev queens
    // at the row index. prevQueenPos[1] = 3 means that the queen is at
    // row 1 and column 3. Count will store the total number of ways.

    if(row == GRID_SIZE) {
        // We can also have an array or arrays which store
        // the actual positions. We can use prevQueenPos to get
        // the position of all the queens and store it in our result
        // 2d array.
        *count++;
        return;
    }

    // Now, we have to place queen in some column in given row. So we traverse
    // all the columns and for each column, we check if we can place our queen
    // there. If yes, we update the prevQueenPos with our queen's position
    // and recursively call the function for next row.
    
    for(int col=0; col<GRID_SIZE; col++) {
        if(isValid(row, col, prevQueenPos)) {
            prevQueenPos[row] = col;
            placeQueen(row+1, prevQueenPos, count);
        }
    }
    return;
}

// Function to check if the row, col position is valid to place the queen.
bool isValid(int row, int col, int *prevQueenPos) {
    // We check for all previous rows for the position of prev queens
    if(row == 0) {
        return true; // As row is 0, this is first queen. So place anywhere.
    }

    int prev_row, prev_col;
    for(prev_row=0; prev_row<row; prev_row++) {
        prev_col = prevQueenPos[prev_row];
        // Now, prev queen is at prev_row,prev_col position. We check if our
        // position row, col lies in same column as prev queen or lies in a
        // diagonal position of prev queen. If yes, return false.
        if(prev_col == col) {
            return false;
        }

        int row_dist = abs(row-prev_row);
        int col_dist = abs(col-prev_col);

        // If the above distances are equal, then it means they are on same
        // diagonal.
        if(row_dist == col_dist) {
            return false;
        }
    }
    return true;
}

/*
 * Knight Problem: We have to move knight such that it covers all the cells on
 * the chess board. If it is possible, we return the solution matrix which
 * contains the move number for each cell.
 *
 * We use backtracking here. We start with 0,0. We initialize our solution matrix
 * of size 8X8 to all -1s. We mark solution[0][0] = 0 as this is our start point.
 * Now, we traverse for all the 8 possible moves of knight and for each, we check
 * if it is a valid move. If yes, we recursively call the function with this new
 * position. If it returns false, we call the function for next possible move and
 * so on. If all return false, then we backtrack by resetting the value in
 * solution matrix and return false. If any of these returned true, we break the
 * for loop and return true.
 */

// For valid moves of knight
int xMove[8] = {  2, 1, -1, -2, -2, -1,  1,  2 };
int yMove[8] = {  1, 2,  2,  1, -1, -2, -2, -1 };

bool knightProblem(int x, int y, int **solution, int count) {
    // Main function will call this function with x=0, y=0, count=1 and
    // solution array all initialized to -1. We check the count and if it
    // is 64 (8*8), we have visited all the cells, so we return true. Its
    // our base case.
    if(count == 64) {
        return true;
    }

    // Traverse for all possible moves and check if it is valid and then
    // recursively call
    for(int i=0; i<8; i++) {
        int new_x = x + xMove[i];
        int new_y = y + yMove[i];

        if(isValidMove(new_x, new_y, solution)) {
            solution[new_x][new_y] = count;
            if(knightProblem(new_x, new_y, solution, count+1)) {
                return true;
            } else {
                // If we reach here, then there is no possible move
                // from new_x, new_y position, so backtrack.
                solution[new_x][new_y] = -1;
            }
        }
    }
    return false;
}

bool isValidMove(int x, int y, int **sol) {
    if(x>=0 && y>=0 && x<8 && y<8 && sol[x][y] == -1) {
        return true;
    } else {
        return false;
    }
}
