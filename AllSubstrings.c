#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


void SubStrings(char *str, int len) {
    for(int curr_start=0; curr_start<len; curr_start++) {
        for(int curr_end=curr_start+1; curr_end<len+1; curr_end++) {
            for(int j=curr_start; j<curr_end; j++) {
                printf("%c", str[j]);
            }
            printf("\n");
        }
    }
}

int main(void) {
    char *str = "abcdefgh ";
    printf("All the substrings are:\n");
    SubStrings(str, 9);

    return 0;
}

