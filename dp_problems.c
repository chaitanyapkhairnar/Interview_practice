/*
 * This file contains top dp problems frequently asked
 * in an interview.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/********************* Utility functions ans structures *********************/
typedef struct Stack {
    int row;
    int column;
    struct Stack *next;
}Stack;

void stackPush(int i, int j, Stack **top) {
    Stack *new_node = (Stack*)malloc(sizeof(Stack));
    new_node->row = i;
    new_node->column = j;
    if(!*top) {
        new_node->next = NULL;
        *top = new_node;
        return;
    }
    new_node->next = *top;
    *top = new_node;
    return;
}

bool stackPop(Stack **top) {
    if(!*top) {
        return false;
    }
    Stack *temp = *top;
    *top = (*top)->next;
    temp->next = NULL;
    free(temp);
    temp = NULL;
    return true;
}

/*
 * Triple Step: A child runs up a staircase where he can take 1, 2 or 3 steps
 * at a time. Find total number of ways he can reach top on the staircase
 * containing n steps.
 *
 * We use tabular approach here. The idea is to start filling the array of
 * length n+1 start from index 1. Here each index means the step number and
 * the value at that index means the total number of ways a child can reach
 * that step. Note that we use array of size n+1 and not n because we start
 * with index 1 and not 0. We initialize this array for steps 1, 2 and 3 such
 * that arr[1]=1 as to go to step 1 there is only 1 way, jump 1 step, arr[2]=2
 * as to go to step 2, there are 2 ways, jump 1, 1 or jump 2. Similarly
 * arr[3]=4, jump 1,1,1; jump 1,2; jump 2,1; jump 3.
 * Once initialized, we start filling indices 4 and above using below formula
 * arr[n] = arr[n-1] + arr[n-2] + arr[n-3]
 * To reach current step, we have all possibilities to reach prev step + 1 jump
 * of 1 step and all possibilities to reach 2 steps prev + 1 jump of 2 steps
 * and all possibilities to reach 3 steps prev + 1 jump of 3 steps. So once we
 * have reached n-1, n-2 or n-3rd step, we can reach present step. So we add
 * all these ways.
 * And finally, we return the value at arr[n].
 *
 * Also note that for some value of n not that large, there is possibility
 * of integer overflow. Good to think it this way and keep this thing in mind too.
 *
 * Time Complexity is O(n) and Extra space is O(n).
 */
int tripleStep(int n) {
    if(n<=0) {
        return -1;
    }
    // Initialize result array
    int arr[n+1];
    memset(arr, 0, n+1);
    arr[1] = 1;
    arr[2] = 2;
    arr[3] = 4;

    if(n<=3) {
        return arr[n];
    }

    // Fill rest of the array
    for(int i=4; i<n+1; i++) {
        arr[i] = arr[i-1] + arr[i-2] + arr[i-3];
    }
    return arr[n];
}

/*
 * Robot in a Grid: A 2d array of r rows and c columns is given and robot is sitting
 * in the top left corner. Robot can move only in forward and downward direction. If
 * the cell in 2d array has value 0, robot cannot move there. Find the path of robot
 * to reach the bottom right corner.
 *
 * There are atleast 2 ways to solve this problem. One is by using backtracking.
 * In this approach, we define a helper function isValidMove() which checks if the
 * cell is non zero and i and j are not going out of bounds. We define a recursive
 * function getPath() which takes the 2d grid, current position indices i and j
 * and solution stack as arguments. It returns bool. Base case is to check if current
 * position indices i==r and j==c. If yes, we have reached the destination. So push
 * these current indices into stack and return true.
 * We start with 0,0 index push this current positon indices into stack.
 * (Our stack structure will contain i and j as members. We use stack to record the 
 * path and then print the path in the end.). Then we first check if forward move 
 * is valid. i.e. (i, j+1). This is valid if i<r, j<c and grid[i][j] != 0.
 * If this is valid, then we recursively call the function for (i, j+1) as current
 * position. If this recursive call returns false, then we try with downward move.
 * We check if (i+1, j) is valid and then recursively call with this position as
 * current position. If this also returns false then it means that from our current
 * position, there is no path to destination. So pop the current position from stack
 * for backtracking and then return false. Else, if any of above two calls returned true,
 * we do not pop the element and return true. Finally we print the stack for path.
 *
 * Time complexity of this is O(2^(rc)). As for each element in the 2d array, we have 2
 * options. We also need extra space for stack. this is O(r+c) as this can be the
 * longest path from origin to destination.
 *
 * We can use dynamic programming to improve the time complexity. The idea is to have a
 * 2d boolean array of same size as grid (rXc). We mark a cell in this sol_arr as true
 * if we can reach here from the origin, else we mark it false. We initialize this sol_arr
 * such that 0,0 is true as this is our starting point. Then we first fill first row and
 * first column. For first row, sol_arr[0][j+1] = sol_arr[0][j] if grid[0][j+1] is non zero.
 * Else sol_arr[0][j+1] = false. false because this is not a valid move.
 * This represents forward move from i,j to i,j+1. Similarly for first columns, it is
 * sol_arr[i+1][0] = sol_arr[i][0] if grid[i+1][0] is nonzero. Else, sol_arr[i+1][0] = false
 * This represents downward move. Once first row and column are filled, we fill rest of the cells
 * by iterating for i=1 to r and j=1 to c. For all these cells, we use below formula
 * sol_arr[i][j] = sol_arr[i][j-1] | sol_arr[i-1][j] if grid[][] is non-zero.
 * Else, sol_arr[i][j] = false. Then we check aol_arr[r][c]. If it is true then we have a path
 * from 0,0 to r,c. Else, we do not have a path. Now to print the path, we start with r,c cell
 * and print these indices first. Then we check if i, j-1 cell is true. If yes, we print this
 * and update our i and j to now point to i, j-1. Else we do this for i-1, j cell. We keep
 * doing this until i and j become zero. This is the path.
 *
 * Time complexity of this is O(rc) and extra space required is O(rc) for sol_arr. If we use
 * stack to print the route, then we need more space of (r+c).
 *
 * If we were asked to get the count of all possible ways from origin to destination, then we
 * use same approach. Only changes we do is to use a int sol_arr instead and instead of updating
 * true, we update as sol_arr[i][j] = sol_arr[i][j-1] + sol_arr[i-1][j]. And instead of updating
 * as false, we update it as some error value. say -1. Finally value at sol_arr[r][c] will have
 * the total number of possible routes.
 */
bool isValid(int **grid, int r, int c, int x, int y) {
    if(x<r && y<c && grid[x][y] != 0) {
        return true;
    } else {
        return false;
    }
}

bool robotInGridBacktrack(int **grid, int r, int c, int curr_i, int curr_j, Stack **sol) {
    // Base case
    if(curr_i == r && curr_j == c) {
        stackPush(curr_i, curr_j, sol);
        return true;
    }

    // Push current cell in stack
    stackPush(curr_i, curr_j, sol);

    // Check for forward and downward move possibilities
    bool forward=false, downward=false;

    if(isValid(grid, r, c, curr_i, curr_j+1)) {
        forward = robotInGridBacktrack(grid, r, c, curr_i, curr_j+1, sol);
        if(forward == true) {
            return true;
        }
    }

    if(isValid(grid, r, c, curr_i+1, curr_j)) {
        downward = robotInGridBacktrack(grid, r, c, curr_i+1, curr_j, sol);
        if(downward == true) {
            return true;
        }
    }

    // If none of above returned true, then no path. So backtrack and return false
    stackPop(sol);
    return false;
    // We can print the stack from main function for path if the final function returned
    // true to the main function.
}

bool robotInGridDynamic(int **grid, int r, int c, Stack **sol) {
    // Define and initialize sol_arr
    bool sol_arr[r][c];
    int i, j;

    for(i=0; i<=r; i++) {
        for(j=0; j<=c; j++) {
            sol_arr[i][j] = false;
        }
    }
    sol_arr[0][0] = true;

    // Fill first row and first columns of sol_arr
    for(j=1; j<=c; j++) {
        if(grid[0][j] != 0) {
            sol_arr[0][j] = sol_arr[0][j-1];
        }
    }
    for(i=1; 1<=r; i++) {
        if(grid[i][0] != 0) {
            sol_arr[i][0] = sol_arr[i-1][0];
        }
    }

    // Now fill rest of sol_arr
    for(i=1; i<=r; i++) {
        for(j=1; j<=c; j++) {
            if(grid[i][j] != 0) {
                sol_arr[i][j] = sol_arr[i-1][j] | sol_arr[i][j-1];
            }
        }
    }

    // Check if sol_arr[r][c] == false. If yes, no path exists, return false
    if(!sol_arr[r][c]) {
        return false;
    }

    // If path exists, we push the path into stack and then return true
    i=r;
    j=c;
    while(i != 0 || j != 0) {
        stackPush(i, j, sol);
        if((j-1 >= 0) && (sol_arr[i][j-1])) {
            j=j-1;
        } else {
            i=i-1;
        }
    }
    // Now we have full path in stack. We can print this from main function.
    return true;
}





int main(void) {
    // triple step problem
    printf("Number of ways a child can climb 8 steps are %d\n", tripleStep(8));




    return 0;
}
