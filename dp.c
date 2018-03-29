/*
 * This file contains all the problems and descriptions
 * regarding Dynamic Programming.
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * There are two ways in Dynamic Programming:
 * 1. Memoization
 * 2. Tabulation
 *
 * Memoization can also be said as Top Bottom approach. It is exactly same as
 * recursion but the only difference is, we maintain a lookup table to avoid
 * calculations again and again. See below Fibonacci example using Memoization
 *
 * Tabulation can also be said as Bottom Up approach. Here we DO NOT use
 * recursion but use iterative method instead. The idea is to build a table
 * of all the values starting from bottom and working our way up. Then the only
 * job is to return the value of table at a particular index which is the solution.
 * See below Fibonacci example using Tabulation.
 */

// This is recursive method, here say for input = 5, the recursion tree will be
//         5
//       3   4
//     1  2 2  3
//       1 1  1  2
//              1
// We are calculating fibonacci for 1,2,3 multiple times. We can avoid this
// using dp.
int get_fibonacci(int input) {
    if (input <= 1) {
        return input;
    } else {
        return get_fibonacci(input-1) + get_fibonacci(input-2);
    }
}

// Memoization: Here we will have same recursive call, but we will
// maintain a lookup table for previously calculated values.
int lookup_table[input+1] = {-1};

int get_fibonacci_memoization(int input) {
    if(lookup_table[input] < 0) {
        if(input <= 1) {
            lookup_table[input] = input;
        } else {
            lookup_table[input] = get_fibonacci_memoization(input-1) +
                                  get_fibonacci_memoization(input-2);
        }
    }
    return (lookup_table[input]);
}

// Tabulation: Here we will build a table from bottom up. i.e. we start
// filling values in the table for i=0, then i=1, then i=2 and so on.
// Finally when we have table filled for i=input, we return the value
// at this index which is our answer.
int tabulation_table[input+1] = {-1};

int get_fibonacci_tabulation(int input) {
    tabulation_table[0] = 0;
    tabulation_table[1] = 1;
    for(int i=2; i<=input; i++) {
        tabulation_table[i] = tabulation_table[i-1] + tabulation_table[i-2];
    }
    return tabulation_table[input];
}

/************************************************************************************/

/* Some more examples on DP. */

/* Ugly number is the number whose only prime factors are 2, 3 or 5.
 * Given a number n, return the nth ugly number. Number 1 is considered
 * as ugly number.
 */

/*
 * First we see straight forward method, where we iterate through each
 * number and check if its ugly or not. We keep doing it till we get
 * nth ugly number. We are storing each number in table.
 */
int max_divide(int number, int divisor) {
    while(number%divisor == 0) {
        number = number/divisor;
    }
    return number;
}

int get_ugly(int n) {
    int ugly_table[n+1] = {-1};
    ugly_table[0] = 1;
    int j=1;
    for(int i=2; i<=n; i++) {
        /* A number will be ugly only if when it is divided by 2 as many times
         * as it can, then by 3 as many times as it can, then by 5 as many
         * times as it can, it becomes 1.
         */
        int temp = max_divide(i, 2);
        temp = max_divide(temp, 3);
        temp = max_divide(temp, 5);
        if(temp == 1) {
            ugly_table[j] = i;
            j++;
        }
    }
    return ugly_table[n-1];
}

/*
 * Now we see dynamic programming approach. We try to build the ugly_table
 * not by iterating each number, but by iterating from 0 to n and in each iteration
 * we store the next ugly number in table.
 *
 * From the ugly number sequence, we see that first ugly number is 1 and then the
 * next ugly number is min(1*2, 1*3, 1*5) = 2, and then the next is min(2*2, 2*3, 2*5)
 * and so on. This way we fill the table and get the solution in O(n).
 */

int get_ugly_dp(int n) {
    int ugly_table[n] = {-1};
    ugly_table[0] = 1;
    int i2, i3, i5 = 0;
    int multiple_2 = ugly_table[i2]*2;
    int multiple_3 = ugly_table[i3]*3;
    int multiple_5 = ugly_table[i5]*5;

    for(int i=1; i<=n; i++) {
        ugly_table[i] = min(multiple_2, multiple_3, multiple_5);
        if(ugly_table[i] == multiple_2) {
            i2++;
            multiple_2 = ugly_table[i2]*2;
        } else if(ugly_table[i] == multiple_3) {
            i3++;
            multiple_3 = ugly_table[i3]*3;
        } else {
            i5++;
            multiple_5 = ugly_table[i5]*5;
        }
    }
    return ugly_table[n];
}

