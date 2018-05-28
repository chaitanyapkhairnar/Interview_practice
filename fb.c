/*
 * This file contains a list of practice questions
 * for fb interview.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
 * Find the minimum window in string S which will contain all the characters in string T
 */




/*
 * Given a tree, write a function to check if it is a binary search tree or not
 */
typedef struct tree_node {
    int data;
    struct tree_node *left;
    struct tree_node *right;
}tree_node;

bool checkIfBinary(tree_node *root, int min, int max) {
    // Base Case
    if(root == NULL) {
        return true;
    }

    if(min == -1 && max == -1) {
        // Root of the tree. This always lies in the range. Update the min and max
        // and proceed.
        bool isLeftBinary = checkIfBinary(root->left, min, root->data);
        bool isRightBinary = checkIfBinary(root->right, root->data, max);
        return (isLeftBinary && isRightBinary);
    }

    if(min == -1) {
        if(root->data >= max) {
            return false;
        }
    } else if(max == -1) {
        if(root->data <= min) {
            return false;
        }
    } else {
        if(root->data >= max || root->data <= min) {
            return false;
        }
    }
    bool isLeftBinary = checkIfBinary(root->left, min, root->data);
    bool isRightBinary = checkIfBinary(root->right, root->data, max);
    return (isLeftBinary && isRightBinary);
}

bool checkBST(tree_node *root) {
    /*
     * A tree is a BST if all the nodes on the left subtree of the root are less
     * than or equal to root and all the nodes on the right subtree of root are
     * greater than the root. We pass two variables min and max to the recursive
     * function along with the root node and for each subtree, we recursively check
     * if the root lies within the range of min and max values of its parent.
     */
    if(root == NULL) {
        return false;
    }
    int minVal=-1;
    int maxVal=-1;
    return checkIfBinary(root, minVal, maxVal);
}

/*
 * 1. Given an array nums, write a function to move all 0's to the end of it
 *    while maintaining the relative order of the non-zero elements.
 */
void move_zeros_to_end(int *array, int len) {
    /* The idea is to have two iterators i and j. j is at -1 initially
     * and we parse the array with i=0 to len. for each i, if we get a
     * non-zero number, we increment j and swap arr[i] with arr[j].
     * If we get a 0 at arr[i], we do nothing. So basically, we are moving
     * non zero elements to front retaining their order. And due to swap
     * operation, 0s will automatically move to end.
     *
     * Time complexity is O(n) and no extra space required.
     * If we want to move zeros to beginning, only if condition will change
     * to if(array == 0). Same thing, if we want to move even/odd numbers.
     */
    int i, j=-1, temp;
    for(i=0;i<n;i++) {
        if(array[i] != 0) {
            j++;
            temp = array[j];
            array[j] = array[i];
            array[i] = temp;
        }
    }
}


/*
 * 2. Given an input array like [1,2,3] and a target like 5,
 *    find all combinations of array that sum up to target.
 *    [2,3] and [3,2] counts for only 1 combination.
 */

/* We use dynamic programming here. We create a boolean 2d array dyn[i][j]
 * such that i is equal to len of array and j is equal to given sum value.
 * the value of dyn[i][j] will be true if there exists elements in subset
 * 0 to i-1 which has sum equal to j.
 * 
 * To fill the elements in this 2d array, we first start with i=0 for all js.
 * i=0 means subset from index 0 to 0. There is no subset present. So, for any value
 * of j (sum), and i=0, there is no subset whose elements will have sum equal to j.
 * So we mark all these elements as false.
 *
 * Now for j=0 and all i's. j=0 means sum=0. i=1 means subset from index 0 to 1.
 * If there are elements in this subset, whose sum will add up to j (which is 0),
 * then we should mark that element as true. Also this means that if we choose to
 * not select any element from the current subset, the sum can be zero. This is true
 * for any subset (any value of i). So for j=0 and all i, we mark the element as true.
 *
 * Now we fill the rest elements. We traverse for i=1 to len and j=1 to sum. For each
 * j, we compare if j < i-1th element in the given array. If it is smaller that means
 * the present sum (value of j) is less than the i-1th element. So, for there to exist
 * elements in subset 0 to i whose sum is equal to j, there should be elements in subset
 * 0 to i-1. (because i-1th element itself is greater than sum, so this element is being
 * excluded from the subset for sure.) So we just copy the result of [i-1][j] in our
 * present element [i][j].
 *
 * But if, the sum (j) > i-1th element in the given array, then we have two
 * possibilities. Either there will be a subset 0 to i-1 whose sum is equal to j. (As
 * in above case where we are excluding the i-1th element for calculating sum). Or there
 * can be a subset 0 to i-1 whose sum is equal to j-array[i-1]. (This is the case where
 * we include the i-1th element in calculating the sum. so, if we include this element,
 * then rest of the elements in the subset should have sum equal to sum-(i-1th)element).
 * So, for this case, the value of [i][j] will be 
 * value of [i-1][j] || value of [i-1][j-element at i-1]
 *
 * Once we have this array, we simply look at [n][sum]. If this is true, that means
 * there exists an element in the array 0 to n whose sum equals to sum.
 *
 * Now to print the combinations whose sum equals given value:
 *
 *
 */
/* Create a 2d boolean array */
bool **dyn_table;

bool issubsetsum(int *arr, int len, int sum) {

    dyn_table = (bool**)malloc(sizeof(bool*)*(len+1));
    for(int k=0;k<=len;k++) {
        dyn_table[k] = (bool *)malloc(sizeof(bool)*(sum+1));
    }

    /* All subsets are true for sum=0 */
    for(int i=0;i<=len;i++) {
        dyn_table[i][0] = true;
    }

    /* If subset is 0, then no way to get any sum out of it */
    for(int j=1;j<=sum;j++) {
        dyn_table[0][j] = false;
    }

    /* Now we fill rest of the elements */
    for(int i=1; i<=len; i++) {
        for(int j=1; j<=sum; j++) {
            if(j < arr[i-1]) {
                dyn_table[i][j] = dyn_table[i-1][j];
            }
            if(j >= arr[i-1]) {
                dyn_table[i][j] = dyn_table[i-1][j] || dyn_table[i-1][j-arr[i-1]];
            }
        }
    }

    /* Now check if the given array has any subset which has sum equal to given value */
    return dyn_table[n][sum];
}

/* Function to recursively traverse dyn_table[][] to find all
 * possible paths from dp[n-1][sum]
 */
void printsubsetwithsum(int *arr, int len, int sum, int *p, int p_index) {
    /* Base case. If we reached to len=0 and sum is still non zero,
     * then check if arr[0] is equal to sum. If yes, print the array
     * p which has all the elements whose sum is equal to given sum.
     */
    if(len == 0 && sum != 0 && dyn_table[0][sum]) {
        p[p_index] = arr[0];
        p_index++;
        for(int i=0;i<p_index;i++) {
            printf("%d ", p[i]);
        }
        return;
    }

    /* Base case. If sum becomes zero, then print the list.
     */
    if(len == 0 && sum == 0) {
        for(int i=0;i<p_index;i++) {
            printf("%d ", p[i]);
        }
        return;
    }

    /* If the current sum can be achieved after ignoring the current element
     * then recursively call the function with same sum but smaller array
     */
    if(dyn_table[len-1][sum]) {
        int *b = p;
        printsubsetwithsum(arr, len-1, sum, b, p_index);
    }

    /* If current sum can be achieved after including the current element
     * then recursively call the function with sum-arr[present]
     */
    if(sum >= arr[i] && dp[i-1][sum-arr[i]]) {
        p[p_index] = arr[i];
        printsubsetwithsum(arr, len-1, sum-arr[i], b, p_index);
    }
}

/*
 * 3. Check if array has duplicates.
 *
 * We use hash table to store the elements of the array as we
 * parse it and check if we already store the data. If yes, there
 * is a duplicate.
 */

bool isduplicate(int *arr, int len) {
    int *hash = (int *)calloc(500, sizeof(int));
    for(int i=0;i<len;i++) {
        if(hash[arr[i]]) {
            return true;
        } else {
            hash[arr[i]]++;
        }
    }
}

/* Time complexity is O(n) and Need O(n) extra space.
 */

/*
 * 4. Merge two sorted arrays in linear time.
 *
 * We create a new array which will have merged values. We initialize
 * i, j and k iterators and for whole length of arrays, we compare
 * a[i] and b[j] and insert whichever is smaller in result[k].
 * Then we check if array a or b is remaining and insert all the remaining
 * elements in result.
 *
 * To do it in place, we start iterating array2 from last to first. Inside
 * this loop, we first store last element on array1 in temp variable, and
 * then start a loop for array1 starting from len-1 to start comparing
 * if arra1 element is greater than array2 element. If yes, then we copy
 * jth element in j+1 and do j--. This is to make space in array 1. Finally
 * we put array2's element in array 1's position and continue.
 *
 * This is O(m*n) complexity.
 */

int* mergesorted(int *a, int *b, int len1, int len2) {
    int *result = (int *)malloc(sizeof(int)*(len1+len2));

    int i=0, j=0, k=0;

    while(i<len1 && j<len2) {
        if(a[i] < b[j]) {
            result[k] = a[i];
            i++;
            k++;
        } else {
            result[k] = b[j];
            j++;
            k++;
        }
    }
    while(i<len1) {
        result[k] = a[i];
        k++;
        i++;
    }

    while(j<len2) {
        result[k] = b[j];
        k++;
        j++;
    }
    return result;
}
/* Time complexity is O(m+n) and extra space required is also O(m+n)
 */


/*
 * 5. Length of longest increasing subarray.
 *
 * subarray means continuous array within given array. We have a max_len
 * and len variables. We traverse given array one by one and compare if
 * next element is greater than current. If yes, we increment the len
 * and proceed. If not, we compare len with max_len and if len is greater,
 * we copy that in max_len. In the end of traversal, we have max len of
 * subarray. If we are asked to print the subarray, we can maintain a structure
 * which has start and end index of subarray. We update this whenever we update
 * the max_len.
 */

int LongestIncreasingSubarray(int *arr, int n) {
    int len=0, max_len=0;
    for(int i=0;i<n-1;i++) {
        if(arr[i] < arr[i+1]) {
            len++;
        } else {
            if(len > max_len) {
                max_len = len;
            }
            len=0;
        }
    }
    if(len > max_len) {
        max_len = len;
    }
    return max_len;
}

/*
 * Longest increasing subsequence in an array.
 * subsequence means subset of array. It need not to be continuous. It is not
 * subarray. We need to find longest subsequence in the given array which is in
 * increasing order.
 *
 * The idea here is to use dynamic programming. We maintain a array list[] which
 * stores the longest length of subsequence for each index i such that list[i] has
 * the value of longest length of subsequence in given array from 0 to present element
 * i. We first initialize list[] to all 1s as minimum length of subsequence will be
 * 1 for each element including itself. Then we keep filling this array by traversing
 * the given array such that if the current element in the given array is greater than
 * any of its previous elements, then the length of subsequence for this array element
 * in list[] is equal to 1+length of subsequence for the element which is smaller than
 * this element. And we update this only if the present list[] value is smaller than the
 * new computed value. Once we are done with this, the max number present in list[] is
 * the max length of subsequence for the given array.
 */

int LengthOfLongestIncreasingSubseq(int *arr, int len) {
    int *list = (int*)malloc(sizeof(int)*len);
    /* Initialize list to all 1s. */
    for(int j=0; j<len; j++) {
        list[j] = 1;
    }

    /* Now we traverse the given array and start updating the list[] */
    for(int i=1; i<len; i++) {
        for(int j=0; j<i; j++) {
            if((arr[i] > arr[j]) && (list[i] < list[j]+1)) {
                list[i] = list[j]+1;
            }
        }
    }

    /* Now we have completely update the list[]. We get the max
     * value of list[] and this is our solution.
     */
    int max = 0;
    for(int i=0; i<len; i++) {
        if(max < list[i]) {
            max = list[i];
        }
    }
    return max;
}
/*
 * Time Complexity is O(n^2). This can also be done in O(nlogn). The solution is below.
 */

/*
 * https://www.geeksforgeeks.org/longest-monotonically-increasing-subsequence-size-n-log-n/
 *
 * The idea is to maintain an array which has only the last element of all possible
 * active lists till present. If for current iteration, the element in the given array
 * is smaller than the smallest element present in the active list array, replace it with
 * 0th element in the active list. If the element in the given array is greater than largest
 * element in the active list array, add this element to the active list array at the end.
 * If the element in the given array is greater than some elements but smaller than some others
 * then get the 1st greater element in the active list array and replace it with the current
 * element. In the end, the length of the active list array is the solution.
 */

int get_index(int *active_lists, int left, int right, int key) {
    /* This function finds the first element in the sorted array active_lists which
     * is greater than or equal to the key. It uses binary search approach.
     */
    int mid;
    while ((right-left) > 1) {
        mid = left + ((right-left)/2);
        if(active_lists[mid] >= key) {
            right = mid;
        } else {
            left = mid;
        }
    }
    return right;
}


int LengthOfLongestSubsequenceNLogN(int *arr, int len) {
    /* Array to maintain last elments of active lists */
    int *active_lists = (int *)malloc(sizeof(int) * len);
    /* index of active_lists which points to next available slot. */
    int index = 1;
    /* Initialize array with single list which has last element as arr[0] */
    active_lists[0] = arr[0];
    /* Iterate through array and keep updating the active_lists array */
    for(int i=1; i<len; i++) {
        if(arr[i] < active_lists[0]) {
            active_lists[0] = arr[i];
        } else if (arr[i] > active_lists[index-1]) {
            active_lists[index] = arr[i];
            index++;
        } else {
            /* If the arr element is greater than some elements and smaller than others
             * in the active_lists, then find the place in active_lists where we can
             * replace the current element with the present one.
             */
            int new_index = get_index(active_lists, -1, len-1, arr[i]);
            active_lists[new_index] = arr[i];
        }
    }
    return (index-1);
}

/*
 * Time complexity for this approach is O(NLog(N))
 * If we want to print the subsequence, follow the link below
 * https://www.geeksforgeeks.org/construction-of-longest-monotonically-increasing-subsequence-n-log-n/
 */

/*
 * Longest common subsequence problem.
 * Given two strings, find the longest common subsequence between them.
 *
 * We use dynamic programming approach here. We have two strings S1 and S2.
 * For each character in these strings, we compare and calculate the length of
 * the common subsequence till here as follows:
 * Let the present character index of S1 be i and of S2 be j.
 * 1. If S1[i] == S2[j] then the length of common subsequence is 1 + length of
 * subsequence at S1[i-1], S2[j-1]. Because we include this present character in the
 * subsequence.
 * 2. If S1[i] != S2[j] then the length of common subsequence is max of length of
 * common subsequence at S1[i-1], S2[j] and S1[i], S2[j-1].
 *
 * Now we have two equations, we implement it first via recursion and then via tabular
 * form of dynamic programming. In dynamic programming, the idea is to maintain a table
 * of all the possible lengths of common subsequences so that we do not calculate
 * them again and again.
 */
int max(int i1, int i2) {
    if(i1 > i2) {
        return i1;
    } else {
        return i2;
    }
}

int lcs_recursive(char *s1, char *s2, int l1, int l2) {
    /* base case */
    if(l1 ==0 || l2 == 0) {
        return 0;
    }
    if(s1[l1-1] == s2[l2-1]) {
        return (1 + lcs_recursive(s1, s2, l1-1, l2-1));
    } else {
        return max(lcs_recursive(s1, s2, l1, l2-1), lcs_recursive(s1, s2, l1-1, l2));
    }
}
/*
 * Time complexity for this is O(2^n) in worst case.
 * We can improve this by using dynamic programming. We build a table
 * and maintain it.
 */
int lcs_dynamic(char *s1, char *s2, int l1, int l2) {
    /* Create a 2d table to store the lengths of common
     * subsequence. table[i][j] will store the max length
     * of subsequence of s1 till index 1 and s2 till index j.
     */
    int **table;
    table = (int **)malloc(sizeof(int *)*l1);
    for(int i=0; i<l1; i++) {
        table[i] = (int *)malloc(sizeof(int) *l2);
    }

    /* We iterate the strings and build the table */
    for(int i=0; i<l1; i++) {
        for(int j=0; j<l2; j++) {
            if(i == 0 || j == 0) {
                table[i][j] = 0;
            } else if (s1[i-1] == s2[j-1]) {
                table[i][j] = 1 + table[i-1][j-1];
            } else {
                table[i][j] = max(table[i][j-1], table[i-1][j]);
            }
        }
    }
    return table[l1][l2];
}



/*
 * Maze Problem. Given a 2d array which represents maze where 1 means a path
 * and 0 means no path, find the path from top left(0,0) to bottom right (n-1, n-1).
 * We can move only in forward or downward direction.
 *
 * Here we use recursion and backtracking. We first define a utility function to
 * check if the next move is valid by checking if the indices are within the range
 * (NxN) and the value at that point is 1. We define another 2d solution matrix.
 * We start with 0,0 and mark 0,0 as 1 in solution matrix. Then we recursively
 * call the function for forward direction. If this returns false, we call the
 * function for downward direction. The base case is if x,y = n-1,n-1. i.e.
 * we reached destination. In this case, return true. Finally we print the solution
 * matrix which has the path. Here we are not marking any cell as visited. So, we
 * may visit a cell multiple times. The time complexity of this is O(2^(r+c)) where
 * r is number of rows and c is number of columns. This is because, as we can move
 * in forward to downward direction, total number of steps in each path in worst
 * case is r+c. and for each step, we make 2 choices either to go forward or down.
 *
 * We can improve this time complexity to O(rc), by avoiding computations for the
 * cells again if we have already done it. We use a visited array for this. Whenever
 * we visit a point (x,y), we mark it visited. And before visiting any point, we
 * check if it is already visited or not. One simple hash function to use is
 * 2x+3y. here x and y are coordinates of the maze. For each x,y visited, we mark
 * visited[2x+3y] = true. Another simpler way is to use a 2d visited array and
 * for x,y mark visited[x][y] = true.
 */

//Maze size
#define N 4

//visited array
bool visited[2N+3N] = {false};

bool isValidDirection(int maze[N][N], int x, int y) {
    if(x>=0 && y>=0 && x<N && y<N && maze[x][y] == 1 && !visited[2*x + 3*y]) {
        // Mark this point as visited
        visited[2*x + 3*y] = true;
        return true;
    } else {
        return false;
    }
}

//Recursive function to get path and store it in solution matrix
bool getPath(int maze[N][N], int x, int y, int solution[N][N]) {
    
    //Base case
    
    if(x == (N-1) && y == (N-1)) {
        solution[x][y] = 1;
        return true;
    }

    //Check if x,y are valid and only then proceed
    
    if(isValidDirection(maze, x, y)) {
        
        bool possible = false;
        //Mark current vertex in solution matrix and recurse
        //for forward path.
        solution[x][y] = 1;
        possible = getPath(maze, x+1, y, solution);
        
        // If no path in forward direction, try to get path
        // by moving downwards.
        if(!possible) {
            possible = getPath(maze, x, y+1, solution);
        }

        // If no path in downward direction too, backtrack
        // solution[x][y] to 0 as no path from current vertex
        // and return false.
        if(!possible) {
            solution[x][y] = 0;
            return false;
        } else {
            return true;
        }
    } else {
        return false;
    }
}

//Main function calling the above function to get path.
//We have to find path from x,y to N-1,N-1
void getSolutionForMaze(int maze[N][N], int x, int y) {
    //Initialize solution matrix to all 0s
    int solution[N][N] = {{0,0,0,0},
                          {0,0,0,0},
                          {0,0,0,0},
                          {0,0,0,0}};
    if(getPath(maze, x, y, solution)) {
        printf("Path found from %d,%d to %d,%d\n", x, y, N-1, N-1);
        for(int i=0;i<n;i++) {
            for(int j=0;j<N;j++) {
                printf("%d ", solution[i][j]);
            }
            printf("\n");
        }
    } else {
        printf("There is no path from %d,%d to %d,%d\n", x, y, N-1, N-1);
    }
}

/*
 * Time complexity is O(N*N).
 */

/*
 * Stock Buy/Sell Problem. Given an array of stock prices for each day,
 * give a list of buy/sell pairs to gain maximum profit.
 * For eg. stock = [100, 180, 260, 310, 40, 535, 695]
 * Result = Buy on day 0 and sell on day 3 and again 
 *          Buy on day 4 and sell on day 6.
 *
 * The idea here is to get the local minima and local maxima for the 
 * array starting from index 0. Buy on local minima day and sell on local
 * maxima day. Then continue to find another local minima and maxima for
 * rest of array.
 * We use an array of structure to store the buy/sell pairs.
 */

typedef struct schedule {
    int buy;
    int sell;
}schedule;

void StockBuySell(int price[], int len) {
    /* We should have atleast 2 entries in the price[]
     * to buy and sell.
     */
    if(len <= 1) {
        printf("Not sufficient data\n");
        return;
    }
    int localMinima, localMaxima;
    int i = 0, count=0;
    schedule result[(len/2)+1]
    while (i < (len-1)) {
        while ((i<(len-1)) && (price[i] >= price[i+1])) {
            i++;
        }
        if(i == len-1) {
            break;
        }
        localMinima = i;
        i++;
        while((i<len) && (price[i] >= price[i-1])) {
            i++;
        }
        localMaxima = i-1;
        result[count].buy = localMinima;
        result[count].sell = localMaxima;
        count++;
    }
    if(count == 0) {
        printf("We cannot buy and sell to make profit\n");
    } else {
        printf("The schedule of buying and selling the shares is as below:\n");
        for(int j=0; j< count; j++) {
            printf("Buy on day %d and sell on day %d\n", result[j].buy, result[j].sell);
        }
    }
    return;
}
/*
 * Time complexity is O(n)
 */
