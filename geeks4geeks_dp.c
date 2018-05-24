/*
 * This file contains dp problems from geeks for geeks forum.
 */

/*
 * 1. Longest common subsequence: Given 2 strings, find the length of longest
 *    common subsequence between them.
 *
 *    Say strings are AGGTAB and GXTXAYB, so longest common subsequence is
 *    GTAB of length 4. The idea is to start traversing the strings from end
 *    and if the chars are same, then the length of subsequence = 1 + length
 *    of subsequence by using both strings of len-1. If the chars are not
 *    equal, then the length will be max(len(str1-1, str2), len(str1, str2-1))
 *    This can be implemented using recursion but it involves lot of repetitive
 *    work. So we use DP instead.
 *
 *    We maintain a 2d array with rows representing one string and columns
 *    representing another string. Say m and n be lengths of the strings.
 *    we take arr[m+1][n+1]. We take lengths+1 for our arr because 0th index
 *    means that particular string is empty. So for any columns, row=0 means
 *    we are considering the case where we have str2 with 1/2/3/.. chars but
 *    there is no str1. For all these cases, the length of common subsequence
 *    will be 0. Similarly for column 0 and all row values. Thus we have
 *    initialized our 2d array. Now we start filling it.
 *
 *    Note that arr[i][j] contains the length of longest common subsequence
 *    for str1[0...i-1] and str2[0...j-1].
 *
 *    We return arr[m][n] which is the answer.
 */
int lcs(char *str1, int m, char *str2, int n) {
    int dp[m][n];

    for(int i=0; i<m; i++) {
        for(int j=0; j<n; j++) {
            if(i==0 || j==0) {
                dp[i][j] = 0;
            } else {
                if(str1[i-1] == str2[j-1]) {
                    dp[i][j] = 1 + dp[i-1][j-1];
                } else {
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
                }
            }
        }
    }
    return dp[m][n];
}

/*
 * Now to find the sequence, we start with x=m and y=n and check if str[x-1]
 * is equal to str2[y-1]. If yes, we store this char in result string at its
 * last index. If not same, then we check in our dp array which one is greater
 * (i-1,j) or (i,j-1) and update x and y accordingly.
 */
void printLcs(char *str1, int m, char *str2, int n, int **dp, int substringLen) {
    int x=m, y=n, z=substringLen;
    char res[substringLen];
    while(x>0 && y>0) {
        if(str1[x-1] == str2[y-1]) {
            res[z] = str1[x-1];
            x--;
            y--;
            z--;
        } else {
            if(dp[x-1][y] > dp[x][y-1]) {
                x--;
            } else {
                y--;
            }
        }
    }
    printf("%s\n", res);
}

/*
 * 2. Maximum sum subarray: Given a array of +ve and -ve integers, return the
 *    max sum that a subarray makes.
 *
 *    We maintain 2 variables, currSum and maxSum. We iterate the array and for
 *    each iteration, we update currSum=max(arr[i], currSum+arr[i]) and we
 *    update maxSum=max(currSum, maxSum). Finally at the end of array, we return
 *    maxSum.
 */
int maxSumSubarray(int *arr, int len) {
    int currSum=arr[0];
    int maxSum=arr[0];

    for(int i=1; i<len; i++) {
        currSum = max(arr[i], currSum+arr[i]);
        maxSum = max(maxSum, currSum);
    }
    return maxSum;
}

/*
 * 3. Maximum square matrix: Given a 2d matrix, find the max size of submatrix
 *    that has all 1s in it.
 *
 *    The basic idea is to consider each element in the given matrix and find
 *    out the size of square it forms. For this, we create a dp array of same
 *    size of given matrix and initialize it by copying first row and column
 *    as it is. Then starting from i=1 and j=1, for each element, we check if
 *    it is 1 and its neighbors (i-1,j), (i,j-1) and (i-1,j-1) are 1s. If yes,
 *    then this element forms a square of size 2. So we update its value. If
 *    not, we dont update the value. This way we get the max size.
 */
int maxSquareMatrix(int **grid, int m, int n) {
    int dp[m][n];
    int maxSize=0;

    for(int i=0; i<m; i++) {
        dp[i][0] = grid[i][0];
    }

    for(int j=0;j<n;j++) {
        dp[0][j] = grid[0][j];
    }

    for(int i=1; i<m; i++) {
        for(int j=1; j<n; j++) {
            if(grid[i][j] == 1) {
                dp[i][j] = 1 + min(dp[i-1][j], dp[i][j-1], dp[i-1][j-1]);
                if(dp[i][j] > maxSize) {
                    maxSize = dp[i][j];
                }
            } else {
                dp[i][j] = 0;
            }
        }
    }
    return maxSize;
}

/*
 * 4. Longest Increasing Subsequence: Given an array of integers, find the
 *    length of the longest increasing subsequence.
 *
 *    We define a dp array of same size of given array and initialize it to
 *    all 1s because, for each index, the length of longest increasing
 *    subsequence is atleast 1 (including only that element). Now, we start
 *    iterating from 1 to n, and for each i, we have j from 0 to i-1. So this
 *    is a n^2 approach. For each iteration, we compare i and j elements and
 *    update the dp array accordingly with the length of longest increasing
 *    subsequence till that index.
 */
int longestIncreasingSubsequence(int *arr, int len) {
    int max=0;
    int dp[len] = {1};

    for(int i=1; i<len; i++) {
        for(int j=0; j<i; j++) {
            if(arr[i] > arr[j] && dp[i] < dp[j]+1) {
                dp[i] = dp[j]+1;
                if(max < dp[i]) {
                    max = dp[i];
                }
            }
        }
    }
    return max;
}

/*
 * 5. Min cost path: Given a 2d cost matrix of +ve integers, find the min
 *    cost to reach the bottom right corner from 0,0. You can go right,
 *    down or diagonally down.
 *
 *    We define a dp matrix of same size as cost matrix. The key is to
 *    initialize this matrix based on the allowed directions.
 *
 *    Start point is 0,0 so put the value of cost[0][0] into dp[0][0].
 *    Now we can move only in right, down or diagonally down direction.
 *    So, based on this, all elements in first row can be reached only
 *    by moving right from 0,0. Because there are no elements above them.
 *    So there is only 1 way to update these elements and that is by
 *    adding their cost to the cost of their prev element. So we update
 *    all the elements in first row of dp as dp[0][j] = dp[0][j] +
 *    dp[0][j-1]. Now, similarly, for all elements in first column,
 *    the only way to update them is by going down from 0,0 as there are
 *    no elements to the left of them. So we update all elements in first
 *    column as dp[i][0] = dp[i][0] + dp[i-1][0]. Once we are done with
 *    this initialization, we start a loop for i=1 to row_len and j=1 to
 *    column_len and for each element, we now consider all three possibilities
 *    to reach it and get the min of these 3 options and update the cost.
 *    Finally, the cost at dp[m][n] has the required answer.
 */
int minCostPath(int **cost, int m, int n) {
    int dp[m][n];

    // Initialize dp matrix
    dp[0][0] = cost[0][0];

    for(int j=1; j<n; j++) {
        dp[0][j] = dp[0][j-1] + cost[0][j];
    }

    for(int i=1; i<m; i++) {
        dp[i][0] = dp[i-1][0] + cost[i][0];
    }

    // Now update rest of dp matrix
    for(int i=1; i<m; i++) {
        for(int j=1; j<n; j++) {
            dp[i][j] = min(dp[i-1][j], dp[i][j-1], dp[i-1][j-1]) + cost[i][j];
        }
    }

    return dp[m][n];
}

/*
 * 6. Coin Change: Given a value N and a list of coin values, return all the
 *    ways to get the value N using any number of given coins.
 *
 *    We use a dp array of size N here. At each index, it contains the number
 *    of ways to get the value=index using given coins. Say, we are given
 *    coins {1, 3, 5}. So, in our dp array, sum 0 can be achieved by 1 way.
 *    Sum 1 can be achieved by 1 way by using 1 coin with value 1. Sum 2 can
 *    be achieved by 1 way by using 2 coins of value 1. Sum 3 can be achieved
 *    by 2 ways, 1 by using 3 1 value coins and another by using 1 coin of value
 *    3. Similarly we have 2 ways to achieve 4 and 5. Now from 6 onwards, the
 *    total number of ways will be addition of total number of ways of getting
 *    [i-1], [i-3] and [i-5] values. This is because if we have total ways of
 *    getting i-1 value, then using a 1 value coin to all these ways, we can
 *    get present value i. Similarly for all ways to get i-3, we add coin 3 to
 *    get present value i. Same for i-5 case.
 *
 *    So the basic idea is, based on the given coins, first initialize our dp
 *    array and then start iterating to fill rest of the array. This is O(mn)
 *    approach where n is the required sum and m are the number of coins given.
 */
int coinChange(int N, int *coins, int len) {
    int dp[N+1] = {0};

    // We can achieve sum 0 with 1 way of not using any coins
    dp[0] = 1;

    // Now we iterate through coin list and for each coin, we iterate
    // till N and update dp
    for(int i=0; i<len; i++) {
        for(int j=coins[i]; j<=N; j++) {
            dp[j] = dp[j] + dp[j-coins[i]]; // Add number of ways from each coin to N
        }
    }
    return dp[N];
}

/* Another way to look at this is, for each coin, we can either include the coin
 * in our sum or we exclude this coin from our sum and proceed. So we have two
 * options. And total number of ways is the addition of number of ways for these
 * two options. So we use a 2d dp array with rows representing the sum and columns
 * representing the coins. We initialize dp[0][j] = 1 for all j as for sum 0,
 * we have 1 way for any number of coins and that is not to use any coin. Now
 * for row=1 to N and for column=0 to number of coins, we fill the dp array by
 * considering both options, either to include present coin in sum or to exclude
 * it. If we include the present coin, then the value will be dp[i-coin[j]][j]
 * and if we exclude the present coin, then the value will be dp[i][j-1]. We
 * have to check if our indices are going out of bounds. If yes, then that case
 * is not possible, so we put 0. Time complexity is same O(mn), but we use extra
 * space O(mn).
 */
int coinChange2d(int N, int *coins, int len) {
    int dp[N+1][len] = {0};
    
    // Initialize for sum=0
    for(int j=0; j<len; j++) {
        dp[0][j] = 1;
    }

    for(int i=1; i<=N; i++) {
        for(int j=0; j<len; j++) {
            int inc=0, exc=0;

            // Number of ways by including current coin
            if(i-coins[j] >= 0) {
                inc = dp[i-coins[j]][j];
            } else {
                inc = 0;
            }

            // Number of ways by excluding current coin
            if(j-1 >= 0) {
                exc = dp[i][j-1];
            } else {
                exc = 0;
            }

            // Update total number of ways
            dp[i][j] = inc + exc;
        }
    }
    return dp[N][len-1];
}

/*
 * 7. Min edit distance: Given two strings str1 and str2, find min number of
 *    edits required on str1 to convert it to str2. We can do 3 operations
 *    on str1, add a char, remove a char or replace a char.
 *
 *    This problem is very similar to other DP problems. First we see what these
 *    operations mean. Say i is str1 iterator and j is str2 iterator and add or
 *    delete char means we are doing these operations to the left of current char.
 *    Now i and j are pointing to some chars in both strings. At this point, if
 *    we want to add a char in str1, it means we added char at i-1st position
 *    that matches jth char in str2. So we let remain i and do j++. Similarly,
 *    when we delete a char, it means we delete ith char in str1, so we do i++
 *    and let remain j. If we replace ith char in str1, then we do i++ and j++.
 *    If ith and jth char were same, we dont do any operation and proceed.
 *
 *    Based on this, we can map the operations as (i, j-1), (i-1, j-1), (i-1, j).
 *    Now, for each char, we need to get the min distance. So, we get min of above
 *    values and add 1 to it.
 *
 *    So, we define a 2d dp array of size m*n where m is length of str1 and n is len
 *    of str2. We initialize it as dp[0][0] = 0 if 0th char of both strings match.
 *    If not, then dp[0][0] = 1 as we did a replace operation here. Now we
 *    initialize first row as dp[0][j] = 1 + dp[0][j-1] because for each column in
 *    the first row, we need to do an add operation on the string in addition to
 *    the operations done to previous char. Similarly, for first columns, we do
 *    dp[i][0] = 1 + dp[i-1][0] because, for each of these columns, we need to do
 *    a delete operation + operations done to prev char. Thus we have initialized
 *    our dp array. Now for row and column 1 to n and m respectively, we check if
 *    ith and jth char match. If yes, we dont do any operation here so we copy
 *    i-1, j-1 values here. If they dont match, then we do 1 operation here which
 *    can be any of the 3 operations. we get min of (i, j-1), (i-1, j-1), (i-1, j)
 *    and add 1 to it. Finally at dp[m][n], we have the solution.
 */
int minEdit(char *str1, int m, char *str2, int n) {
    int dp[m][n];
    if(str1[0] == str2[0]) {
        dp[0][0] = 0;
    } else {
        dp[0][0] = 1;
    }

    for(int i=1; i<m; i++) {
        dp[i][0] = 1 + dp[i-1][0];
    }

    for(int j=1; j<n; j++) {
        dp[0][j] = 1 + dp[0][j-1];
    }

    // Now fill the rest of dp
    for(int i=1; i<m; i++) {
        for(int j=1; j<n; j++) {
            if(str1[i] == str2[j]) {
                dp[i][j] = dp[i-1][j-1];
            } else {
                dp[i][j] = 1 + min(dp[i][j-1],dp[i-1][j],dp[i-1][j-1]);
            }
        }
    }

    return dp[m-1][n-1];
}

/*
 * 8. Cutting a Rod: Given a rod of length n and an array of n elements where
 *    each element represents the price of piece of length index+1, return the
 *    max price we can get by cutting the rod at different places.
 *
 *    The idea is to have an array of size n+1 which has the max price we can
 *    get by cutting the rod of length index+1. We initialize dp[0]=0. Now
 *    we start i from 1 to n and for this, we start j from 0 to i. At each
 *    index i, we calculate max_val = price[j] + dp[i-j]. What this means is,
 *    for a rod of length i, we can get max val by trying a cut at each
 *    position j (from 0 to i) and then getting the max val of all these values
 *    If we try a cut at j, then the max val will be price of piece of length j
 *    plus max val we got for piece of total length - j. We keep doing this and
 *    we will have the answer in dp[n]. Time complexity is O(n^2).
 */
int maxValRodCut(int *price, int n) {
    int dp[n+1];
    int maxVal=-1;

    dp[0] = 0;

    for(int i=1; i<=n; i++) {
        maxVal = -1;
        for(int j=0; j<i; j++) {
            maxVal = max(maxVal, price[j]+dp[i-j-1]);
        }
        dp[i] = maxVal;
    }

    return dp[n];
}

/*
 * 9. Subset Sum: Given an array of integers and a sum value, return true if a
 *    subset exists within the given array which has the given sum.
 *
 *    For each index, there are two options, either include it in the subset
 *    to check if the sum exists, or exclude this element from the subset.
 *    If we try to do it recursively, then it is exponential time complexity.
 *    So we use DP instead.
 *
 *    We maintain a 2d dp array where dp[i][j] = true means there exists a subset
 *    in 0 to i-1 which has sum equal to j.
 *    We initialize dp[i][0] to true as for any set, sum=0 can be achieved by
 *    choosing a subset with no elements in it. Also dp[0][j]=false as if we
 *    have no members in subset but have non zero sum, then there exists no
 *    subset.
 *
 *    Now we start filling dp for i=1 to n and j=1 to given sum. For each case,
 *    we check if the current element arr[i-1] > sum j. If yes, then there is
 *    only 1 option, not to include this element. So we update dp[i][j] = 
 *    dp[i-1][j]. But if arr[i-1] < sum, then we can include this element and
 *    check for subset and also exclude this element and check for the subset.
 *    so dp[i][j] = dp[i-1][j] || dp[i-1][j-arr[i-1]]. We get the final answer 
 *    in dp[len][sum] where len is length of given array. Time complexity
 *    is O(sum*len). We can also print all these subsets by traversing the dp
 *    array from bottom right. For each dp[i][j], we see if dp[i-1][j] is true
 *    Then we add it to path and recursively call the function for i-1. Now, we
 *    check if dp[i-1][j-arr[i] is true, then we add this element arr[i] into list
 *    and then recursively call for i-1 and sum-arr[i].
 */
bool subsetSum(int *arr, int len, int sum) {
    bool dp[len+1][sum+1];

    for(int i=0; i<=len; i++) {
        dp[i][0] = true;
    }

    for(int j=1; j<=sum; j++) {
        dp[0][j] = false;
    }

    for(int i=1; i<=len; i++) {
        for(int j=1; j<=sum; j++) {
            if(arr[i-1] > j) {
                dp[i][j] = dp[i-1][j];
            } else {
                dp[i][j] = dp[i-1][j] || dp[i-1][j-arr[i-1]];
            }
        }
    }

    return dp[len][sum];
}

/*
 * 10. Min jumps to reach end: Given an array where each element represents
 *     max number of steps you can jump from that position, return min jumps
 *     required to reach the end of array.
 *
 *     One approach is maintain another dp array of same size as given array
 *     dp contains min number of jumps required to reach current index from 0.
 *     Start traversing the given array, and for each i, get the value of arr[i]
 *     and update all the indices from i to arr[i] steps with min steps = 
 *     min(existing val, 1+value at dp[i]). Once we are done with the traversing,
 *     the value at dp[len] has min jumps required. This is O(n^2) approach
 */
int minJumps(int *arr, int len) {
    int dp[len] = {9999};
    dp[0] = 1;

    for(int i=0; i<len; i++) {
        j = i + 1;
        max_step = arr[i];
        if(max_step == 0) {
            continue;
        }
        for(int k=0; k<max_step; k++) {
            dp[j+k] = min(dp[j+k], 1+dp[i]);
        }
    }
    return dp[len-1];  // If it is unreachable, the value will be >=9999
}

/* Another way to do it in O(n) is to maintain 3 variables maxReach, step, jump.
 * We update these variables for each iteration of array. maxReach stores the
 * max reachable index based on current arr[i] value, step stores the number of
 * steps we can still take and jump stores number of jumps we took till now.
 * Whenever steps become 0, we increment jump.
 *
 * We initialize maxReach=arr[0], steps=arr[0] and jump=1.
 *
 * Now, for i=1 to len of array, we update maxReach = max(maxReach, i+arr[i])
 * We also decrement step by 1 as we took 1 step to come here. We now check if
 * step became 0. If yes, we increment jump by 1 anc check if i >= maxReach.
 * If yes, then it is not reachable, so return -1. If no, then we update 
 * step = maxReach - i. We also check if i reached len-1, then we reach the 
 * value of jump.
 */
int minJumpsLinearTime(int *arr, int len) {
    int maxReach = arr[0];
    int steps = arr[0];
    int jumps = 1;

    for(int i=1; i<len; i++) {
        if(i == len-1) {
            return jump;
        }
        maxReach = max(maxReach, arr[i]+i);
        step--;

        if(step == 0) {
            jump++;
            if(i > maxReach) {
                return -1;
            }
            step = maxReach-i;
        }
    }
    return -1;
}

/*
 * 11. Assembly line problem: In a car factory, there are two assembly lines
 *     with n stations each. Both the assembly lines are exact replicas of each
 *     other. We are given time each car spends on each station. We are also
 *     given entry time and exit time for both the assembly lines. A car can
 *     move from station i on one assembly line to station i+1 either on
 *     same assebly line or on different assembly line. If it moves to different
 *     assembly line, then extra time is taken. This time is also given to us.
 *     We need to find the min time a car can take from start to end. e.g.
 *
 *     Line 1 ------S1------S2------S3------S4------EXIT
 *                    \    /
 *                     \  /
 *                      \/
 *                     / \
 *                    /   \
 *     Line 2 ------S1-----S2------S3------S4------EXIT
 *
 *     time[2][i] has times for i stations S1, S2, ... for both lines
 *     time[0][0] means start time for line 0 and time[0][n] means end
 *     time for line 0.
 *     transition[2][i] has times if a car moves from 1 line to another.
 *     transition[0][2] means time required to move to station 2 on line 2
 *     from line 1.
 *
 *     We use DP here. We define two arrays minT1[n] and minT2[n] where n
 *     are the number of stations. These arrays will have the min time taken
 *     by car to exit ith station on line 1 and 2 respectively.
 *
 *     To initialize, we do minT1[0] = time[0][0] + time[0][1]
 *     and minT2[0] = time[1][0] + time[1][1].
 *     Now we start filling the arrays by using below formula
 *     minT1[i] = min(minT1[i-1] + time[0][i], minT2[i-1]+time[0][i]+transition[1][i])
 *     Similarly for minT2[i] too.
 *
 *     What this means is, for each station, we get the min time required to exit
 *     this station by taking into consideration 2 options. Either the car came
 *     to this station from previous station on same line, or it came from
 *     previous station from different line. We update whatever value is minimum.
 */

/*
 * 12. Max sum of increasing subsequence: Given an array of integers, return the
 *     max sum that can be achieved by considering the elements in the array in
 *     increasing order.
 *
 *     This problem is very similar to longest increasing subsequence problem.
 *     In that problem, we calculated the length of the longest increasing
 *     subsequence, and here we need to calculate the sum of longest increasing
 *     subsequence. We follow similar O(n^2) approach. The only difference is, in
 *     our DP array, instead of storing the length values, we store the sum values.
 */
int longestIncreasingSum(int *arr, int len) {
    int dp[len];
    int maxS=0;

    // Initialize dp with values of arr as for each element, this can be the
    // min sum.
    for(int i=0; i<len; i++) {
        dp[i] = arr[i];
    }

    // Now, we start traversing the arr and update the values in dp
    for(int i=1; i<len; i++) {
        for(int j=0; j<i; j++) {
            if(arr[i] > arr[j]) {
                dp[i] = max(dp[i], arr[i]+dp[j]);
                maxS = max(maxS, dp[i]);
            }
        }
    }
    return maxS;
}

/*
 * 13. Maximum chain length: We are given a list of tuples where in each tuple,
 *     first number is always smaller than the second one. We want to build a
 *     chain of these tuples such that (a,b)->(c,d) is possible only if c>b.
 *     We have to return the max length of chain than can be formed.
 *
 *     We can build a chain only if the last number of first tuple is less than
 *     the first number of second tuple and so on. This is again similar to
 *     longest increasing subsequence problem. First we sort the given list of
 *     tuples based on the first numbers. Then we apply the longest increasing
 *     subsequence approach by comparing the first number of current element
 *     with the last number of previous element and update the lengths. Finally,
 *     we return the max length. Time complexity is O(n^2).
 */

/*
 * 14. Longest common substring: Given two strings, find the length of longest
 *     common substring.
 *
 *     We can do it in O(m*n) time where m and n are the lengths of the
 *     strings. We maintain a 2d DP array which stores the longest common
 *     suffix for each index of both the strings. The max length of longest
 *     common suffix is our longest common substring.
 *
 *     To find the longest common suffix, we iterate first string and for each
 *     of this, we iterate second string. We compare the chars of each string
 *     and if they are same, then the length of common suffix is 1 + length
 *     for previous chars. If they are not same, then there is no common suffix
 *     so we put it as 0.
 *
 *     We take the DP array of length n+1 by m+1 because we consider the case
 *     of row=0 and column=0 which means either of the strings does not exist.
 *     In this case, the lenght of suffix is always 0. This is what we
 *     initialize. Then we fill the rest of array.
 */
int longestCommonSubstring(char *str1, int m, char *str2, int n) {
    int dp[m+1][n+1];
    int maxSuffix=0;

    for(int i=0; i<m; i++) {
        for(int j=0; j<n; j++) {
            if(i==0 || j==0) {
                dp[i][j] = 0;
            } else {
                if(str1[i-1] == str2[j-1]) {
                    dp[i][j] = 1 + dp[i-1][j-1];
                    maxSuffix = max(maxSuffix, dp[i][j]);
                } else {
                    dp[i][j] = 0;
                }
            }
        }
    }

    return maxSuffix;
}

/*
 * 15. Total number of ways: Find total number of ways to reach the cell (n,m)
 *     from cell (0,0) with the constraint that we can move only in forward or
 *     downward direction.
 *
 *     We use a 2d DP array of size mXn to store total number of ways to reach
 *     each cell from 0,0. As we can move only in forward or downward direction,
 *     There is only 1 way we can reach any cell in first row. Similarly only
 *     1 way to reach any cell in first column. So we initialize DP array with
 *     this. Then for cell 1,1 onwards, the total number of ways are number of
 *     ways to reach i-1,j cell + number of ways to reach i,j-1 cell. Finally
 *     we return the value at dp[m-1][n-1]. Time complexity is O(mn).
 */
int totalNumberOfWays(int m, int n) {
    int dp[m][n];

    for(int i=0; i<m; i++) {
        dp[i][0] = 1;
    }
    for(int j=0; j<n; j++) {
        dp[0][j] = 1;
    }

    for(int i=0; i<m; i++) {
        for(int j=0; j<n; j++) {
            dp[i][j] = dp[i-1][j] + dp[i][j-1];
        }
    }

    return dp[m-1][n-1];
}

/*
 * 16. Number of values to reach a score in game: Given a final score N and
 *     different possible scores we can achieve in 1 move, find the number of
 *     ways to reach the final score. e.g. N=40 and M={3,5,10} means we can
 *     achieve either a score of 3 or 5 or 10 in a move and we need to achieve
 *     the final score of 40.
 *
 *     This is exactly similar to coin change problem. It can be done in O(MN)
 *     where M is number of possible scores for a move and N is the final
 *     score needed. We maintain a DP array of size N+1, initialize dp[0]=1
 *     and then traverse the list of possible scores and starting from that
 *     index till N, we update the DP.
 */
int waysToWinGame(int N, int *M, int len) {
    int dp[N+1];
    dp[0] = 1;

    for(int i=0; i<len; i++) {
        for(int j=M[i]; j<=N; j++) {
            dp[j] = dp[j] + dp[j-M[i]];
        }
    }
    return dp[N+1];
}

/*
 * 17. 0-1 Knapsack Problem: Given a list of items with their value and weight
 *     and a weight limit, return the maximum value that we can achieve by
 *     selecting the items such that their total weight will be less than or
 *     equal to the given limit. We have 2 arrays of length n each. val[]
 *     contains the values of n elements and wt[] contains their weights.
 *     We are given W which is the weight limit.
 *
 *     We use a 2d DP array to solve this problem. The DP array is of size
 *     n+1 by W+1. DP[i][j] has the max value we can achieve by having i-1
 *     items with total weight of j. So our final answer will be in dp[n][W]
 *
 *     We initialize dp[0][j] and dp[i][0] with 0. Now we fill the dp for
 *     i from 1 to n and j from 1 to W. For each iteration, we check if wt[i]
 *     is greater than current value of weight which is j. If it is greater,
 *     then it means that we cannot include this element in our calculation
 *     for max value. So we just take the value of dp[i-1][j]. But if wt[i]
 *     is less than j, then we have two options. Either include this element
 *     or not include it. We take max of these values and store it.
 *     Time complexity is O(Wn).
 */
int knapsack(int *val, int *wt, int n, int W) {
    int dp[n+1][W+1];

    for(int i=0; i<=n; i++) {
        for(int j=0; j<=W; j++) {
            if(i==0 || j==0) {
                dp[i][j] = 0;
            } else {
                if(wt[i-1] > j) {
                    dp[i][j] = dp[i-1][j];
                } else {
                    dp[i][j] = max(dp[i-1][j], (val[i-1]+dp[i-1][j-wt[i-1]]));
                }
            }
        }
    }
    return dp[n][W];
}

/*
 * 18. Length of longest substring without repeating characters: Given a string
 *     return the length of longest substring which has all unique characters.
 *
 *     We use a hash array here to store the already visited characters. We
 *     store their most recent index in the hash array. We maintain a start
 *     and end iterators and a maxLen variable. Initiall, start and end are at
 *     0 and maxLen is 0. We also put 0th char in the hash array with idx=0.
 *     Now, for end = 1 to len of string, we check if the present char is
 *     present in the hash. If not, we add it to hash with its index and
 *     continue. If it is present in hash, then we check if the index in hash
 *     is in between start and end. If yes, then we update the maxLen and move
 *     start to end and continue. If not, then we just continue. In the end,
 *     we will have the required length in maxLen.
 *     Time complexity is O(n).
 */
int longestSubstringUnique(char *str, int len) {
    int hash[26] = {-1};

    int start=0, end=0, maxLen=0;
    hash[str[0]-'a'] = 0;

    for(end=1; end<len; end++) {
        if(hash[str[end]-'a'] == -1) {
            // Not present in hash. Add it to hash and continue
            hash[str[end]-'a'] = end;
        } else {
            // Present in hash. Check if it is between start and end.
            // If not, continue, else update the maxLen.
            int id = hash[str[end]-'a'];
            if(id >= start) {
                maxLen = max(maxLen, end-start);
                start = end;
            }
        }
    }
    return maxLen;
}

/*
 * 19. Egg and Floor Problem: Given n eggs and k floors, find the minimum
 *     number of trials required in worst case to find the last floor from
 *     which the dropped eggs does not break.
 *
 *     If we have only 1 egg and k floors, total number of trials required
 *     will be k in worst case (worst case when kth floor is safe to drop egg).
 *     We start with 1st floor and drop the egg. If it does not break, then we
 *     drop it from 2nd floor and so on. But now, if we have 2 eggs, then the
 *     number of trials can be reduced. Say we dropped our 1st egg from xth
 *     floor. There are two possibilities, the egg will break or not break.
 *     If the egg breaks, then we have only 1 remaining egg and we need to
 *     check floors from 1 to x. If the egg does not break, then we have 2
 *     eggs remaining and we need to check floors from x+1 to k. So say
 *     f(eggs, floors) is the function to get min number of trials to get
 *     the critical floor 'eggs' number of eggs and 'floors' number of floors.
 *     So, f(eggs, floors) = 1 + min(f(eggs-1, x-1), f(eggs, floors-x))
 *     Here, x is the xth floor we did our trial. Now, x is also unknown and
 *     to get most optimized value of x (the floor from which we should start
 *     our first trial), we should try with all values of x from 1 to floors
 *     and get the max of these values. So, for all x from 1 to floors,
 *     f(eggs, floors) = 1 + min(max(f(eggs-1, x-1), f(eggs, floors-x)))
 *
 *     What we are doing here is, for all x from 1 to floors, we drop the egg
 *     and calculate both possibilities for it (break or not break). We get
 *     the max of these two possibilites (for worst case) and store it. We
 *     do this for all the values of x. So, we will have a list of size floors.
 *     Now, we return the min of this value + 1 which is required answer.
 */
int eggDrop(int n, int k)
{
    // There are total n eggs and k floors
    
    // A 2D table where entery eggFloor[i][j] will represent minimum
    // number of trials needed for i eggs and j floors.
    int eggFloor[n+1][k+1];
    int res;
    int i, j, x;
 
    // For any number of eggs, we need ony 1 trial for 1 floor and
    // 0 trials for 0 floors
    for (i = 1; i <= n; i++)
    {
        eggFloor[i][1] = 1;
        eggFloor[i][0] = 0;
    }
 
    // If we have only 1 egg, then we need as many trials as many floors
    for (j = 1; j <= k; j++)
        eggFloor[1][j] = j;
 
    // Fill rest of the entries in table using optimal substructure
    // property
    for (i = 2; i <= n; i++)
    {
        for (j = 2; j <= k; j++)
        {
            eggFloor[i][j] = INT_MAX;
            // We traverse for each floor and get the max number of trials for
            // both the options of egg break and no break and add 1 to it. We
            // add 1 to include our current trial of dropping the egg. We maintain
            // a min of all these values for different x and finally put this value
            // in eggFloor[i][j].
            for (x = 1; x <= j; x++)
            {
                res = 1 + max(eggFloor[i-1][x-1], eggFloor[i][j-x]);
                if (res < eggFloor[i][j])
                    eggFloor[i][j] = res;
            }
        }
    }
 
    // eggFloor[n][k] holds the result
    return eggFloor[n][k];
}

/*
 * 20. Given a list of jobs with start time and end time, return maximum number
 *     of jobs that can be executed given the fact that at a time, only one
 *     job can be done.
 *
 *     We need to find a list or jobs that are not overlapping and also we need
 *     to include as many jobs as possible. We use greedy algorithm here. If we
 *     start selecting jobs with as small end time as possible, we can say that
 *     we will end up selecting maximum possible number of jobs. So, we sort
 *     the jobs according to ascending order of their end times. Then we select
 *     first job and for 2nd job onwards, we check if it overlaps with the
 *     previous job by comparing its start time with the end time of prev job.
 *     If it does not overlap, we include it in our list else, we dont include
 *     it. Thus we have max number of jobs we can do.
 *     Time Complexity is O(nLog(n)). We need only O(n) to get the list once
 *     jobs are sorted.
 */
int maxJobs(int *start, int *end, int len) {
    // Here we are given 2 seperate arrays for start and end times and total
    // number of jobs is given by len.

    // First we sort the jobs according to end times. Make sure we make same
    // operations in start array too so as to maintain the relative order
    // of start and end times.
    sort(end, start, len);

    // We maintain a count. We include the first job by default so we initialize
    // the count to 1. Now we traverse the start array from 1 to len and for each,
    // we check if it is greater than end[i-1]. If yes, we increment the counter.
    int count = 1;
    for(int j=1; j<len; j++) {
        if(start[j] > end[j-1]) {
            count++;
        }
    }
    return count;
}

/*
 * 21. Weighted Job list: Say we are given profit for each job above along with
 *     their start and end times and now, we need to return max profit we can
 *     make.
 *
 *     Here, we cannot use greedy algorithm as it is not necessary to do more
 *     jobs to earn more profit. So, we use DP here. First we sort the jobs
 *     according to their end times. Now, we maintain a dp array which stores
 *     the max profit we can make for each job as its index. We initialize
 *     dp[0] = profit[0] because for only 0th job, this is the max profit
 *     we can make. Now, for each job's start time, we try to get the last
 *     job which does not overlaps with it. If we find such job, then we
 *     get the profit as profit of curr job + profit of that prev job.
 *     This profit is the profit we can make by including the curr job in
 *     our list. There is another option of not including the current job
 *     in our list. For this, the profit is dp[i-1]. We store the max of
 *     these 2 values in dp[i]. We continue doing this for the entire list
 *     of jobs and finally, in dp[len], we have the answer.
 *     Time complexity is O(n^2) as for each job, we try to find a job
 *     previous of it which does not overlap with it.
 *     We can use binary search for this searching and improve the 
 *     complexity to O(nlogn) as sorting is still required.
 */
int maxWeightedJob(int *start, int *end, int *profit, int len) {
    // We define a structure to hold all these values for each job and
    // then define an array of these structs to hold all jobs.
    // struct jobs { int start, int end, int profit };
    struct jobs jobArr[len];
    for(int i=0; i<len; i++) {
        jobArr[i].start = start[i];
        jobArr[i].end = end[i];
        jobArr[i].profit = profit[i];
    }

    // Now we sort the list according to end times.
    sortEndTime(jobArr, len);

    // Define a dp array to store the max profits.
    int dp[len];
    dp[0] = jobArr[0].profit;
    int incProfit=0, excProfit=0;

    for(int i=1; i<len; i++) {
        // Find the latest prev job which does not overlap with this one
        for(int j=i-1; j>=0; j--) {
            if(jobArr[i].start > jobArr[j].end) {
                break;
            }
        }
        // Get the profit by including current job in the list
        if(j == -1) {
            incProfit = jobArr[i].profit;
        } else {
            incProfit = jobArr[i].profit + dp[j];
        }
        // Get the profit by excluding current job from the list
        excProfit = dp[i-1];
        // Update dp with max of these 2 values.
        dp[i] = max(incProfit, excProfit);
    }
    return dp[len-1];
}

/*
 * 22. Flood Fill: Given a 2d Matrix containing integers and given (x,y) point
 *     with a new value new_val, write a algorithm to fill the point (x,y) and
 *     all its neighbors and their neighbors with this new_val. This is similar
 *     to the paint application where when we fill the color, all the pixels
 *     of same previous color get filled with this new color.
 *
 *     The idea is to start with x,y and update it with new value and then
 *     recursively check for its 4 neighbors (x-1, y), (x+1, y), (x, y-1), (x, y+1)
 *     and if they had same previous color as (x,y), then update them too and
 *     continue the recursion for their neighbors.
 *
 *     We use BFS here. We start with (x,y) and enqueue it. Now we start a while
 *     loop till queue is not empty. In this, we first dequeue, update that point
 *     with new_val and then check for its 4 neighbors. If the neighbor has old
 *     value, enqueue that neighbor and continue.
 */
void floodFill(int **grid, int x_len, int y_len, int i, int j, int new_val) {
    queue *q;
    queue_node temp;
    temp.x = i;
    temp.y = j;
    enqueue(q, temp);

    while(!isEmpty(q)) {
        queue_node point = dequeue(q);
        int x = point.x;
        int y = point.y;
        int prev_val = grid[x][y];
        grid[x][y] = new_val;

        if(x-1 > 0 && grid[x-1][y] == prev_val) {
            point.x = x-1;
            point.y = y;
            enqueue(q, point);
        }
        if(x+1 < x_len && grid[x+1][y] == prev_val) {
            point.x = x+1;
            point.y = y;
            enqueue(q, point);
        }
        if(y-1 > 0 && grid[x][y-1] == prev_val) {
            point.x = x;
            point.y = y-1;
            enqueue(q, point);
        }
        if(y+1 < y_len && grid[x][y+1] == prev_val) {
            point.x = x;
            point.y = y+1;
            enqueue(q, point);
        }
    }
    return;
}

/*
 * 23. Replace O with X: Given a 2d matrix which has Os and Xs, we have to
 *     replace all those Os which are surrounded by Xs with Xs. An O is
 *     surrounded by an X if it has X on all its 4 neighbor positions.
 *     Adjascent Os can be considered as a group in which case, we have to
 *     have Xs on all positions adjascent to these Os.
 *
 *     We use similar approach as we used for floodFill. Our aim is to
 *     NOT replace all those Os which are on the edges of given matrix
 *     because these Os do not have Xs as all their neighbors because
 *     they are on edge (first and last row and column). Also, if there
 *     are any adjascent Os to these edge Os, they will also not be
 *     replaced. All other Os should be replaced. So, first we convert
 *     all the Os to some special char say '-'.
 *     And then for each - on the edge, we call the floodFill algo to
 *     replace it back with O. Then for rest of '-', we replace them
 *     with a X.
 */
void replaceO(char **grid, int x, int y) {
    // Replace all O with -
    for(int i=0; i<x; i++) {
        for(int j=0; j<y; j++) {
            if(grid[i][j] == 'O') {
                grid[i][j] = '-';
            }
        }
    }

    // Replace all edge - back with O
    for(int i=0; i<x; i++) {
        if(grid[i][0] == '-') {
            floodFill(grid, x, y, i, 0, 'O');
        }
    }
    for(int i=0; i<x; i++) {
        if(grid[i][y-1] == '-') {
            floodFill(grid, x, y, i, y-1, 'O');
        }
    }
    for(int j=0; i<y; j++) {
        if(grid[0][j] == '-') {
            floodFill(grid, x, y, 0, j, 'O');
        }
    }
    for(int j=0; i<y; j++) {
        if(grid[x-1][j] == '-') {
            floodFill(grid, x, y, x-1, j, 'O');
        }
    }

    // Replace remaining - with X
    for(int i=0; i<x; i++) {
        for(int j=0; j<y; j++) {
            if(grid[i][j] == '-') {
                grid[i][j] = 'X';
            }
        }
    }
}

/*
 * 24. Skyline Problem: Given an array of nodes where each node has 3 members
 *     lx, rx and height. Each node represents a building with lx = x coordinate
 *     of left edge, rx is x coordinate of right edge and height is the height of
 *     the building. We have to return a array of points where each point has
 *     members x and h where x is x coordinate and h is height of that point.
 *     This returned array should represent the skyline.
 *
 *     The idea here is to use the concept of Merge Sort. What we essentially
 *     want to do is first divide the given array of buildings into halves
 *     and then, we merge these in such a way that it represents a skyline.
 *
 *     The base case is when we have only one node in the building array. Say
 *     it is (x, y, h). Skyline representation for this would be {(x,h), (y,0)}
 *
 *     Now, say we have {(x1,h1), (x2,h2)} and {(x3,h3),(x4,h4)}
 *     we need to merge these two lists together. For this, just like merge
 *     method in merge sort, we compare (x1,h1) with (x3,h3) and if x1 < x3,
 *     then we add x1,h in our result array and increment list 1s iterator.
 *     Also in above, we get h = max(h1,h2). Initially h1 and h2 are 0. We
 *     update h1 or h2 whenever we increment that particular counter. Also
 *     we need to make sure that, while adding an element to our result,
 *     if the prev element also has same h or same x value, we dont add
 *     current element as it is redundant.
 *
 *     Time complexity is O(n*Log(n)).
 */
typedef struct bldg_node {
    int lx;
    int rx;
    int height;
}bldg_node;

typedef struct skyline_node {
    int x;
    int h;
}skyline_node;

skyline_node *result = (skyline_node*)malloc(sizeof(skyline_node)*100);
static int result_id=0;

void result_add(int x, int h) {
    if(result_id != 0 && (result[result_id-1]->x == x || 
                          result[result_id-1]->h == h)) {
        return;
    } else {
        result[result_id]->x = x;
        result[result_id]->h = h;
        result_id++;
        return;
    }
}

void mergeSkyline(skyline_node *resultl, skyline_node *resultr, int l, int r, skyline_node *result) {
//TODO

skyline_node* getSkyline(bldg_node *arr, int start, int end) {
    // Main will call this function with start=0 and end=len of arr
    // Base case
    if(start == end) {
        skyline_node *result = (skyline_node*)malloc(sizeof(skyline_node)*100);
        int result_id=0;
        result_add(result, result_id, arr[start]->lx, arr[start]->height);
        result_add(result, result_id+1, arr[start]->rx, 0);
        return result;
    } else {
        skyline_node *resultl, *resultr, *result;
        result = (skyline_node*)malloc(sizeof(skyline_node)*100);
        int mid = (start + end)/2;
        resultl = getSkyline(arr, start, mid);
        resultr = getSkyline(arr, mid+1, end);
        mergeSkyline(resultl, resultr, int l, int r, result);
    }
    return result;
}

