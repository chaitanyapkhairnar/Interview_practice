/*
 * This file contains leetcode questions asked in Google Interview.
 * Solutions are mostly theoratical with some pseudo-coding
 */

/*
 * 1. Generate parenthesis: Given a number n, generate all possible
 *    parenthesis with n '(' and n ')'.
 *
 *    We use backtracking here. The idea is to start with a '(' and then
 *    for rest of n brackets, we either put a '(' or a ')' and continue.
 *    Base case is if we have string length equal to 2n, we print and return.
 */
void generateParenthesis(int n) {
    char *result = (char*)malloc(sizeof(char)*2n);
    result[0] = '(';

    backtrackingParenthesis(result, 2*n, n-1, n, 1);
    return;
}

void backtrackingParenthesis(char *result, int max_len, int open_cnt, int close_cnt, int start) {
    if(start == max_len) {
        printf("%s\n", result);
        return;
    }

    if(open_cnt > 0) {
        result[start] = '(';
        backtrackingParenthesis(result, max_len, open_cnt-1, close_cnt, start+1);
    }

    if(close_cnt > 0) {
        result[start] = ')';
        backtrackingParenthesis(result, max_len, open_cnt, close_cnt-1, start+1);
    }
}

/*
 * 2. Merge Intervals: Given a list of intervals in the form of pair of start
 *    time and end time, merge the overlapping intervals.
 *
 *    We use sorting here. We store start times and end times in seperate arrays
 *    Then we sort the array with start times and while doing these operations,
 *    we do same operations on end time array to maintain the relation. Then
 *    we get a stack with nodes having start and end time as members and push
 *    first start time and its pair end time into stack. Then we compare the
 *    start time of next element with the end time of current element in the
 *    stack and if less, we update the end time of current element to end time
 *    of next element. If not then we push this element in the stack. In the end
 *    the stack has the list of merged elements.
 *    Time complexity is O(nlog(n)) and extra space required is O(n).
 */

/*
 * 3. Number of Islands: Given a 2d array of 1s and 0s, return the number of
 *    islands in it. 1s denote land and 0s denote water. Assume out of bound
 *    indices are all water. Any connected chunk of 1s is an island. e.g.
 *    1 1 0 0 0
 *    1 1 0 0 0
 *    0 0 1 0 0
 *    0 0 0 1 1
 *    Here there are 3 islands. 1s connected diagonally are not considered
 *    connected.
 *
 *    We traverse the 2d array and for each element, we check if the top or left
 *    element is 1. If yes, we do not increment the count, else we increment the
 *    count. In the end, we will have the count of islands.
 */
int numberOfIslands(int **grid, int rows, int columns) {
    int count = 0;
    for(int i=0; i<rows; i++) {
        for(int j=0; j<columns; j++) {
            if(arr[i][j] == 1) {
                if((i-1 < 0) && (j-1 < 0)) {
                    count++;
                } else if(i-1 < 0) {
                    if(arr[i][j-1] == 0) {
                        count++;
                    }
                } else if(j-1 < 0) {
                    if(arr[i-1][j] == 0) {
                        count++;
                    }
                } else {
                    if(arr[i-1][j] == 0 && arr[i][j-1] == 0) {
                        count++;
                    }
                }
            }
        }
    }
    return count;
}

/*
 * 4. Spiral Matrix: Given a 2d matrix, print it in spiral order.
 *    Solution is in SpiralMatrix.c file. The approach is same as
 *    rotating the 2d array.
 */

/*
 * 5. Queue reconstruction by height: We have n people randomly standing in
 *    a queue. Each person has 2 attributes height and number of people with
 *    height greater than our height standing in front of us. Arrange the queue
 *    to satisfy this. e.g.
 *    (7,0), (4,4), (7,1), (5,0), (6,1), (5,2) should be arranged as
 *    (5,0), (7,0), (5,2), (6,1), (4,4), (7,1)
 *
 *    The idea is first we find the people with max height and put them in
 *    result list on index specified by the second number in them
 *    So, first, we have
 *    (7,0), (7,1) Max height is 7 and they go to index 0 and 1 accordingly.
 *    Now we keep getting the next max height people and put them in the
 *    indices according to second number in them. While doing this, we may
 *    need to shift the existing elements in our result array. So, our next
 *    max height element is (6,1), so we put it at index 1 of result
 *    (7,0), (6,1), (7,1). Our (7,1) is shifted right. We continue doing this
 *    and we get the answer.
 *    (5,0), (7,0), (5,2), (6,1), (7,1)
 *    (5,0), (7,0), (5,2), (6,1), (4,4), (7,1)
 *
 *    We can use linked list to store the result as it is easier to insert
 *    elements in any index. We can store people's height in one array and
 *    second numbers in another. Then we sort array1 with same operations on
 *    array2. The we start taking the larger elements and store it in linked
 *    list. Time complexity is n^2 as it takes n^2 to insert n elements in
 *    the linked list.
 */

/*
 * 6. Valid Parenthesis: Given a string of brackets, return if it is valid or
 *    not.
 *
 *    We use stack here. For every opening bracket, we push it to stack and
 *    for every closing bracket, we pop the element and check if it is of
 *    same type as the closing bracket. If not, return false. When we reach
 *    end of string, finally we check if the stack is empty. If not, return
 *    false, else return true.
 */

/*
 * 7. Number addition: Given two arrays of integers, return a array containing
 *    the addition of these two arrays. The arrays contain digits of number such
 *    that MSB is in 0th index. e.g. a1=[1,2,3], a2=[9,9,8] then a3=[1,1,2,1]
 *
 *    We initialize carry to 0. Then we we start a while loop for i1>=0 and 
 *    i2>=0. We start with the last index of both arrays and start adding them
 *    and also add carry to it. Then we put res%10 in result array and res/10
 *    in carry. Decrement i1 and i2 and continue. Finally, we chek if any
 *    array is remaining. If yes, we put remaining values in result array.
 *    The size of result array will be 1+max(size of a1 and a2).
 *    Time complexity is O(n) where n is size of larger array.
 */
int numberAddition(int *a1, int *a2, int len1, int len2) {
    if(!a1 && !a2) {
        return -1;
    }
    if(!a1) {
        return a2;
    }
    if(!a2) {
        return a1;
    }

    int *result = (int*)malloc(sizeof(int)*((max(len1, len2))+1));
    int i=len1-1, j=len2-1, k=max(len1, len2), carry=0;

    while(i>=0 && j>=0) {
        int temp;
        temp = a1[i] + a2[j] + carry;
        carry = temp/10;
        result[k] = temp%10;
        i--;
        j--;
        k--;
    }

    // Take care of remaining digits
    while(i>=0) {
        
        result[k] = (a1[i]+carry)%10;
        carry = (a1[i]+carry)/10;
        k--;
        i--;
    }
    while(j>=0) {
        result[k] = (a2[j]+carry)%10;
        carry = (a2[j]+carry)/10;
        k--;
        j--;
    }

    // If carry, then add it to our result
    if(carry>0) {
        result[k] = carry;
    }

    return result;
}

/*
 * 8. Min Stack: Design a stack which supports push, pop, top and getMin in
 *    O(1) time.
 *
 *    There are 2 approaches. One is we use two stacks. For 1st push operation,
 *    we push the element in both stacks. For next push onwards, we push it into
 *    1st stack and check if it is smaller than top element on stack 2. If yes,
 *    we push it in stack 2 too. For pop, we pop from stack 1. We see if the popped
 *    element in top element in stack 2. If yes, we pop from stack 2 too. For
 *    get min, we return the top value of stack 2. This way all operations are O(1)
 *    at the expense of extra space.
 *
 *    Another approach is without using extra stack. We have a int min initialized
 *    to some high number. Then for first push, we store the element in min and 
 *    push element-min to stack. This would be 0 for first element. Then for next
 *    push onwards, we push element - min to stack. If element - min is +ve, we
 *    do not update the min. But if it is -ve, then we push that -ve element as is
 *    and update the min = element. For pop, if the element in +ve, we just add min
 *    to this popped element and return. But if it is -ve, then we return the min
 *    and then we update min = min + (abs(popped element)). As this was previous
 *    min. To get min, we just return the min.
 */
static int min = 9999;
void push(stack **top, int val) {
    if(min == 9999) {
        min = val;
    }
    int push_val = val - min;

    if(push_val < 0) {
        min = push_val;
    }
    stack *node = (stack*)malloc(sizeof(stack));
    node->val = push_val;
    node->next = *top;
    *top = node;
}

int pop(stack **top) {
    stack *temp = *top;
    *top = (*top)->next;
    int ret_val;
    if(temp->val > 0) {
        ret_val = temp->val + min;
    } else {
        ret_val = min;
        min = min + abs(temp->val);
    }
    return ret_val;
}

int top(stack **top) {
    return (*top)->val;
}

int getMin(stack **top) {
    return min;
}

/*
 * 9. Judge route circle: Initially robot is at 0,0 position. Then a string with
 *    series of commands is passed to robot to move the robot. Return true if
 *    the path of robot forms a loop. The commands are L for left move by 1
 *    position, R for right move, U for up and D for down. e.g.
 *    LLDRRU will form a loop.
 *
 *    Basically what we look at is if the robot starts and ends at current
 *    position. If yes, there is a circle/loop. We simply maintain two count
 *    variables, horizontal and vertical. We increment horizontal for a R and
 *    decrease it for L. Similarly we increase vertical for U and decrease it
 *    for D. Finally if we have both these 0, then it means that we came to
 *    origin and we return true. Else we return false.
 */

/*
 * 10. Island Primeter: We are given a 2d matrix of 1s and 0s. We need to find
 *     the perimeter of the island formed. perimeter is sum of sides.
 *
 *     The idea here is simple, For each cell which is 1, we check its neighbors
 *     which are left right top and bottom and we increment the count for each
 *     neighbor which is 0. We do this for entire array and we have the final count
 *     as perimeter.
 *     Time complexity is O(m*n).
 *
 *     if(arr[i][j] == 1) {
 *         if(arr[i-1][j] == 0) { count++; }
 *         if(arr[i+1][j] == 0) { count++; }
 *         if(arr[i][j-1] == 0) { count++; }
 *         if(arr[i][j+1] == 0) { count++; }
 *     }
 */

/*
 * 11. Anagram Mappings: We are given two variables which are anagrams of each
 *     other. We have to give the mappings of indices from variable 1 to 2.
 *
 *     We use hashmap here. We traverse the second variable and store the indices
 *     for the values. Then we traverse the first variable and for each value,
 *     we get the indices and print them.
 */

/*
 * 12. Power of 3: Given a number, return true if it is a power of 3.
 *
 *     One simple and straightforward approach is to check if number%3 is 0 and
 *     then keep doing number=number/3 while number%3 is 0. In the end, we check
 *     if the number is 1 then return true, else return false. The time complexity
 *     is O(log(n)) where log is to the base 3 and n is the given number. Another
 *     good method is to convert the given number to base 3 number and then check
 *     if it is of the form 10000... This works because in base 10 numbers, all
 *     powers of 10 are 10,100,1000,... Similarly for base 2 numbers, all powers
 *     of 2 are 10(2), 100(4), 1000(8), ... So for any base number, all the powers
 *     of that base are of the form leading 1 and then all 0s. Time complexity
 *     will be same.
 *     Yet another approach for this specific case is, we use the limitation of int
 *     variable. The max value of int is (2^32)/2 -1. And we know that 3 is a prime
 *     number. So all powers of 3 will be divisible only by 3 or multiples of 3.
 *     So we first get the max int which is also power of 3. This is 3^19.
 *     Now any int smaller than 3^19 will be a power of 3 only if it divides 3^19
 *     completely with a remainder of 0. So, if(3^19%n == 0), then n is a power
 *     of 3. The time complexity here is O(1).
 */

/*
 * 13. Convert given number to given base and vice versa.
 *
 *     To convert the given number to target base, we keep dividing the number
 *     with the target base and keep storing the remainder in a result string.
 *     Finally we reverse the string.
 *     while(num) {
 *         string[i] = num%base;
 *         num = num/base;
 *         i++;
 *     }
 *     return reverse(string);
 *
 *     To get base 10 of given number which is of given base form, we multiply
 *     each digit of given number with the base^position where position is the
 *     index of present digit. We add all these values to get the answer.
 *     e.g. str="19A", base=16.
 *     len = strlen(str);
 *     result = 0;
 *     pow=1;
 *     for(i=len-1; i>=0; i--) {
 *         result = result + (str[i]*pow);
 *         pow = pow*base;
 *     }
 */

/*
 * 14. Find all disappeared numbers: Given a array of len n containing integers
 *     in range 1 to n and it can have duplicates, return the list of missing
 *     numbers.
 *
 *     The straightforward way to do this is to use hash. We traverse the array
 *     and mark the values as true. Then we traverse the hash array from 1 to n
 *     and print all the indices who are false. We do this in O(n) time with
 *     O(n) extra space. We can reduce the space by using bit vector. Say if
 *     range is 32, then we can take a int variable initialized to 0 and then
 *     we set the corresponding bits. Then we print all the position at which
 *     the bits are 0.
 *     Best way to do without using extra space and using the fact that all
 *     numbers are within range 1 to n is to use the array itself as a hash.
 *     We traverse the array and for each abs(value) in arr[i], we make arr[value]
 *     element -ve. We complete the traversal and then we again traverse the
 *     array and print the indices whose values are +ve.
 *     for(i=0; i<n; i++) {
 *         arr[abs(arr[i])] = arr[abs(arr[i])]*-1;
 *     }
 *     for(i=0; i<n; i++) {
 *         if(arr[i] > 0) {
 *             printf("%d ", i);
 *         }
 *     }
 *
 *     Time complexity is O(n)
 */

/*
 * 15. First unique char in string: Given a string, return the index of first
 *     char that is unique.
 *
 *     Parse the string first and store the count in hash. Then parse the string
 *     again checking the count in hash and print first char whose count is 1.
 *
 *     Time complexity is O(n) where n is len of string.
 */

/*
 * 16. Power of 2
 *     One way to solve is to keep dividing the num by 2 until remainder is 0
 *     In the end if num is 1 then return true else false.
 *     if(num <=0) return false
 *     while(num%2 == 0) {
 *         num = num/2;
 *     }
 *     if num == 1 return true, else return false.
 *     We have to consider the corner case num == 0. If not, we will be stuck in
 *     while loop forever.
 *     Time complexity is O(log(n)) here log is base 2.
 *
 *     Another way is to use the bit manipulation. We know that if a number is
 *     power of 2, it will have only 1 bit set. So we count number of bits set
 *     in the number and if it is 1 then it is power of 2. We can easily do this
 *     in O(1). We do num & num-1. If this is 0, then return true, else there are
 *     more than 1 bit set, so return false.
 */

/*
 * 17. Reverse only vowels: Given a string, reverse only vowels in it.
 *
 *     We use similar method to reverse the string. We initialize start=0
 *     and end=len-1. then,
 *     while(start < len) {
 *         while(str[start] != vowel) { start++; }
 *         while(str[end] != vowel) { end--; }
 *         if(start > end) return;
 *         swap(str[start], str[end]);
 *     }
 *     Time complexity is O(n)
 */

/*
 * 18. All tree paths: Given root of tree, print all paths from root to leaf node.
 *
 *     We use recursion here. First we check if(!root) then return NULL. We define
 *     a string variable and put s[0]=root->val. Then if(!root->left && !root->right)
 *     print s and return. if(root->left) recursively call by passing s as argument.
 *     if(root->right) recursively call by passing s as argument.
 *     Time complexity is O(n) where n is number of nodes in tree.
 */

/*
 * 19. Diameter of Binary tree: Given a root, return the diameter of binary tree.
 *     Diameter is the longest distance between any two nodes in the tree.
 *
 *     The longest distance between any two nodes has to pass through root. So,
 *     to get the longest distance, we get farthest left node and farthest right node
 *     from root and add their distances. To get the distance of farthest node
 *     from root, we recursively call for left and right child, get distances
 *     each of these and then add 1 to max of these and return.
 *     Time complexity is O(n).
 */
int diameterBST(node *root) {
    if(!root) {
        return -1;
    }
    if(!root->left && !root->right) {
        return 0;
    }
    int leftdistance = 0, rightdistance = 0;
    if(root->left) {
        leftdistance = getMaxDistance(root->left);
    }
    if(root->right) {
        rightdistance = getMaxDistance(root->right);
    }
    return leftdistance + rightdistance + 1;
}

int getMaxDistance(node *root) {
    if(!root->left && !root->right) {
        return 0;
    }
    int left=0, right=0;
    if(root->left) {
        left = getMaxDistance(root->left);
    }
    if(root->right) {
        right = getMaxDistance(root->right);
    }
    return max(left, right) + 1;
}

/*
 * 20. Binary Watch: Given a binary watch which has 4 LEDs to represent hour
 *     and 6 LEDs to represent Minutes in binary form such that whatever LED
 *     is lit, the time is represented by it. Now given a number n which 
 *     denotes number of LEDs lit, print all possible times.
 *
 *     The first thing that comes to mind in using backtracking. We can have a
 *     string on len 10 which is initialized to all 0s. Say first 4 chars
 *     represent 4 leds of hours and last 6 represent minutes. Now, we
 *     start a for loop for 0 to 9 and for each char, we have two options, either
 *     make it 1 or 0. So for these options, we recursively call the function.
 *     We keep track of number of 1s and when this count is reached, we print
 *     the time based on the state of string and return.
 *
 *     Another simpler approach is for each hour and minute, we calculate number
 *     of bits set and if it is equal to given number, we print the hour and min.
 *     for(h=0; h<12; h++) {
 *         for(m=0; m<60; m++) {
 *             int bits = countBits(h) + countBits(m);
 *             if(bits == n) {
 *                 printf(hours:mins);
 *             }
 *         }
 *     }
 */

/*
 * 21. Toeplitz Array: Given a array return true if it is a toeplitz array.
 *     An array is toeplitz if each of its diagonal elemnts from top left to
 *     bottom right are equal. e.g. below array is toeplitz
 *     1 2 3 4
 *     5 1 2 3
 *     9 5 1 2
 *
 *     The first idea that comes to mind is, for each element, check if it
 *     is equal to its bottom right neighbor. So check if a[i][j] == a[i+1][j+1]
 *     Also keep check if i+1 or j+1 goes out of bounds. If at any point, it is
 *     not equal, return false.
 *
 *     for(r=0; r<row_len-1; r++) {
 *         for(c=0; c<column_len-1; c++) {
 *             if(a[r][c] != a[r+1][c+1]) {
 *                 return false;
 *             }
 *         }
 *     }
 *     return true;
 *
 *     This is O(mn) approach.
 *
 *     Another approach using extra space is by using hash. We say that r1,c1
 *     and r2,c2 are diagonals of each other only if r1-c1 == r2-c2. So what we
 *     do is, for each r and c, we put the value of a[r][c] in hash at key r-c
 *     (or c-r) if it is not already present, else we check if the value matches
 *     If not a match, return false.
 *
 *     for(r=0; r<row_len-1; r++) {
 *         for(c=0; c<column_len-1; c++) {
 *             if(hash[c-r] == INT_MIN) {
 *                 hash[c-r] = arr[r][c];
 *             } else {
 *                 if(arr[r][c] != hash[c-r]) {
 *                     return false;
 *                 }
 *             }
 *         }
 *     }
 *     return true;
 *
 *     This is also O(mn), but it also uses extra space.
 */

/*
 * 22. Longest univalue path: Given a tree, return the longest path such that
 *     each node in the path has same value. The path may not pass through
 *     root. e.g.
 *                        1
 *                     2    5
 *                    3 4    5
 *                   3      5
 *    In this case, longest univalue path is 3 which is made of all 5s.
 *
 *    Its a tree problem so obviously we use recursion. In recursive func
 *    arguments, we pass path count till now. we call function for both
 *    nodes checking if our value is same as nodes value. If yes, we
 *    increment the count of path count in argument. Finally return the
 *    max of left and right node returned values. Dont forget to consider
 *    the case where left->val and right->val are equal to root->val.
 *
 *    int longestUnivalupath(node *root, int path_count) {
 *        if(!root) {
 *            return 0;
 *        }
 *        if(!root->left && !root->right) {
 *            return path_count+1;
 *        }
 *
 *        int left=0, right=0;
 *        if(root->left) {
 *            if(root->val == root->left->val) {
 *                left = longestUnivalupath(root->left, path_count+1);
 *            } else {
 *                left = longestUnivalupath(root->left, path_count);
 *            }
 *        }
 *        if(root->right) {
 *            if(root->val == root->right->val) {
 *                right = longestUnivalupath(root->right, path_count+1);
 *            } else {
 *                right = longestUnivalupath(root->right, path_count);
 *            }
 *        }
 *        if(root->val == root->left->val == root->right->val) {
 *            return left+right-1;
 *        } else {
 *            return max(left, right);
 *        }
 *    }
 *
 *    Time complexity is O(n) where n is number of nodes in the tree.
 */

/*
 * 23. Number of Boomerangs: Given a set of points, return all boomerangs.
 *     A boomerang is a set of 3 points i,j and k such that distance between
 *     i and j equals distance between i and k. Order matters.
 *
 *     We use hash here. For i=0 to n, we run another loop j=0 to n. We
 *     calculate distance between i and j and check if the value is present
 *     in hash at index distance. If not, put i,j in hash (maintain order)
 *     at distance index. If value found, we print found values (say a,b) and
 *     j (tuple is a,b,j). When we increment outer loop i, clear the hash table.
 *
 *     Time complexity is O(n^2).
 *     
 *     we use memset to clear hash. We use array of structures as hash. struct
 *     has members x1, y1, x2, y2.
 */

/*
 * 24. Maximum average subarray: Given a array of size n and an integer k < n,
 *     find the subarray of length k which has maximum average.
 *
 *     We are given window size k. So we use windowing here. We take 2 variables
 *     start and end. Initially start = 0 and end = 0. Then we move end to k steps
 *     ahead and keep getting the sum in sum variable. Now we take average
 *     by calculating sum/4 and store it. Now while end < len, we do
 *     sum=sum-arr[start--]+arr[++end] and get new average and update it only if
 *     it is more than our prev average. Finally when end reaches the end of array
 *     we have the max average.
 */

/*
 * 25. Minimum difference BST: Given a BST, find the minimum difference between
 *     two different nodes.
 *
 *     The straightforward approach is to get the Inorder traversal of tree so
 *     that we have all elements in sorted order. The we take difference of all
 *     neighboring pairs and return the minimum difference. We can implement this
 *     within Inorder algorithm so we get the min diff in O(n) time.
 *     We have a node *prev=NULL. We start with root and first check the base case
 *     if root == NULL, return. Then just like inorder, we recursively call
 *     for root->left. After returning from this, we check if prev != NULL.
 *     Inside this, we take the diff of node->val - prev->val and update the 
 *     min diff if required. Then we update prev = node and call for
 *     node->right. This way, we are checking for each neighboring pair and
 *     updating the diff. Finally, we return the diff.
 */

/* 26. Baloon burst problem: Refer this for problem:
 *     https://leetcode.com/problems/burst-balloons/description/
 *     Refer this for solution:
 *     https://www.youtube.com/watch?v=IFNibRVgFBo
 *
 *     Time complexity is O(n^3).
 */
int baloonBurst(int *arr, int arr_len) {
    // dp array to store the results.
    int dp[arr_le][arr_len] = {0};

    for(len=1; len<arr_len; len++) {
        for(start=0; start<arrLen-len; start++) {
            end = start + len - 1;
            for(i=start; i<=end; i++) {
                int leftVal=1;
                int rightVal=1;

                if(i != 0) {
                    leftVal = arr[i-1];
                }
                if(j != arr_len-1) {
                    rightVal = arr[j+1];
                }

                int before = 0;
                int after = 0;

                if(i != start) {
                    before = dp[start][i-1];
                }
                if(end != i) {
                    after = dp[i+1][end];
                }

                dp[start][end] = max(dp[start][end], (leftVal*arr[i]*rightVal + before + after));
            }
        }
    }
    return dp[0][arr_len-1];
}
