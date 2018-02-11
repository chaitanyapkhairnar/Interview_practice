#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int main(void) {
    int a[10];
    int i, j=0, sum=0, start=0, end=0, orig_sum=4;
    bool found = false;

    printf("The array is :\n");
    for(i=0;i<10;i++) {
        a[i] = i+1;
        printf("%d\n", a[i]);
    }

    printf("The sum for the subarray we are looking for is %d\n", orig_sum);

    /* Algorithm starts here */
    start = j;
    for (i=0;i<10;i++) {
        sum = sum + a[i];
        if (sum == orig_sum) {
            end = i;
            found = true;
            break;
        }
        while (sum > orig_sum) {
            sum = sum - a[j];
            j++;
            if (sum == orig_sum) {
                start = j;
                end = i;
                found = true;
                break;
            }
        }
        if(found == true) {
            break;
        }
    }

    if(found == true) {
        printf("The start index is %d and end index is %d\n", start, end);
    } else {
        printf("Subarray with the given sum not found in the original array.\n");
    }
    return 0;
}
