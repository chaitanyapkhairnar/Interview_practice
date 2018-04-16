/*
 * This file contains the problems in Cracking the Coding Interview
 * book for different categories.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* Category 1: Strings and Arrays */

/* Is Unique: Implement an algorithm to determine if a string has all unique characters.
 *            What if you cannot use extra space?
 */

// By using extra space. Use hash table to store characters of string.
// We define hash as a boolean array of size 128 which is 128 bytes in total.
// Time complexity is O(n) and space complexity is O(n)
#define ALPHABET_SIZE 128
bool IsUniqueWithHash(char *str, int len) {
    bool hash_map[ALPHABET_SIZE] = {false};
    if(!str || len == 0) {
        printf("Empty String.\n");
        return false;
    }
    if(len == 1) {
        return true;
    } else {
        for(int i=0; i<len; i++) {
            if(hash_map[str[i]]) {
                return false;
            } else {
                hash_map[str[i]] = true;
            }
        }
        return true;
    }
}

// In previous implementation, we used 128 bytes of extra space, but we need only 128
// bits to store true or false. We can reduce the extra space used by using 4 integers
// of 4byte length each so we have 16 bytes which is 128 bits. And we use bit
// manipulation to set bits. We will use a single 4 byte integer here assuming 26
// english characters only in the given string.
bool IsUniqueWithBit(char *str, int len) {
    int hash_int = 0;
    if(!str || len == 0) {
        printf("String is empty\n");
        return false;
    }
    if(len == 1) {
        return true;
    } else {
        for(int i=0; i<len; i++) {
            // assuming all small letter english characters in str.
            // so a=0, b=1, c=2 and so on.
            int index = str[i] - 'a';
            if(hash_int & 1<<index) {
                // Duplicate found
                return false;
            } else {
                // Set the bit
                hash_int = hash_int | 1<<index;
            }
        }
        return true;
    }
}

// To check without using extra space, one approach is brute force where we compare
// each character of the string with each other character. Time complexity is O(n^2).
bool IsUniqueWithoutExtraSpace(char *str, int len) {
    if(!str || len == 0) {
        printf("String is empty.\n");
        return false;
    }
    if(len == 1) {
        return true;
    }
    for(int i=0; i<len-1; i++) {
        for(int j=i+1; j<len; j++) {
            if(str[i] == str[j]) {
                return false;
            }
        }
    }
    return true;
}

/*
 * Is Permutation: Write an algorithm to determine if one string is permutation of
 *                 the other string.
 */

// We use hash_map to store the count of characters of str 1 and then verify if str 2
// has only those characters present in str 1.
bool IsPermuteUsingHash(char *str1, int len1, char *str2, int len2) {
    // Length should be equal for them to be permutation of each other
    if(len1 != len2) {
        return false;
    }
    if(!str1 || !str2) {
        printf("Either of the string is empty.\n");
        return false;
    }
    int hash_map[ALPHABET_SIZE] = {0};
    for(int i=0; i<len1; i++) {
        hash_map[str1[i]]++;
    }
    for(int j=0; j<len2; j++) {
        hash_map[str2[j]]--;
    }
    // Now hash_map should be all 0s if str1 and str2 are permutations.
    for(int k=0; k<ALPHABET_SIZE; k++) {
        if(hash_map[k] != 0) {
            return false;
        }
    }
    return true;
}

// To reduce the extra space used, we can use bit manipulation. We use a 4 byte integer
// and while traversing the strings, we keep flapping the bit. In the end, we should
// have the integer value 0 for the strings to be permutations of each other.
bool IsPermuteUsingBit(char *str1, int len1, char *str2, int len2) {
    // Length should be equal for them to be permutation of each other
    if(len1 != len2) {
        return false;
    }
    if(!str1 || !str2) {
        printf("Either of the string is empty.\n");
        return false;
    }
    // Initialize the hash integer to 0
    int hash_map = 0;

    for(int i=0; i<len1; i++) {
        int index = str1[i] - 'a';
        // Flap the bit of hash_map at index position
        hash_map = hash_map ^ (1 << index);
    }

    for(int j=0; j<len2; j++) {
        int index = str2[j] - 'a';
        hash_map = hash_map ^ (1 << index);
    }
    if(hash_map == 0) {
        return true;
    } else {
        return false;
    }
}

/*
 * URLify: Replace all the spaces in the given string with '%20'
 */

// We assume that the given string has sufficient length to accomodate 
// all %20 replacements. We use two iterators. One is at the last character of string
// and another at the end of string. Then we move the iterator1 bottom up and for each
// iteration, we check if its a ' '. If yes, we add %20 and move iterator2. If not, we
// just copy the character at iterator1 into iterator2 position and proceed.
char* URLify(char *str, int len1, int len2) {
    // Here len1 is lenght till last char of str and len2 is till the end of str
    if(!str || len1 == 0 || len2 == 0) {
        printf("Empty string.\n");
        return str;
    }
    int i, j = len2-1;
    for(i=len1-1; i>=0; i--) {
        if(str[i] == ' ') {
            str[j] = '0';
            str[j-1] = '2';
            str[j-2] = '%';
            j = j-3;
        } else {
            str[j] = str[i];
            j--;
        }
    }
    return str;
}

/*
 * Palindrome Permute: Given a string, determine if it is a permutation of a
 *                     Palindrome or not.
 */

// A string can be a Palindrome if it has all the characters with even count of
// occurance and atmost 1 character with odd count of characters. We simply traverse
// the string and store the count of each character in Hash Map. Then we traverse
// the Hash map and check if we have only 1 character with odd count and all other
// characters with even count. Another optimized way is to maintain a OddCount variable
// and increment it whenever the hash map value is changed to odd value and decrement
// it whenever the hash map value is changed to even. In the end the count should be 1
// or 0 for the string to be a permutation of palindrome.
bool IsPalindromePermute(char *str, int len) {
    if(len == 0) {
        printf("Empty String\n");
        return false;
    }
    if(len == 1) {
        return true;
    }
    int OddCount=0;
    int hash_map[ALPHABET_SIZE] = {0};

    for(int i=0; i<len; i++) {
        hash_map[str[i]]++;
        if(hash_map[str[i]]%2) {
            OddCount++;
        } else {
            OddCount--;
        }
    }
    if(OddCount == 0 || OddCount == 1) {
        return true;
    } else {
        return false;
    }
}

int main(void) {
    char str1[11] = "aaaaabbbba\0";
    char str2[11] = "ababababab\0";
    char str3[21] = "My Name Is Ram      \0";

/*    if(IsUniqueWithHash(str1, 10)) {
        printf("The string has all unique characters. Verified using hash.\n");
    } else {
        printf("The string has duplicates. Verified using hash.\n");
    }
    if(IsUniqueWithBit(str1, 10)) {
        printf("The string has all unique characters. Verified using bits.\n");
    } else {
        printf("The string has duplicates. Verified using bits.\n");
    }
    if(IsUniqueWithoutExtraSpace(str1, 10)) {
        printf("The string has all unique characters. Verified using no xtra space.\n");
    } else {
        printf("The string has duplicates. Verified using no xtra space.\n");
    }

    if(IsPermuteUsingHash(str1, 10, str2, 10)) {
        printf("Both strings are permutations of each other. Verified using hash.\n");
    } else {
        printf("Both strings are not permutations. Verified using hash.\n");
    }
    if(IsPermuteUsingBit(str1, 10, str2, 10)) {
        printf("Both strings are permutations of each other. Verified using bits.\n");
    } else {
        printf("Both strings are not permutations. Verified using bits.\n");
    }

    printf("String %s after URLify is %s\n", str3, URLify(str3, 14, 20));
*/
    if(IsPalindromePermute(str1, 10)) {
        printf("The String %s is a Palindrome Permute\n", str1);
    } else {
        printf("The String %s is not a Palindrome Permute\n", str1);
    }

    return 0;
}
