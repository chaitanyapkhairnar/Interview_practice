/*
 * This file contains leetcode questions asked in fb
 * This file has pseudo codes and it does not compile.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
 * 1. Word Ladder: You are given a start word and an end word. You have to
 *    return number of transformations to change start word to end word.
 *    Each transformation can change only 1 char in the word. You are given
 *    a list of words as dictionary. The condition is after each transformation
 *    whatever new word is formed, it should be in the dictionary. e.g.
 *    start word: hit, end word: cog, dictionary: {hot, dot, dog, lot, log, cog}
 *    Number of transformations required is 4 as below
 *    hit -> hot -> dot -> dog -> cog.
 *
 *    We use the concept of DFS here. We start with the start word and put it into
 *    the queue along with the change counter value which is 0 for start word.
 *    Then we enter a while loop until queue is not empty. Inside this, we pop the
 *    element from the queue and store this popped word in currWord variable and
 *    the change counter in currCounter variable. Then we start a for loop for the
 *    list of words in the dictionary. For each word in dictionary, we check if it
 *    is the adjascent word to our currWord. Here by adjascent we mean that both the
 *    words have only 1 char different. If yes, we push this word in the queue along
 *    with counter=1+currCounter. And we remove this word from the dictionary to
 *    make sure we do not consider this again. This is like marking the word visited.
 *    We do this for all the words in the dictionary. While doing this, if we encounter
 *    the end word, we return. Once we come out of this for loop, our queue has all the
 *    words that are 1 char different from our currWord. We are still inside while loop.
 *    So now, we again pop first element from the queue, put it in currWord and continue
 *    the process.
 *
 *    Time Complexity is O((n^2)*m). Here n is number of words in the dictionary and m
 *    is the length of word.
 */
bool isadjacent(char *a, char *b, int len) {
    int counter=0;
    for(int i=0; i<len; i++) {
        if(a[i] != b[i]) {
            counter++;
        }
    }
    if(counter == 1) {
        return true;
    }
    return false;
}

int shortestChainLen(char* start, char* target, char** D, int D_len)
{
    // Create a queue for BFS and insert 'start' as source vertex
    queue Q;
    struct QItem item;
    item.word = start;
    item.len = 1;
    Q_push(item);
    bool visited[D_len] = {false};
 
    // While queue is not empty
    while (!Q_empty())
    {
        // Take the front word
        struct QItem curr = Q_front();
        Q_pop();
 
        // Go through all words of dictionary
        for (int i = 0; i != D_len; i++)
        {
            // Process a dictionary word if it is adjacent to current
            // word (or vertex) of BFS
            char *temp = D[i];
            int len = strlen(curr.word);
            if (isadjacent(curr.word, temp, len))
            {
                // Add the dictionary word to Q
                item.word = temp;
                item.len = curr.len + 1;
                Q.push(item);
 
                // Remove from dictionary so that this word is not
                // processed again. mark visited
                visited[i] = true;
 
                // If we reached target
                if (temp == target) {
                    return item.len;
                }
            }
        }
    }
    return 0;
}

/*
 * 2. Decode Ways: Given a string containing integer digits and given a mapping
 *    such that 1 = 'a', 2 = 'b', ..., 26 = 'z', find the number of possible
 *    decodings done with the given string.
 *
 *    We use dynamic programming here. We define a array of size n+1 where n is
 *    length of given string. This array stores the number of possible
 *    decodings at each of its index. We have to fill this array and return nth
 *    index. We take the length as n+1 because we want to start with 1st index
 *    of given string. We initialize arr[0]=1 and arr[1]=1 as if we have a 0 or
 *    1 integer only, then there is only 1 way of decoding. Now when we have 2
 *    or more digit integer, then there can be multiple ways of decoding for e.g.
 *    12 can mean 'ab' as well as 'l'. So for i=2 to len of given string, the
 *    total number of ways will be total number of ways at i-1. And then we
 *    also check if i-2 was 1 or 2 and i-1 was < 7. If yes, then i-2, i-1 form
 *    a valid 2 digit number which can be interpreted as some alphabet. So,
 *    if this condition is true, we add total number of ways at i-2 also to our
 *    count. Finally we return arr[n].
 *
 *    Time complexity is O(n) where n is length of given string.
 */
int decode_ways(char *str, int len) {
    int arr[len+1];
    arr[0]=1;
    arr[1]=1;

    for(int i=2; i<=len; i++) {
        arr[i] = 0;
        int count;
        if(str[i-1] != '0') {
            count = arr[i-1];
        }
        if(str[i-2] == '1' || str[i-2] == '2' && str[i-1] < '7') {
            count = count + arr[i-2];
        }
        arr[i] = count;
    }
    return arr[n];
}

/*
 * 3. 3Sum: Given a array, return a list of unique triplets whose sum equals 0.
 *
 *    We do this in O(n^2). We first sort the array. Then we start a for loop
 *    from 0 to n. For each of this iteration, we get l=i+1 and r=len-1. Then
 *    we check the sum of arr[i]+arr[l]+arr[r]. If it is zer0, we print the
 *    elements. If it is >0 then we move r--, If it is <0, then we move l++.
 *
 *    As each element is being visited for each element in the array,
 *    Time complexity is O(n^2).
 */
list* 3Sum(int *arr, int len) {
    list *head = NULL;
    
    // Sort the array
    sort(arr, len);

    // We loop till len-2 because in last case, i will be at index len-2,
    // l will be at len-1 and r is also at len-1
    for(int i=0; i<len-1; i++) {
        int l=i+1;
        int r=len-1;
        while(l<r) {
            if(arr[i]+arr[l]+arr[r] == 0) {
                list_add(head, arr[i], arr[l], arr[r]);
                l++;
                r--;
            }
            if(arr[i]+arr[l]+arr[r] < 0) {
                l++;
            } else {
                r--;
            }
        }
    }
    return head;
}

/*
 * 4. Continuous subarray sum: Given a array, find the subarray whose sum equal
 *    given value.
 *
 *    We initialize start variable to 0 and currSum to arr[0]. Then we start a
 *    for loop from 1 to len of array. Inside this for loop, first we check if
 *    currSum > givenSum. While this is true and start is < i, we update
 *    currSum = currSum - arr[start] and then move start++. If currSum ==
 *    givenSum, then we print the subarray from start to i and return. Finally,
 *    we add the current element in currSum and end the for loop so i increments
 *    for next iteration.
 *
 *    Another method is to maintain a hash array which stores the sum of subarray
 *    till the current index. We initialize the hash[0]=arr[0]. Now for i=1 to len,
 *    we check if givenSum-arr[i] is present in the array. If yes, we have subarray
 *    from index of hash which has givenSum-arr[i] value to index i. If not, we
 *    update currSum and store it in hash and continue.
 *
 *    Time complexity is O(n) for both. The first approach does not handle -ve
 *    cases while second one does handle.
 */
void subarraySum(int *arr, int len, int sum) {
    int start=0;
    int currSum=arr[0];

    for(int i=1; i<len; i++) {
        while(currSum > sum && start < i-1) {
            currSum = currSum-arr[start];
            start++;
        }

        if(currSum == sum) {
            printf("Subarray from index %d to %d\n", start, i);
            return;
        }

        if(i < len) {
            currSum = currSum + arr[i];
        }
    }
    printf("No subarray found.\n");
}

/*
 * 5. Validate if the tree is BST.
 *
 *    We maintain min and max integer variables. Initially, both are set to -1.
 *    We recursively call the function to validate the tree with root node and min
 *    and max values. If root is null, return true. Then we check if min and max
 *    both are -1. If yes, this is the root node case. So recursively call for
 *    root->left with max updated to root->val and then for root->right with min
 *    updated to root->val. If both returned true then return true else false.
 *    If both min and max are not -1, then we check if root->val lies between
 *    min and max values. If not, return false. If yes, then we do above 2
 *    recursive calls. The idea is to check if each node value lies within the
 *    range of min and max and we update min and max depending on the parent node
 *    value.
 *
 *    Time complexity is O(number of nodes in tree).
 */

/*
 * 6. Clone a given Graph.
 *
 *    We use BFS/DFS here. We define a hashmap to mark the nodes as visited.
 *    We start with the first node of given graph and create a copy node of this.
 *    Then we push the original node into queue and also mark this node as visited
 *    by putting copy_node pointer in the hashmap at original_node pointer index.
 *    i.e. hash[original_node] = copy_node.
 *    Now we start a while queue not empty loop. Inside this, we pop the element
 *    from the queue (which is a original node) and then start a for loop for
 *    all the neighbors for this popped element. We get the copy node of this
 *    popped element from the hash (say it is parent_copy_node).
 *    Now for each neighbor node of this popped node, we check if it is present
 *    in the hash. If yes, we do nothing. If no,
 *    then we create a copy node of this neighbor node and insert this new
 *    copy node in the neighbor list of parent_copy_node. Also we insert it into
 *    the hash. Finally we enqueue the original neighbor node into queue and
 *    continue for next neighbor nodes. This way we traverse the entire original
 *    graph and while traversing keep creating the clone of it.
 *
 *    Time complexity is same as it is for BFS of graph which is O(V+E)
 */

/*
 * 7. Minimum swaps required to make 2 sequences in strictly increasing order.
 *    We are given two arrays of same length. We can swap only the elements from
 *    both the arrays at same index. Return the min number of swaps required.
 *
 *    We use dynamic programming here. There are following possibilities of swapping.
 *    1. if A[i] > A[i-1] && B[i] > B[i-1], then for ith position, we can either not
 *       swap, or we swap both A[i], B[i] and A[i-1], B[i-1] to maintain the order.
 *    2. if A[i] > B[i-1] && B[i] > A[i-1], then for ith position, we can either swap
 *       A[i],B[i] or we can let remain these and swap A[i-1],B[i-1].
 *
 *    We have to consider all these possibilities for each index i and keep updating
 *    the min values. We use 4 integer variables n1 and n2 to maintain the count of
 *    no_swap operations and s1 and s2 to maintain count of swap operations. n1 and
 *    s1 are for previous and s1 and s2 are for current index. We initialize n1=0 and
 *    s1=1 for index 0 as if we had only 1 element in both the arrays, we can either
 *    leave the elements as it is (n1=0) or swap the elements (s1=1). Now, we iterate
 *    for i=1 to len. For each i, we check the above possibilites and update n2 and s2
 *    and then in the end of each iteration, we make n1=n2 and s1=s2 as these will be
 *    previous values for next i. In the end, the min value of n1,s1 will be our answer.
 *
 *    Time complexity is O(n) and no constant space required. (only 4 int variables.)
 */

int minSwapsStrictlyIncreasing(int *arr1, int *arr2, int len) {
    int n1=0, s1=1, n2=INT_MAX, s2=INT_MAX;

    for(int i=1; i<len; i++) {
        if(arr1[i]>arr1[i-1] && arr2[i] > arr2[i-1]) {
            // Two options.
            // No swap
            n2 = min(n1, n2);

            // Swap both prev as well as curr. So add 1 to the swap val of prev
            s2 = min(s2, s1+1);
        }

        if(arr1[i]>arr2[i-1] && arr2[i]>arr1[i-1]) {
            // Two options.
            // swap only current. So get value of no-swap+1 (n1+1) of prev in our s2
            s2 = min(s2, n1+1);

            // dont swap current, but swap only previous.
            n2 = min(n2, s1);
        }

        // update n1 and n2 for next iteration
        n1 = n2;
        s1 = s2;
    }

    // Finally return the min of n1,s1
    return min(n1, s1);
}


/*
 * 8. Design a datastructure that supports addWord(word) and 
 * bool searchWord(word). The searchWord returns true or false depending on
 * the word found or not. The searchWord can take a string which has '.' which
 * means this particular char is a wildcard entry and it can match to anything.
 * e.g. "b.d" can mean "bad", "bed", "bod" etc.
 *
 * Obviously, we use trie data structure here. Trie node will have a char* member
 * which will be NULL if the node is not the end of word and it will contain the
 * entire word if the node is end of word. And it will have a array of pointers
 * of length 26 to represent children.
 * addWord function will traverse from the root of trie and create children for each
 * char in the given word and finally copy the word in the char* member of last node.
 * searchWord will be a recursive function. If the present char is not a '.', then
 * node = node->children[present char] and recursively call the function with this
 * updated node. If the present char is a '.', then for each child of present node,
 * recursively call the function with node = node->children[i].
 */

/*
 * 9. Implement pow(x,n) where it returns x^n. n is huge and can be -ve
 *
 *    The simple straighforward idea is to keep multiplying x n times. But the
 *    catch here to consider all corner cases. If n is 0, we return 1. If n is 1
 *    we return x. If n is -ve, we have to divide 1 by x n times. We have to make
 *    sure we use long float to store the decimal value which can be large enough.
 *
 *    One O(n) algorithm is to first consider cases of n = 0 and 1. Then if n < 0
 *    put x = 1/x and n = -n. Initialize result=1. Then we start a loop for i=0
 *    to n and do result=result*x.
 *
 *    Another fast approach in O(log(n)) is to use the fact that if we have x^n,
 *    we can get x^2n by just doing (x^n)^2. We recursively call the function for
 *    n/2. Base case is if n==0, return 1. We store the result in variable half.
 *    After returning from the recursive call, we check if n%2 is 0 then
 *    result = half*half. Else, result = half*half*x. Return the result.
 */
double pow(double x, int n) {
    long long int N = n;
    if(N < 0) {
        N = -N;
        x = 1/x;
    }
    return rec_pow(x, N);
}

double rec_pow(double x, long long int n) {
    if(n == 0) {
        return 1;
    }
    double half = rec_pow(x, n/2);
    if(n%2 == 0) {
        return half*half;
    } else {
        return half*half*x;
    }
}

/*
 * 10. Simplify paths: Given a string which has path as we would give to a cd
 *     command, return the result as cd command would give.
 *
 *     We use stack for this. O(n) solution is already described in another doc.
 *     Refer that for the answer.
 */

/*
 * 11. Multiple strings: Given two strings that represent numbers, return a
 *     string that has the multiplication of both numbers.
 *
 *     This question already asked. Most probably it wont be asked again.
 *     Time complexity of O(mn) where m and n are lengths of given strings
 *     can be implemented.
 */

/*
 * 12. Word search: Given a 2d matrix with chars in it and given a string,
 *     return true is the string is found in the matrix. The word can be
 *     searched only in horizontal and vertical direction. You can go front
 *     and back and top and down, but we cannot use same visited char again.
 *
 *     We use backtracking and DFS to solve this problem. In one function,
 *     we start two for loops for row and column and call the recursive
 *     function with present i and j indices, 2d matrix, string, start index
 *     of string (0 initially). This recursive function first checks if
 *     the start index of string == strlen. If yes, then return true. Then it
 *     checks if i and j are valid and matrix[i][j] == string[start]. If not,
 *     return false. If present index in matrix has present char in string,
 *     then we start the backtracking algo. We mark the present char in
 *     matrix as visited. Then we recursively call the function for i, j+1
 *     and start index of string + 1. If this returns false, then we call
 *     for i,j-1. If this returns false, we call for i+1,j If this returns
 *     false then we call for i-1,j. If this also returns false, then we
 *     backtrack by unmarking the present char in matrix as visited and return
 *     false.
 *
 *     Time complexity: TODO
 */
bool checkWord(char **matrix, int i, int j, int row_len, int column_len,
               char **string, int str_start, int string_len) {
    // Check for validity of i and j
    if(i < 0 || i > row_len || j < 0 || j > column_len) {
        return false;
    }
    // Check if current char is already visited
    if(matrix[i][j] == '*') {
        return false;
    }
    // Check if string already found.
    if(str_start == string_len) {
        return true;
    }

    // Now check if current char in matrix matches curr char in string
    char currC = matrix[i][j];
    if(currC != string[str_start]) {
        return false;
    }

    // Now mark the current char as visited in matrix and try all options
    matrix[i][j] = '*';
    bool res = false;

    res = checkWord(matrix, i, j+1, row_len, column_len, string, str_start+1,
                    string_len);
    if(!res) {
        res = checkWord(matrix, i, j-1, row_len, column_len, string, str_start+1,
                        string_len);
    }
    if(!res) {
        res = checkWord(matrix, i+1, j, row_len, column_len, string, str_start+1,
                        string_len);
    }
    if(!res) {
        res = checkWord(matrix, i-1, j, row_len, column_len, string, str_start+1,
                        string_len);
    }

    if(!res) {
        // No solution from this index. So backtrack and return
        matrix[i][j] = currC;
        return false;
    } else {
        return true;
    }
}

// Function to call checkWord for each and every index in matrix
bool findWord(char **matrix, int row_len, int column_len, char **string,
              int string_len) {
    // Check for sanity
    if(!matrix || !string || string_len == 0) {
        return false;
    }
    for(int i=0; i<row_len; i++) {
        for(int j=0; j<column_len; j++) {
            bool res = false;
            res = checkWord(matrix, i, j, row_len, column_len, string,
                            0, string_len);
            if(res) {
                return true;
            }
        }
    }
    return false;
}

/*
 * 13. Lowest common ancestor
 *     Solution in another document.
 */

/*
 * 14. Course Schedule: Given n number of courses and a list of dependencies
 *     of each course, give a list of courses in the order they should be taken
 *     e.g. 4 [[1,0],[2,0],[3,1],[3,2]] means there are 4 courses to be taken
 *     such that course 0 is prerequisite for course 1 and 2. 1 is prereq for 3
 *     and 2 is also prereq for 3. So the order of courses should be 0,1,2,3
 *
 *     For these type of dependency related questions, we use topological
 *     sorting. First we create a directed graph with edges from dependent
 *     course to the independent course. Then we do topological sorting on this
 *     graph. If topological sorting does not exists, then answer is not
 *     possible. If topological sorting exists, then this is the answer.
 *
 *     In our example, the graph formed will be as below. All edges are directed
 *     and point in downward direction.
 *                    3
 *                  /   \
 *                 1     2
 *                  \   /
 *                    0
 *     Now, we do topological sorting of this graph. Topological sorting means
 *     for every directed vertex say from a to b, always print b first and then a.
 *     So in above graph, 0 should always come before 1 and 2 and similarly, 1 and 2
 *     should always come before 3. So topological sort will be 0,1,2,3 or 0,2,1,3.
 *     And this is the answer. Any scheduling task where there is dependency
 *     between the tasks is done by this algo.
 *
 *     When we represent the given list as graph, we have to make sure we use
 *     adjacency list representation of graph and not the 2d matrix representation
 *     as Topological Sorting requires adjacency list representation.
 *
 *     Time Complexity is same as DFS. O(V+E)
 *
 *     Look how to implement Topological Sorting in geeksforgeeks.
 */

/*
 * 15. Maximal Square: Given a 2d matrix of 1s and 0s, find the largest square
 *     with all 1s and return its area.
 *
 *     We use Dynamic Programming here. We take another 2d integer array of same
 *     dimentions as given array. This array will store the size of biggest
 *     square that can be formed such that the value at arr[i][j] represents the
 *     size of square that can be formed considering the cell i,j in the given
 *     matrix is the bottom rightmost cell of this square being formed. We
 *     initialize the arr to all 0s. The we copy the values of given 2d array
 *     into arr for 1st row and 1st column. This is for initialization. Now, we
 *     start a for loop for i=1 to row_len and j=1 to column_len. For each cell,
 *     we get min value of the 3 adjascent cells to it which are i-1,j i-1,j-1
 *     and i,j-1. Then we add 1 to this min val and we update this value to i,j
 *     cell of arr. This way, we build the full array. We also keep track of max
 *     value. In the end, this is the max length of square that can be formed.
 *     Area will be max_val^2.
 *
 *     Time complexity is O(mn) and extra space requirement is also O(mn).
 */

/*
 * 16. Account Merge: Given a list of strings where each string has name as
 *     first member and then a list of emails. Different accounts may have
 *     same name. We have to look into emails and merge the accounts having
 *     atleast 1 common email.
 *     
 *     accounts = [["John", "johnsmith@mail.com", "john00@mail.com"], 
 *                 ["John", "johnnybravo@mail.com"], 
 *                 ["John", "johnsmith@mail.com", "john_newyork@mail.com"], 
 *                 ["Mary", "mary@mail.com"]]
 *     Output: [["John", 'john00@mail.com', 'john_newyork@mail.com',
 *               'johnsmith@mail.com'],
 *               ["John", "johnnybravo@mail.com"], ["Mary", "mary@mail.com"]]
 *
 *     We use concept of graph here. We use hash to store names against the
 *     email addresses. Then we create a graph such that there is nondirected
 *     edge between the emails belonging to same account. Once this is done
 *     for all the accounts, then we find the connected components and create
 *     a list of these and add name by finding it from hash and return the list.
 *
 *     Time complexity is O(summation of (alog(a)))
 */

/*
 * 17. Largest plus sign: Given a 2D matrix containing 1s and 0s, return the size
 *     of largest plus sign that is being formed in the array with 1s. The size 
 *     here is defined as the length of 1 arm of plus sign + 1. e.g.
 *     0 0 1 0 0
 *     0 0 1 0 0
 *     1 1 1 1 1
 *     0 0 1 0 0
 *     0 0 1 0 0
 *     In this case, the size of plus formed is 3 as [2,2] is the center of plus
 *     and its arm length is 2, so size is 2+1=3.
 *
 *     We use dynamic programming here. For each element in the given matrix,
 *     we need to check its left, right, top and bottom sides. The plus will be
 *     formed of size min(left, right, top, bottom). Here, left, right, top and
 *     bottom have the length of consecutive 1s in respective directions. To get
 *     these, we use DP.
 *
 *     We define a 2D DP matrix. The for each row from 0 to n and for each
 *     column from 0 to n, we calculate number of 1s to the left of present
 *     index and put these values in DP matrix.
 *
 *     Then for each row 0 to n and column n to 0, we calculate number of 1s
 *     to the right of present index and then update DP matrix with the min
 *     value of DP's current value and this new calculated value.
 *
 *     Similarly we do for top and bottom once for row 0 to n and once for
 *     row n to 0. Finally, the max value present in the DP matrix is our
 *     answer.
 *
 *     Time complexity is O(mn) and Space Complexity is also O(mn).
 */
int maxPlusSize(int **grid, int row_len, int column_len) {
    int DP[row][column];
    int max = 0;
    /* Traverse the grid to get number of 1s in left and right direction
     * of curr elem.
     */
    for(int r=0; r<row_len; r++) {
        // Get the length of 1s in left of current cell
        for(int c=0; c<column_len; c++) {
            if(r==0 && c==0) {
                DP[r][c] = grid[r][c];
            } else {
                if(grid[r][c] == 1) {
                    DP[r][c] = 1 + DP[r][c-1];
                } else {
                    DP[r][c] = 0;
                }
            }
            if(DP[r][c] > max) {
                max = DP[r][c];
            }
        }

        // Get the length of 1s in right of current cell.
        // Update DP only with min val.
        for(int c=column_len-1; c>=0; c--) {
            if(r==row_len-1 && c==column_len-1) {
                DP[r][c] = min(DP[r][c], grid[r][c]);
            } else {
                if(grid[r][c] == 1) {
                    DP[r][c] = min(DP[r][c+1]+1, DP[r][c]);
                } else {
                    DP[r][c] = 0;
                }
            }
            if(DP[r][c] > max) {
                max = DP[r][c];
            }
        }
    }
    
    /* Now, traverse the grid to get number of 1s top and bottom direction
     * of curr elem.
     */
    for(int c=0; c<column_len; c++) {
        // Look for 1s in top direction
        for(int r=0; r<row_len; r++) {
            if(c==0 && r==0) {
                DP[r][c] = grid[r][c];
            } else {
                if(grid[r][c] == 1) {
                    DP[r][c] = min(DP[r][c], DP[r-1][c]+1);
                } else {
                    DP[r][c] = 0;
                }
            }
            if(DP[r][c] > max) {
                max = DP[r][c];
            }
        }

        // Look for 1s in bottom direction
        for(int r=row_len-1; r>=0; r--) {
            if(c==column_len-1 && r==row_len-1) {
                DP[r][c] = grid[r][c];
            } else {
                if(grid[r][c] == 1) {
                    DP[r][c] = min(DP[r][c], Dp[r+1][c]+1);
                } else {
                    DP[r][c] = 0;
                }
            }
            if(DP[r][c] > max) {
                max = DP[r][c];
            }
        }
    }

    return max;
}

/* 18.
 * Given a 2D matrix with 1s and 0s, find the number of rectangles formed
 * within this matrix such that they have 1s on their corners. The rectangles
 * can have 1s inside them too, but they MUST have 1s on all 4 corners. e.g.
 * 1 0 0 1 0
 * 0 1 0 1 0
 * 1 0 0 1 0
 * 0 1 0 1 0
 * In this case, 2 rectangles are formed. {0,0; 0,3; 2,0; 2,3} and
 * {1,1; 1,3; 3,1 3,3}.
 *
 * Our approach is to traverse all rows and for each row i, start another loop
 * for rest rows j. Now for these two rows i and j, we traverse columns and
 * get the number of pairs of 1s such that matrix[i][c] and matrix[j][c]
 * contain 1s. Once we have these number of pairs, we calculate the number of
 * rectangles using formula n*(n-1)/2 where n is number of pairs of 1s.
 *
 * Time complexity is O(row^2*column). No extra space required.
 */
int cornerRectangles(int **grid, int row_len, int column_len) {
    int one_pairs=0;
    int total_rectangles=0;

    for(int i=0; i<row_len-1; i++) {
        for(int j=i+1; j<row_len; j++) {
            for(int c=0; c<column_len; c++) {
                if(grid[i][c] == 1 && grid[j][c] == 1) {
                    one_pairs++;
                }
            }
            total_rectangles += (one_pairs*(one_pairs-1))/2;
            one_pairs = 0;
        }
    }
    return total_rectangles;
}

/*
 * 19. Find friends of appropriate ages: Given a list of ages of people and
 *     below conditions to make a friend request, return the number of friend
 *     requests made.
 *     Person A makes a friend request to B only if
 *     1. age[B] <= 0.5 * age[A] + 7
 *     2. age[B] > age[A]
 *     3. age[B] > 100 && age[A] < 100
 *
 *     One straightforward approach is O(n^2) where for each person, we check
 *     all others and increase the count if they meet above conditions.
 *
 *     Another approach is O(nlog(n)). We sort the age list first.
 *
 *     Then we initialize the count to 0 and start with 1st index as 0th index
 *     cannot make any friend request as there is no person with smaller age.
 *     For each index, we calculate the lower bound age using condition 1
 *     higher bound age is present index age. Then we use binary search to find
 *     the lower bound age index in array and calculate the distance between that
 *     index and present index. This is the count of requests for current index.
 *     We continue doing this till the end of array and we have the answer.
 *     We can use hash to store the indices of ages so that we can find lower
 *     bound age index in O(1).
 *     Time complexity is O(nlog(n)).
 */

/*
 * 20. Bipartite Graph: Given a graph return true if it is bipartite. A graph
 *     is bipartite all its nodes can be divided into two seperate subsets such
 *     that for each edge present in the graph, the two nodes connected by the
 *     edge should be present in 2 different subsets. e.g.
 *     1-------2
 *     |       |
 *     3-------4
 *     This graph is bipartite as we can divide the nodes into 2 subsets as below
 *     (1,4), (2,3). So that each edge connects nodes in different subsets.
 *
 *     We use a hashmap here to store the node's subset. We need to divide the
 *     nodes into 2 subsets, so our node can be in subset 0 or 1. So our hash
 *     will have values 0 or 1 for each node. Also we initialize hash to -1
 *     as we will use the same hash to mark nodes as visited too.
 *
 *     We do some traversal of graph. Say we do DFS here. We do DFS for each
 *     node as to include disconnected parts of graph too. Initially, for
 *     first node, we mark as say 0 in hash. Then we mark all its neighbors
 *     as 1 and put them in stack. Then we pop an element from stack and
 *     mark all its neighbors as !(this nodes set) and put them in stack.
 *     We also keep checking if we encounter a neighbor who is already
 *     marked. If it is marked same as our present node, then return false.
 *
 *     Time complexity is O(N+E) where N is nodes and E is edges. We traverse
 *     each node once and for each node, we traverse all its edges too.
 *     Space is O(N) for hash.
 */
bool isBipartite(int **graph, int nodes) {
    // We are using 2d representation of graph here. nodes are number of nodes.

    // Hash to store the sets of nodes
    int hash[nodes] = {-1};
    // Stack for traversing
    Stack st=NULL;

    // We start a for loop to traverse each node in graph.
    for(int i=0; i<nodes; i++) {
        if(hash[i] == -1) {
            // Mark first node as 0
            hash[i] = 0;
            // Push it into stack
            stack_push(st, i);

            // Start a while loop to traverse all neighbors
            while(!isEmpty(st)) {
                int curr = stack_pop(st);
                // Traverse for all neighbors of curr
                for(int j=0; j<nodes; j++) {
                    if(graph[curr][j] != 0) {
                        if(hash[j] == -1) {
                            // Mark neighbor in another set than parent
                            hash[j] = !hash[curr];
                            stack_push(st, j);
                        } else {
                            if(hash[j] == hash[curr]) {
                                // Neighbor is in same set as parent.
                                return false;
                            }
                        }
                    }
                }
            }
        }
    }
    return true;
}

/*
 * 21. Continuous subarray sum: Given an array of Integers and a number K,
 *     return true if there exists a subarray with sum equal to multiple of K.
 *     So sum can be K or 2K or 3K and so on.
 *
 *     We use hashmap and running sum here. We traverse the array from 0 to len
 *     While traversing, we keep on getting the running sum of elements and
 *     we do a modulo K on this sum and put it in hash if it is not already
 *     present. Here the key is this sum%K and value is the index. If the
 *     element is already present in the hash, then it means there exists a
 *     subarray from index hash[key]+1 to current index which has sum
 *     multiple of K.
 *
 *     This is very similar to the problem of finding the subarray with the
 *     given sum. There, we store the sum in hash with the index and for each
 *     new sum, we check if sum-given value is present in the hash.
 *
 *     Here as we need to check for all multiples of K, we use % operator.
 *
 *     Time complexity is O(n) and Space is also O(n)
 */
subarrayWithMultipleSum(int *arr, int len, int k) {
    int hash[len] = {-1};
    int sum = 0;

    for(int i=0; i<len; i++) {
        sum = sum + arr[i];
        int val = sum%k;
        if(hash[val] == -1) {
            hash[val] = i;
        } else {
            // subarray exists.
            return true;
            // If we want indices of subarray, they are (hash[val]+1 to i).
        }
    }
    return false;
}

/*
 * 22. Brick Wall: Given a list of arrays where each array represents a row of
 *     brick wall and each element within the array represents the length of the
 *     bricks, we have to draw a vertical line on this wall such that this line
 *     crosses minimum bricks. If the line passes through the edge, then it is
 *     not considered as crossing the brick. e.g.
 *     a1 = [1, 2, 3]
 *     a2 = [2, 4]
 *     a3 = [1, 1, 1, 3]
 *     a4 = [1, 1, 2, 2]
 *
 *     This means the wall has 4 rows of bricks, row a1 has 3 bricks of lengths
 *     1, 2 and 3. similarly for other rows.
 *
 *     The idea we use here is of running sum and hash. We get running sum of 
 *     each arrays first. Then we traverse each of the arrays one by one and
 *     increment its count in hash. (hash[val]++). Finally, we get the max val
 *     in the hash - total number of rows and this is the answer. Basically,
 *     when we take running sum here, when multiple rows have same cumulative
 *     sum same at a particula index, that means that there is a edge there
 *     on all these rows. So we get max number of edges at a particular
 *     index to minimize the bricks crossed.
 *
 *     Time complexity is O(n) where n is total number of bricks. Space
 *     required is O(m) where m is width of wall.
 */
int minBricksCrossed(int **wall, int rows) {
    // We take 2d array as argument. Each row can have different length columns
    // We can put a -1 at a particular index to denote the end of that row.

    int width=0;

    // Calculate running sum for each rows and update the wall array
    for(int i=0; i<rows; i++) {
        int j=0;
        int sum=0;
        while(wall[i][j] != -1) {
            sum = sum + wall[i][j];
            wall[i][j] = sum;
            j++;
            if(sum > width) {
                width = sum;
            }
        }
    }

    // hash array
    int hash[width] = {0};
    int max = 0;
    // Now traverse each row and update count in hash
    for(int i=0; i<rows; i++) {
        int j=0;
        while(wall[i][j] != -1) {
            hash[wall[i][j]]++;
            if(max < hash[wall[i][j]]) {
                max = hash[wall[i][j]];
            }
            j++;
        }
    }

    // We have max containing max number of edges at any possible index
    // so we return the min bricks crossed count
    return rows - max;
}

/*
 * 23. Graph valid tree: Given a graph with undirected edges, return true if
 *     this graph is a valid tree.
 *
 *     Any graph is a valid tree if it does not have cycles in it. So all we
 *     need to find is if there are any cycles present in the given graph.
 *     The best method to do this is using union find algorithm. Please go
 *     through this algorithm for implementation details.
 */

/*
 * 24. Given a array of 1s and 0s, find the number of subarrays which have
 *     equal number of 0s and 1s in them. e.g.
 *     arr = [0 0 1 1 0 1 0 0]
 *     total number of subarrays = 10
 *     0011, 001101, 01, 0110, 011010, 110100, 10, 1010, 01, 10
 *
 *     The idea here is to use DP and running sum. We use a variable count.
 *     We traverse through the array and if arr[i] == 0, then count = count-1
 *     and if arr[i] == 1 then count = count+1. We store these values of count
 *     in another array or we can overwrite given array too. So for above e.g.
 *     we have, res = [-1 -2 -1 0 -1 0 -1 -2].
 *     Now whenever we have a 0 in this matrix, it means we have equal no of
 *     1s and 0s in the subarray starting from first and ending at index which
 *     has 0 value in our res array. Also in our res array, when we encounter
 *     same numbers, that means the subarray in between indices on which we
 *     encountered same numbers have equal count of 1s and 0s. So, in our
 *     res array, all possible subarrays between indices that have -1 have
 *     equal number of 1s and 0s. Similarly for 0 and -2.
 *     Now we need to find the total count of such subarrays. From our res
 *     array, the count of repeating numbers are as below
 *      0 --- 2
 *     -1 --- 4
 *     -2 --- 2
 *
 *     The count will be (n-1)! for all counts + number of 0s.
 *     count = (2-1)! + (4-1)! + (2-1)! + 2 = 10
 *
 *     Now if we are asked to return the length of longest subarray that has
 *     equal number of 0s and 1s, then we use a hash instead of res array.
 *     We traverse the given arr, get the count as above and if this count
 *     is not present in the hash, we add it to hash along with the index.
 *     If the count is present in the hash, then we get the diff of present
 *     index and the index present in the hash and update it to max variable
 *     if it is greater than max. Thus in the end, we get the value in max.
 */
int getMaxSubarray0and1(int *arr, int len) {
    int max = 0;
    // 2*len because our count will be in range -len to +len. So whenever we
    // add the value to hash, we simply do val+len and add this value to hash
    // as index of hash array cannot be -ve. When we get the element from hash,
    // we do element-len and that is the actual element.
    int hash[2*len] = {-1};
    int count = 0;

    for(int i=0; i<len; i++) {
        if(arr[i] == 0) {
            count = count - 1;
        } else {
            count = count + 1;
        }
        
        if(hash[count+len] == -1) {
            hash[count+len] = i;
        } else {
            if(i - hash[count+len] > max) {
                max = i - hash[count+len];
            }
        }
    }
    return max;
}

/*
 * 25. Random Index: Given an array which might have duplicates, and a target
 *     value, return index of the array containing this target value randomly
 *     with equal probability. e.g. arr = [1 2 3 3 3 4] and k=3 should return
 *     either 2 or 3 or 4 as index value with equal probability which means
 *     if we call same function with same array and k multiple times, each time
 *     we should get a random index number between 2 and 4.
 *
 *     We can do this in O(n). We first traverse the array and get the count
 *     of number of times k value is present in our array. If it is present
 *     only 1s, then there is no duplicate and directly return the index.
 *     If it is present for more than 1 time, then we generate a random
 *     number using time as seed in the range 0 to count. Then we again
 *     traverse the array and if we encounter the value k, we decrement this
 *     random number by 1. If this number becomes 0, we return that particular
 *     index.
 */
int randomIndex(int *arr, int len, int k) {
    int count=0;
    int latest_index=-1;
    for(int i=0; i<len; i++) {
        if(arr[i] == k) {
            count++;
            latest_index = i;
        }
    }
    if(count == 0) {
        return -1;
    } else if(count == 1) {
        return latest_index;
    }

    int random = rand()%count;

    for(int i=0; i<len; i++) {
        if(arr[i] == k) {
            if(random == 0) {
                return i;
            } else {
                random--;
            }
        }
    }
}

/*
 * 26. Given a binary tree, print it in vertical order. e.g.
 *             3
 *         9       20
 *             15      7
 *     
 *     Output will be:
 *     9
 *     3 15
 *     20
 *     7
 *
 *     We use hash and linked list concepts here. We use a variable offset.
 *     We start from root and offset is 0 initially. We put the value of root
 *     in hash at hash[offset]. Each hash[i] contains a pointer to the head of
 *     a linked list. So to insert a value in hash, what we do is, we first get
 *     the head pointer from hash[i], then we traverse to the end of list and add
 *     a new node to the end of list with the value of tree node.
 *     Once tree root value is in hash, we recursively call for root->left with
 *     offset=offset-1 and root->right with offset=offset+1. Now the problem is,
 *     we cannot have -ve index for hash. So we cannot start with offset of 0.
 *     So, to overcome this, we first calculate number of nodes in the tree.
 *     Then we have to get log to the base 2 of this number of nodes. We do
 *     this by doing while(num/2) { num = num/2; count++;}. The count we got
 *     tells us offset can be in range -count to +count. So we initialize
 *     offset with 2*count.
 *     Once entire tree is parsed, we parse the hash from 0 to 2*count, and
 *     for each entry, we traverse the list and keep printing the node values.
 *     Before going to next entry of hash, we print a new line.
 *
 *     Time complexity is: O(n) to traverse entire tree and then again, we
 *     traverse all these nodes from the list so O(n). So total time
 *     complexity is O(n).
 *     Space complexity: We need 2*log(n) extra space for hash and O(n) extra
 *     space for storing the tree nodes in linked list. And again recursive
 *     calls need O(n) stack space. So total O(n) space.
 */
void verticalOrderTree(tree_node *root) {
    int node_count=0;

    node_count = countNode(root);
    int offset_range=0;
    while(node_count/2) {
        offset_range++;
        node_count = node_count/2;
    }
    int offset = offset_range;
    ll_node *hash[2*offset] = {NULL};

    fillHash(root, offset, &hash);

    for(int i=0; i<2*offset_range; i++) {
        if(hash[i]) {
            ll_node *temp = hash[i];
            while(temp) {
                printf("%d ", temp->val);
                temp = temp->next;
            }
            printf("\n");
        }
    }

    return;
}

void fillHash(tree_node *root, int offset, ll_node **hash) {
    if(!root) {
        return;
    }
    ll_node *temp = *hash[offset];
    temp = new_ll_node(root->val);
    fillHash(root->left, offset-1, hash);
    fillHash(root->right, offset+1, hash);
    return;
}

/*
 * 27. Implement a data structure to add and search word. addWord will add
 *     the word in dictionary and searchWord will search for keyword. keyword
 *     can be a whole word or it can contain a '.' Here '.' means any single
 *     char.
 *
 *     We use Trie for this. For addWord, we create child nodes starting from
 *     root for each char in word and on the last node, we add the whole word.
 *
 *     For searWord, we traverse the trie from root for each char. If the
 *     present char is not '.', then we look for exact child node. If it is
 *     a '.', then we traverse for all children and if any one returns true,
 *     we return true.
 *
 *     Time complexity for addWord and searchWord is O(n) where n is length
 *     of word. In case of a '.' present in searchWord, time complexity
 *     increases to n^n.
 */

/*
 * 28. Given a list of integers, find total hamming distance between all
 *     possible pairs. Hamming distance is the number of bits in both the
 *     numbers that are not same. e.g. hammin distance between 5 and 2 is
 *     3 because total 3 bits have different values 101, 010
 *
 *     One way to do is to find all possible pairs if numbers and for each
 *     of these pairs, do n1^n2 so that we get all those bits set which are
 *     not equal. Then count number of 1s from this result and this is the
 *     hamming distance between these two numbers. Keep doing this for all
 *     pairs. But this is very expensive approach.
 *
 *     Anothe better way is, we traverse over each bit instead of finding
 *     all pairs. We define a count array of size 32 to count number of 1s
 *     in all given numbers at each bit location. Once we have this count,
 *     we can get the count of number of 0s by doing n - 1s count where
 *     n is total number of numbers in given array. Once we have these
 *     counts, we can say that all the pairs formed such that 1 number
 *     has 1 in this bit position and another has 0 in this bit position,
 *     then their hamming distance is 1. There are in total a*n-a
 *     possibilities. here a is number of 1s and n-a is number of 0s.
 *     If we do this for each bit from 0 to 32, we will have the answer
 *
 *     Time complexity is O(n) where n is O(n*m) where n is total numbers
 *     in the given array and m is the max length of number in binary
 *     representation.
 *
 *     Extra space is O(1) as we are using only 32 size array.
 */
int totalHammingDistance(int *arr, int len) {
    int count[32] = {0};
    int hamming_count = 0;

    for(int i=0; i<len; i++) {
        int j=0;
        while(arr[i] > 0) {
            count[i] += (arr[i] & 1);
            arr[i] >>= 1;
            i++;
        }
    }

    for(int i=0; i<32; i++) {
        hamming_count += count[i]*(len-count[i]);
    }

    return hamming_count;
}

/* 29. Max Swaps: Given an integer, return max possible integer by making atmost
 *     1 swap of digits from the given integer.
 *
 *     Here one thing to point out is it is mentioned that we can do atmost 1
 *     swap. This means we have 2 options, either do 1 swap or do 0 swap and
 *     return the same integer. We use a hash table for this. First we traverse
 *     the given integer and store its digits in hash along with their indices.
 *     Then we traverse the integer again and for each index, we try to get max
 *     available digit from the hash table. If we get one such digit, we swap
 *     current digit with that digit and return. If no such digit is found, we
 *     return the original number with 0 swaps.
 *
 *     Time complexity is O(n) where n is length of integer and Space is O(1)
 *     as we need constant space for hash. (length og hash is 9 for digits 1-9)
 */
int maxSwaps(int input) {
    int len=0;
    int temp = input;
    while(temp) {
        temp = temp/10;
        len++;
    }
    int in_arr[len];
    int hash[9] = {-1};
    int i=len;
    temp = input;
    // Get array from input integer and also fill the hash
    while(temp) {
        in_arr[i] = temp%10;
        hash[in_arr[i]] = i;
        temp = temp/10;
        i--;
    }

    // For each digit in our array try to find max digit present in the hash
    // and swap if present.
    for(i=0; i<len; i++) {
        for(int d=9; d>in_arr[i]; d--) {
            if(hash[d] > i) {
                int swap = in_arr[i];
                in_arr[i] = in_arr[hash[d]];
                in_arr[hash[d]] = swap;
                int result = in_arr[0];
                for(int k=1; k<len; k++) {
                    result = result*10 + in_arr[k];
                }
                return result;
            }
        }
    }

    return input;
}

/*
 * 30. Walls and Gates: Given a 2d array with 3 possible values in it
 *      0  - Gate
 *     -1  - Wall
 *     INF - Empty
 *     Return a 2d array with the distance to nearest gate from all
 *     empty spaces.
 *
 *     The idea here is to find the distance of each cell from a cell
 *     marked as 0. And this distance should be nearest distance.
 *     If a cell is marked as -1 then its a wall and we ignore it.
 *     This is best candidate for BFS. We start with the cell with 0 and
 *     visit all its neighbors first and mark their distance as 1. Then we visit
 *     all the neighbors of all these neighbors and mark their distance as 2
 *     and so on. But there is a issue here. We can have multiple cells with 0
 *     and in this case, we have to do BFS starting from each of these cells
 *     one by one and update the cells with the cost only if the new cost is
 *     less than the existing cost. To further optimize it, we can start BFS
 *     from all the cells with 0 simultaneously. This way, we can be done with
 *     updating the costs in M*N time. As we are doing it simultaneously, in
 *     first pass, all possible cells with distance 1 will get visited and then
 *     in 2nd pass all cells with cost 2 and so on. During this, if we encounter
 *     a cell which has been updated already, we ignore it as it is already
 *     visited.
 *     How to do BFS simultaneously?
 *     The answer is simple. We use queue for BFS just like normal case. The
 *     only difference here is, we first traverse the entire 2d array and enqueue
 *     all the cells in the queue which have 0. (In normal case, we would enqueue
 *     only 1 cell to start with, but here we are enquiuing all). Now, while
 *     queue is not empty, we dequeue the element, get all its neighbors, update
 *     their distance and enqueue them. This way, we are doing BFS simultaneously.
 *
 *     Time complexity is O(M*N).
 */
int** wallsGates(int **grid, int rows, int columns) {
#define INF 9999
    // Define a result array
    int **result = (int **)malloc(sizeof(int*)*rows);
    for(int i=0; i<rows; i++) {
        result[i] = (int *)malloc(sizeof(int)*columns);
    }

    // Initialize the result array to all INF
    for(int i=0; i<rows; i++) {
        for(int j=0; j<columns; j++) {
            result[i][j] = INF;
        }
    }

    // Define a queue. Our queue node has two members x and y for indices.
    queue_node *root=NULL;
    queue_node *temp=NULL;

    // Enqueue ALL cells with 0 value also update their distance in result
    for(int i=0; i<rows; i++) {
        for(int j=0; j<columns; j++) {
            if(grid[i][j] == 0) {
                enqueue(root, i, j);
                result[i][j] = 0;
            }
        }
    }

    // Now start BFS algo while queue is not empty.
    while(!isEmpty(root)) {
        temp = dequeue(root);
        int x = temp->x;
        int y = temp->y;

        // update distances of all neighbors and enqueue them
        if(y-1>0 && result[x][y-1]==INF) {
            if(grid[x][y-1] == -1) {
                result[x][y-1] = -1;
            } else {
                result[x][y-1] = 1 + result[x][y];
                enqueue(root, x, y-1);
            }
        }

        if(y+1<column && result[x][y+1]==INF) {
            if(grid[x][y+1] == -1) {
                result[x][y+1] = -1;
            } else {
                result[x][y+1] = 1 + result[x][y];
                enqueue(root, x, y+1);
            }
        }

        if(x-1>0 && result[x-1][y]==INF) {
            if(grid[x-1][y] == -1) {
                result[x-1][y] = -1;
            } else {
                result[x-1][y] = 1 + result[x][y];
                enqueue(root, x-1, y);
            }
        }

        if(x+1<row && result[x+1][y]==INF) {
            if(grid[x+1][y] == -1) {
                result[x+1][y] = -1;
            } else {
                result[x+1][y] = 1 + result[x][y];
                enqueue(root, x+1, y);
            }
        }
    }

    return result;
}
