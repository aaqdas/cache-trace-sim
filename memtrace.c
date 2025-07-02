#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

int main() {
    int* array = malloc(SIZE * sizeof(int));
    if (!array) {
        perror("malloc failed");
        return 1;
    }

    // Write to array
    for (int i = 0; i < SIZE; i++) {
        array[i] = i * 2;
    }

    // Read from array
    int sum = 0;
    for (int i = 0; i < SIZE; i++) {
        sum += array[i];
    }

    printf("Sum: %d\n", sum);

    free(array);
    return 0;
}
