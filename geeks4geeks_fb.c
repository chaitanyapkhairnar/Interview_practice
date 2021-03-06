/*
 * This file contains all the questions with fb tag on geeks for geeks website.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

/*
 * 1. Find number of flips required to convert the given string of binary digits
 *    to a string that has all 1s on left and all 0s on right.
 *    {10110001} => {11110000} 2 flips required. 1 to flip second bit and 1 for last bit
 *
 *  We first convert the string to integer and then we xor this integer with all
 *  possible masks with 1s on left and 0s on right. masks for above eg are
 *  10000000, 11000000, 11100000, 11110000, 11111000, 11111100, 11111110.
 *  The number of 1s in the result of xor of integer and mask will be number of flips
 *  required. We get the minimum of this count and return.
 */

// Count number of 1s in given number
int get_ones(int in) {
    int count = 0;
    while(in) {
        in = in & (in-1);
        count++;
    }
    return count;
}

int string_to_int(char *str) {
    int len = strlen(str);
    int result = 0;
    for(int i=0; i<len; i++) {
        int power = pow(2, i);
        if(str[len-1-i] == '1') {
            result = result + power;
        }
    }
    return result;
}

int min_flips_reqd(char *str) {
    int input=0, min_flips, output;
    
    int len = strlen(str);
    // convert str to int
    input = string_to_int(str);

    // Initialize min_flips to len of string
    min_flips = len;

    // Create a mask variable
    int mask = 0;

    // Start a for loop to test with each mask
    for(int j=(len-1); j>0; j--) {
        mask = mask | 1<<(j);
        // Calculate xor
        output = input^mask;
        // Get number of 1s in output and if minimum, store it
        int ones = get_ones(output);
        if(ones < min_flips) {
            min_flips = ones;
        }
    }
    return min_flips;
}

/*
 * 2. Find all possible interpretations of an array of digits.
 *    Given a coding pattern such that 1 means 'a', 2 means 'b' ... 26 means 'z' and
 *    given an array of integers say [1,2,3], print all possible interpretations like
 *    1,2,3 = abc; 1, 23 = aw and 12,3 = lc.
 *
 *    The idea is to use recursion. For each case, we have two choices. Either use
 *    single digit or use two digits. We use str to maintain the result stored so far.
 *    We also pass str index and array index to recursive function.
 *    We have a dictionary to map 1,2,3 to a,b,c, ...
 */
char dictionary[26] = {'', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',
                       'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y',
                       'z'};

void print_all_interpretations(int arr[], int arr_idx, int arr_len, char *str, int str_idx) {
    if(arr_idx >= arr_len) {
        printf("%s\n", str);
        return;
    }

    str[str_idx] = dictionary[arr[arr_idx]];
    print_all_interpretations(arr, arr_idx+1, arr_len, str, str_idx+1);

    if(arr[arr_idx] <= 2) {
        int number = 0;
        number = 10*arr[arr_idx] + arr[arr_idx+1];
        if(number <= 26) {
            str[str_idx] = dictionary[number];
            print_all_interpretations(arr, arr_idx+2, arr_len, str, str_idx+1);
        }
    }
    return;
}

void all_interpretations(int arr[], int arr_len) {
    int arr_idx=0;
    char *str = (char *)malloc(sizeof(char)*100);
    int str_idx = 0;
    print_all_interpretations(arr, arr_idx, arr_len, str, str_idx);
    return;
}

/*
 * 3. Convert a ternary expression to a binary tree.
 *    Given a ternary expression say a?b:c, convert it into binary tree a
 *                                                                     / \
 *                                                                    b   c
 *    The expression can be nested like a?b?c:d:e
 *    
 *    See ternary.c for detailed implementation.
 */

/*
 * 4. Largest sum subarray with at-least k numbers
 *    Given an array, we need to find a subarray which has atleast k distinct
 *    numbers and it also has the largest sum.
 *
 *    We use sliding window technique here. We have two pointers start and end. We start
 *    a loop until end pointer < length of array. We also have a hash table to store the
 *    elements parsed so far to keep track of unique elements. We start traversing the
 *    array and for each element, we check if its already there in hash. If yes, we
 *    increment its count in hash. If not, we increment its count in hash and also
 *    increment another counter say unique_counter. We update the sum and store the sum
 *    in the max_sum if it is > the max_sum. Once we have k unique elements, we move the
 *    start pointer and remove that element from sum and from hash. We check if the
 *    unique counter needs to be updated or not. We also update max_sum if needed. We
 *    keep doing this until our unique counter goes below k. After this, we again 
 *    increment end pointer and continue. In the end, we get max sum.
 */

int largest_subarray_sum_k(int arr[], int len, int k) {
    int start = 0, end = 0;
    if(len < k) {
        return -1;
    }
    int unique_ctr=0, sum=0, max_sum=0, hash[100] = {0};
    while(end < len) {
        
        if(unique_ctr < k) {
            if(hash[arr[end]] == 0) {
                unique_ctr++;
            }
            hash[arr[end]]++;

            sum = sum + arr[end];
            if(sum > max_sum) {
                max_sum = sum;
            }
            end++;
        } else {
            while(unique_ctr >= k) {
                sum = sum  - arr[start];
                hash[arr[start]]--;
                if(hash[arr[start]] == 0) {
                    unique_ctr--;
                }
                if(sum > max_sum) {
                    max_sum = sum;
                }
                start++;
            }
        }
    }
    return max_sum;
}

/*
 * 5. Minimum Word Break: Given a list of words as dictionary and given a string
 * find minimum number of breaks needed on the string so that each of the substring
 * created by breaks are present in the dictionary.
 * For e.g. dictionary ["Cat", "Mat", "Ca", "tM", "at", "C", "Dog", "og", "Do"]
 * String "Catmat", Minimum breaks required is 1 after t such that Cat and Mat
 * substrings are formed, and both these are in dictionary.
 *
 * We use Trie here. We first parse the dictionary and create a Trie for each word in
 * dictionary. We now parse the given string and for each character, we check if it
 * is present in the Trie. If yes, we increase the break counter and recurse with
 * string start index++. The main thing to consider here is, when we return from
 * recursion, we should again check in trie if next character exists after the 
 * present character we are in. If yes, we move our trie pointer to this next character
 * and continue the for loop. This way, say for catmat, we first get C and see in trie
 * that C is EOF, so we recurse with atmat with break++. And then in the end when we
 * return from all the recursions, we check that if CA exists in trie. It exists, so we
 * continue. This way, we hit CAT case and thus we get minimum breaks required.
 *
 * Complexity is O(nm) to create a trie where n is number of words in the list and m is
 * the max length of a word. Then for recursion, we have O(k^2) complexity where k is
 * the length of given string. Because, in worst case, for each character in the given
 * string, we call recursion for each other character.
 * So total complexity is O(mn) + O(k^2)
 */
#define ALPHABET_SIZE 26

// Structure for trie node
typedef struct trie_node {
    struct trie_node *children[ALPHABET_SIZE];
    bool is_end;
}trie_node;

// Function to create a new trie node
trie_node* get_new_node(void) {
    trie_node *temp;
    temp = (trie_node *)malloc(sizeof(trie_node));
    temp->is_end = false;
    for(int i=0; i<ALPHABET_SIZE; i++) {
        temp->children[i] = NULL;
    }
    return temp;
}

// Function to insert word in trie given root node
void insert_word(trie_node *root, char *word, int len) {
    if(len == 0) {
        return;
    }
    trie_node *temp = root;
    for(int i=0; i<len; i++) {
        int index = word[i]-'a';
        if(!temp->children[index]) {
            temp->children[index] = get_new_node();
        }
        temp = temp->children[index];
    }
    // Mark end of word
    temp->is_end = true;
}

// Function to get minimum number of breaks
void min_breaks(char *str, int len, int start, int *min_break, int level, 
                trie_node *root) {
    // Base case: If we reach end of string, we update the min_break
    if(start == len) {
        if(level-1 < *min_break) {
            *min_break = level-1;
        }
        return;
    }

    trie_node *temp = root;
    // Traverse the given string and check in trie if present char exists
    for(int i=start; i<len; i++) {
        int index = str[i] - 'a';
        // If current char does not exist, return
        if(!temp->children[index]) {
            return;
        }
        // If current char exists, look if it is end of word. If yes,
        // we increment the level and recursively call with index+1
        temp = temp->children[index];
        if(temp->is_end) {
            min_breaks(str, len, i+1, min_break, level+1, root);
        }
        // When we come back here, we have updated min_break. Now continue
        // to check if we can make any other word by appending next character
        // in the given string. If yes, we continue the process.
    }
}

/*
 * 6. Given two sorted arrays, find the median of them.
 *    We have to find the median of all the numbers in both the arrays.
 *    One straight forward solution is to use the merge method of mergesort
 *    and while merging, keep counting. Once the count reaches (n+m/2), we have
 *    the median element. Here n and m are the lengths of given arrays. This is
 *    O(n) approach. There is a better solution to this which is O(log(n))
 *    approach where n is the length of the shorter array. The idea is to
 *    partition arrays into 2 halves such that first half contains some
 *    elements from array1 and some elements from array2 and second half
 *    contains the rest of the elements. Now we have to reach a condition
 *    such that all the elements in first half are smaller than all the
 *    elements in the second half. Once we reach this condition, we have
 *    the median. Please see below link for detailed explanation
 *    https://www.geeksforgeeks.org/median-two-sorted-arrays-different-sizes-ologminn-m/
 */
int getMedian(int *a, int n, int *b, int m) {
    /* Make sure that a is smaller length array. */
    if(n>m) {
        int *temp = a;
        a = b;
        b = temp;

        int t = n;
        n = m;
        m = t;
    }

    int min, max, i, j, median=0;

    min = 0;
    max = n;

    while(min < max) {
        i = (min+max)/2;
        j = ((n+m+1)/2)-i;

        /* Check if b[j-1] > a[i] and if yes, update min=i+1;
         * Similarly if a[i-1] > b[j], max = i-1;
         * We want to reach the condition where
         * a[i-1] <= b[j] && b[j-1] <= a[i]
         */
        if(i<n && j>0 && b[j-1] > a[i]) {
            min = i+1;
        }
        else if(j<m && i>0 && a[i-1] > b[j]) {
            max = i-1;
        } else {
            /* We have reached the condition. Now get the median */
            if(i == 0) {
                median = b[j-1];
            } else if(j == 0) {
                median = a[i-1];
            } else {
                median = max(a[i-1], b[j-1]);
            }
            break;
        }
    }

    // If number of elements are odd, then return the median.
    if(n+m % 2 == 1) {
        return median;
    } else {
        // For even elements, median is average of two middle elements
        if(i == n) {
            return median+b[j]/2;
        } else if(j == m) {
            return median+a[i]/2;
        } else {
            return median+max(a[i], b[j])/2;
        }
    }
}

/* Time complexity is O(log(n)) */
