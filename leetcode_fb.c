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
 *    We use dynamic programming here. To get the min number of swaps at ith
 *    index, we need to know min number of swaps at i-1th index. If,
 *    A[i-1] < A[i] and B[i-1] < b[i], then it is already in strictly increasing
 *    order so no swaps are required at this location. So we can just copy the
 *    swaps required for i-1th location. TODO: Incomplete. Complete it later.
 *
 */

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
