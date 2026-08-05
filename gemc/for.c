#include <stdio.h>
#include <stdlib.h>

#define CEILING_LIMIT 100000000ULL

void print_sample(const unsigned long long *arr, unsigned long long size) {
    /* Print boundary samples to avoid flooding the mobile screen */
    printf("First element: %llu\n", arr[0]);
    printf("Middle element: %llu\n", arr[size / 2]);
    printf("Ceiling element: %llu\n", arr[size - 1]);
}

int main(void) {
    unsigned long long i;
    unsigned long long sum = 0;
    
    /* Dynamically request a massive block for 100 million elements */
    unsigned long long *numbers = (unsigned long long *)malloc(CEILING_LIMIT * sizeof(unsigned long long));
    
    if (numbers == NULL) {
        printf("Allocation failed! Reduce CEILING_LIMIT for this device profile.\n");
        return 1;
    }

    printf("Filling array up to %llu elements...\n", CEILING_LIMIT);
    
    for (i = 0; i < CEILING_LIMIT; i++) {
        numbers[i] = i + 1;
        sum += numbers[i];
    }

    print_sample(numbers, CEILING_LIMIT);
    printf("Maximum calculated sum: %llu\n", sum);

    free(numbers);
    return 0;
}