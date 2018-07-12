/*
 * TIPS:
 *
 * 1. Commonly used tables for hash are:
 *
 * int[26] for Letters 'a' - 'z' or 'A' - 'Z'
 * int[128] for ASCII
 * int[256] for Extended ASCII
 *
 * In ASCII table, characters start with a "space" whose value
 * is 32. Value of "A" is 65 and "a" is 97
 * 
 * We can get index of character for our hash table as str[i] - ' '
 * This will include all the characters in all cases.
 * The actual length of hash required is 127-32 = 95 as space is 32
 * and last character in ASCII is 127
 * 
 * 2. Given a number say 23156. If we want to isolate each digit
 * seperately, we use following
 * Units = num%10
 * Tens = (num%100)/10
 * Hundreds = (num%1000)/100
 * Thousands = (num%10000)/1000
 * and so on.
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/*
 * 1. Longest Substring without repeating characters
 */
int longestSubstringWithoutDuplicates(char *str, int *start, int *end) {
    // We find the longest substring in str which has all unique characters
    // and update the start and end pointers with the substring indexes.
    int len = strlen(str);
    if(!str || len == 0) {
        printf("Empty string\n");
        return 0;
    }
    // We use hash to store the visited character and its last found index.
    // Then we traverse the string by incrementing p2 and checking if the char
    // at p2 is present in hash or not. If not, get the curr len of substring
    // and update the maxLen if required and increment p2. But if char is present
    // in the hash, then check if the last found index of it is between p1 and p2.
    // If yes, we move p1 to index beyond this one. If not,
    // then this is not part of our substring, so proceed with p2++
    int p1=0;
    int maxLen=0, currLen=0;
    int hash[26];
    int index = -1;

    // Initialize hash
    for(int i=0; i<26; i++) {
        hash[i] = -1;
    }

    // Traverse String
    for(int p2=0; p2<len; p2++) {
        index = str[p2] - 'a';
        if(hash[index] < 0 || (hash[index] < p1)) {
            // Char not yet visited.
            hash[index] = p2;
            currLen = p2-p1;
            if(currLen > maxLen) {
                maxLen = currLen;
                *start = p1;
                *end = p2;
            }
        } else {
            p1 = hash[index] + 1;
            hash[index] = p2;
        }
    }

    return maxLen+1;
}

/* 2. Longest Palindromic substring in given string.
 * We traverse the entire string and for each i, we try to build
 * palindromic string around it by expanding in both directions.
 * We have to consider both even and odd length palindrome cases.
 * This is O(n^2) approach.
 */
char* longestPalindromeSubstring(char* s) {
    int low, high;
    int len = strlen(s);
    int maxLen=0;
    int start=-1;
    if(!s || len == 0) {
        printf("String is empty.\n");
        return NULL;
    }

    if(len == 1) {
        printf("Longest palindromic substring is %s\n", s);
        return s;
    }

    for(int i=0; i<len; i++) {
        /* Find all odd length palindromes with i as middle */
        low = i-1;
        high = i+1;
        while(low >= 0 && high < len && s[low] == s[high]) {
            if((high-low+1) > maxLen) {
                maxLen = high-low+1;
                start = low;
            }
            high++;
            low--;
        }
        
        /* Now find all even length palindromes */
        low = i-1;
        high = i;
        while(low >= 0 && high < len && s[low] == s[high]) {
            if((high-low+1) > maxLen) {
                maxLen = high-low+1;
                start = low;
            }
            high++;
            low--;
        }
    }
    /* If no substring found, then return any single character. as it itself
     * is a palindrome.
     */
    if(maxLen == 0) {
        char *res = (char*)malloc(sizeof(char));
        strncpy(res, s, 1);
        printf("Longest palindromic substring is %s\n", res);
        return res;
    }
    char *result = (char*)malloc(sizeof(char)*maxLen);
    strncpy(result, s+start, maxLen);
    printf("Longest palindromic substring is %s\n", result);
    return result;
}

/* 3. Given a string of digits, print all possible strings as they
 *    would mean on a telephone keypad.
 *    We assume that if a string has 0 or 1, we print 0 or 1 as this is
 *    a corner case.
 */
void PhoneKeypadPrintAll(char *str, int start_id, char dictionary[10][4], char *output) {
    int len = strlen(str);
    // Base Case
    if(start_id == len) {
        output[len] = '\0';
        printf("%s\n", output);
        return;
    }

    // Now we iterate for all possible characters in dictionary for str[start_id]
    int index = str[start_id] - '0';
    int i_len = strlen(dictionary[index]);
    for(int i=0; i<i_len; i++) {
        // We put the current char into output
        output[start_id] = dictionary[index][i];
        // Now we recurse for rest of given str.
        PhoneKeypadPrintAll(str, start_id+1, dictionary, output);
    }
}

void PhoneKeypadProblem(char *str) {
    /* This is O(4^n) approach. We first create a dictionary to store chars
     * for each digits as a 2d array. Then we get str[start_d] digit and iterate
     * the dictionary for all characters for this digit. For each of this digit,
     * we recursively call the function with start_id+1
     */
    if(!str || strlen(str) == 0) {
        printf("String is empty.\n");
        return;
    }
    int start_id = 0;
    char *output = (char*)malloc(sizeof(char)*strlen(str)+1);
    char dictionary[10][4] = {{"0"},
                              {"1"},
                              {"abc"},
                              {"def"},
                              {"ghi"},
                              {"jkl"},
                              {"mno"},
                              {"pqrs"},
                              {"tuv"},
                              {"wxyz"}};

    PhoneKeypadPrintAll(str, start_id, dictionary, output);
    return;
}

/*
 * 4. Check if str2 is rotation of str1 or not
 */
bool isRotationString(char *str1, char *str2) {
    /* We need to check if str1 is rotation of str2 or not. We simply
     * concatenate str2 with itself and check if str1 is substring of str2
     * or not. If yes, it means str1 is rotation of str2. The start index
     * of substring indicates the number of rotations on left to be done
     * on str1 to get str2.
     */

    // Corner case
    if(!str1 || !str2) {
        return false;
    }
    if(strlen(str1) != strlen(str2)) {
        return false;
    }

    int temp_len = 2*strlen(str1);
    char temp[temp_len];

    // Concatenate str1 to itself
    strcat(temp, str1);
    strcat(temp, str1);

    // Now check if str2 is substring of str1 or not.
    if(strstr(temp, str2)) {
        // str2 is found in str1
        return true;
    } else {
        return false;
    }
}

/*
 * 5. Print reverse of string using recursion
 */
void printReverseString(char *str, int index) {
    // Base case
    if(!str || index >= strlen(str)) {
        return;
    }
    printReverseString(str, index+1);
    printf("%c", str[index]);
    return;
}

/*
 * 6. Reverse the string iterative
 */
char* ReverseString(char *str) {
    if(!str) {
        return NULL;
    }
    int len = strlen(str);
    int start=0, end=len-1;
    while(start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
    return str;
}

/*
 * 7. Rotate the string anticlockwise by given shifts
 */
char* RotateString(char *str, int d) {
    // We have to rotate the string by d shifts anticlockwise
    // The algo we use is as below
    // 1. Reverse substring 0 to d
    // 2. Reverse substring d+1 to len
    // 3. Reverse entire string.
    if(!str) {
        return NULL;
    }

    int len = strlen(str);
    if(d == len) {
        return str;
    }
    
    // Reverse str from 0 to d
    int start = 0, end = d;
    while(start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }

    // Reverse str from d+1 to len
    start = d+1;
    end = len-1;
    while(start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }

    // Reverse the entire string
    start = 0;
    end = len-1;
    while(start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
    return str;
}

/*
 * 8. PATTERN SEARCH
 */

/*
 * There are many algorithms for this. Lets explore some.
 */

/*
 * Naive method where we get string and pattern to search as arguments
 * and then we place pattern on all possible positions in the string
 * and then traverse the pattern to see if it matches the string.
 *
 * Say length of string is N and length of pattern is M. M should be
 * less than or equal to N. So number of possibilities that we can put
 * pattern on the string is N-M+1. For each of these possibilities,
 * we traverse the pattern for its length of M to compare each char
 * in pattern matches the char in string or not.
 * So Complexity is O(M*(N-M+1))
 */
void PatterMatchNaive(char *str, char *pat) {
    if(!str || !pat) {
        return;
    }
    int str_len = strlen(str);
    int pat_len = strlen(pat);

    if(str_len < pat_len) {
        return;
    }
    // Traverse for all possibilities to put pattern onto string
    for(int i=0; i<(str_len-pat_len)+1; i++) {
        // For each possibility, traverse the pattern to see if all
        // chars in pattern matches the corresponding chars in str.
        int j;
        for(j=0; j<pat_len; j++) {
            if(pat[j] != str[i+j]) {
                // Mismatch.
                break;
            }
        }
        if(j == pat_len) {
            // That means we have found the pattern
            printf("Pattern is found at %d\n", i);
        }
    }
    return;
}

/*
 * KMP Pattern Search: The above method is bad in cases were the pattern has
 * many matching chars but only a few non matching chars. This is the worst case
 * in which the complexity is O(M*(N-M+1)). KMP has worst case complexity O(N) where
 * N is length of given text. In KMP, we take advantage of a fact that while traversing
 * the pattern and text, when we encounter a mismatch, then from this point of mismatch
 * backwards, there might already be some chars which already match to pattern and we
 * need not to match these again and again.
 * The idea is to preprocess pattern to find the number of prefixes that match the suffixes
 * at each index of pattern. We store this in another array say lps[].
 *
 * For building lps[], we first initialize lps[0] = 0 and len = 0 
 * then for i = 1 to length of pattern, we check if pat[i] and pat[len] matches or not.
 * Based on this, we update len, and store its val in lps[i].
 */
void ComputeLps(int *lps, char *pat, int pat_len) {
    int len = 0;
    lps[0] = 0;

    int i=1;
    while(i<pat_len) {
        if(pat[i] == pat[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if(len != 0) {
                len = lps[len-1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

void PatternMatchKMP(char *str, char *pat) {
    if(!str || !pat) {
        return;
    }
    int str_len = strlen(str);
    int pat_len = strlen(pat);

    int lps[pat_len];

    ComputeLps(lps, pat, pat_len);

    int i=0;
    int j=0;

    while(i < str_len) {
        if(pat[j] == str[i]) {
            i++;
            j++;
        }

        if(j == pat_len) {
            printf("Pattern found at %d\n", i-j);
            j = lps[j-1];
        } else if(i < str_len && pat[j] != str[i]) {
            if(j != 0) {
                j = lps[j-1];
            } else {
                i = i+1;
            }
        }
    }
}

/*
 * 9. Wildcard string matching
 */
bool WildCardMatch(char *str1, char *str2) {
    // Here str1 may have wildcard characters as below
    // * --- matches with 1 or more instances
    // ? --- matches with only current instance.
    // We have to return true if str1 and str2 match
    if(!str1 || !str2) {
        return false;
    }
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    if(len1 != len2) {
        return false;
    }

    if(*str1 == '*' && *(str1+1) != '\0' && *str2 == '\0') {
        return false;
    }

    if(*str1 == '?' || *str1 == *str2) {
        return WildCardMatch(str1+1, str2+1);
    }

    if(*str1 == '*') {
        return WildCardMatch(str1+1, str2) || WildCardMatch(str1, str2+1);
    }

    // Will never reach here
    return false;
}

int main(void) {
    /* Longest Substring with unique characters */
    char str[11] = "abbcdefagh\0";
    printf("The given string is: %s\n", str);
    int start=0, end=0;
    int len = longestSubstringWithoutDuplicates(str, &start, &end);
    printf("The length of longest substring with all unique characters is"
           " %d and the substring is from index %d to %d\n", len, start, end);

    /* Longest Palindromic substring */
    char pal[11] = "abcdefghij\0";
    printf("The given string is %s.\n", pal);
    longestPalindromeSubstring(pal);

    /* Phone Keypad print */
    char phone_str[4] = "123\0";
    PhoneKeypadProblem(phone_str);

    /* Rotation of string */
    char rotStr1[10] = "abcdefghi\0";
    char rotStr2[10] = "defghiab\0";
    if(isRotationString(rotStr1, rotStr2)) {
        printf("%s and %s are rotations of each other.\n", rotStr1, rotStr2);
    } else {
        printf("%s and %s are not rotations of each other.\n", rotStr1, rotStr2);
    }

    /* Print Reverse recursion */
    printReverseString(rotStr1, 0);
    printf("\n");

    /* Reverse the given string */
    char revstr[10] = "abcdefghi\0";
    printf("\nString before reversal is %s\n", revstr);
    char *newrevstr = ReverseString(revstr);
    printf("String after reversal is %s\n", revstr);

    /* Rotate the string */
    char rotatestr[10] = "abcdefghi\0";
    char *rotatedstr = RotateString(rotatestr, 3);
    printf("\nString after rotating anticlockwise by 3 is: %s\n", rotatedstr);

    /* Pattern Matching */
    char text[10] = "abcabcabc\0";
    char pattern[3] = "ab\0";
    printf("\n*********** Naive ***********\n");
    printf("Text is %s and Pattern is %s\n", text, pattern);
    PatterMatchNaive(text, pattern);
    printf("\n");

    printf("\n*********** KMP ***********\n");
    printf("Text is %s and Pattern is %s\n", text, pattern);
    PatternMatchKMP(text, pattern);
    printf("\n");
    
    return 0;
}
