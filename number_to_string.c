/*
 * This file contains function which given a number
 * returns its string representation.
 */

#include <stdio.h>
#include <stdlib.h>

/* Define an array of strings for string representation
 * of digits at units place.
 */
char units[10][6] = {{"zero"},
                     {"one"},
                     {"two"},
                     {"three"},
                     {"four"},
                     {"five"},
                     {"six"},
                     {"seven"},
                     {"eight"},
                     {"nine"}};

/*
 * Define an array of strings for 10 to 19
 */
char teen[9][20] =      {{""},
                        {"eleven"},
                        {"twelve"},
                        {"thirteen"},
                        {"fourteen"},
                        {"fifteen"},
                        {"sixteen"},
                        {"seventeen"},
                        {"eighteen"},
                        {"nineteen"}};

/* Define an array of strings for string representation
 * of digits at tens place.
 */
char tens[10][7] = {{""},
                    {"ten"},
                    {"twenty"},
                    {"thirty"},
                    {"fourty"},
                    {"fifty"},
                    {"sixty"},
                    {"seventy"},
                    {"eighty"},
                    {"ninty"}};

/* Define an array of strings for string representation
 * for hundreds, thousands, etc.
 */
char denomination[4][9] = {{""},
                           {"hundred"},
                           {"thousand"},
                           {"million"},
                           {"billion"}};

/*
 * This function will seperate the digits on the given number and store it
 * in an array. Then we parse the array to print the string representation
 * of this number.
 */
char* get_string(long long int number) {
    int digits[15];
    int index=0;

    while(number) {
        digits[index] = number%10;
        index++;
        number = number/10;
    }

