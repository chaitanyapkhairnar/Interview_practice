#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool check_sanity(char input) {
    if((input != 'i') || (input != 'I') || (input != 'v') ||
       (input != 'V') || (input != 'x') || (input != 'X') ||
       (input != 'l') || (input != 'L') || (input != 'c') ||
       (input != 'C') || (input != 'd') || (input != 'D') ||
       (input != 'm') || (input != 'M')) {
        return false;
    } else {
        return true;
    }
}

int main(void) {
    
    char *input = NULL;
    int c = EOF, n=0;
    int size_block = 5;
    int current_size = size_block;

    /* Dynamically allocate memory to input string starting
     * with a size of 5. If while reading the input, we need
     * extra space, we will dynamically increase the size
     */
    input = (char *)malloc(size_block);

    printf("Enter the number in Roman format\n");
    while((c = getchar()) != '\n' && c != EOF) {
        input[n] = (char)c;
        if(!check_sanity(input[n])) {
            printf("\nInvalid Roman character entered. ABORTING\n");
            return 0;
        }
        n++;
        /* If the size of the input reached size_block,
         * realloc size.
         */
        if (n == size_block) {
            current_size = current_size + size_block;
            input = realloc(input, current_size);
        }
    }
    input[n] = '\0';
}
