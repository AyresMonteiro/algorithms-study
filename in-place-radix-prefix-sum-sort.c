#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <limits.h>
#include <string.h>

typedef struct bucket {
    int size;
    int currentSize;
    int * vector;
} bucket;

void print_vector(int * vector, int size) {
    for (int i = 0; i < size - 1; i++) {
        printf("%d, ", vector[i]);
    }
    
    printf("%d ", vector[size - 1]);

    printf("\n");
}

void clean_vector(int * vector) {
    if (vector != NULL) free(vector);
}

int * create_vector(int size) {
    if (size <= 0) return NULL;
    int * vector = (int *) calloc(size, sizeof(int));
    return vector;
}

int * create_random_vector(int size, int min, int max) {
    int * vector = create_vector(size);

    for (int i = 0; i < size; i++) {
        vector[i] = rand() % (max - min + 1) + min;
    }

    return vector;
}

int * copy_vector(int * vector, int originalSize, int size) {
    int * newVector = create_vector(size);

    for (int i = 0; i < originalSize; i++) {
        newVector[i] = vector[i];
    }

    return newVector;
}

void copy_vector_to(int * original, int * newVector, int size) {
    for (int i = 0; i < size; i++) {
        newVector[i] = original[i];
    }
}

void zeros_vector(int * vector, int size) {
    for (int i = 0; i < size; i++) {
        vector[i] = 0;
    }
}

int get_digit(int base, int num, int place) {
    return (num / (int) pow((int) base, (int) place)) % base;
}

int get_num_of_digits(int base, int num) {
    int i = 0;

    while (num > 0) {
        num /= base;
        i++;
    }

    return i;
}

int get_max_radix (int base, int * vector, int size) {
    int max_radix = 0, radix;

    for (int i = 0; i < size; i++) {
        radix = get_num_of_digits(base, vector[i]);

        max_radix = (max_radix + radix + abs(max_radix - radix)) / 2;
    }

    return max_radix;
}

void in_place_radix_counting_sort (int base, int * input, int size) {
    int * counting = create_vector(base);
    int * output = create_vector(size);

    zeros_vector(counting, base);

    int max_radix = get_max_radix(base, input, size);

    for(int i = 0; i < max_radix; i++) {
        for (int j = 0; j < size; j++) {
            int radix = get_digit(base, input[j], i);
            counting[radix]++;
        }

        for (int j = 1; j < base; j++) {
            counting[j] += counting[j - 1];
        }

        for (int j = size - 1; j >= 0; j--) {
            int radix = get_digit(base, input[j], i);

            output[counting[radix] - 1] = input[j];
            counting[radix]--;
        }

        copy_vector_to(output, input, size);

        zeros_vector(counting, base);
        zeros_vector(output, size);
    }

    clean_vector(counting);
    clean_vector(output);
}

int main () {
    srand(time(NULL));

    clock_t exec_start = clock();

    int base = 2048;
    int number_of_items = 10000000;
    int max = INT_MAX;

    int * vector = create_random_vector(number_of_items, 0, max);

    clock_t init = clock();

    in_place_radix_counting_sort(base, vector, number_of_items);

    clock_t end = clock();

    clean_vector(vector);

    printf(
        "Elapsed time (radix prefix sum sort, %d items, base %d, max integer %d): %f seconds\n",
        number_of_items,
        base,
        max,
        ((double) (end - init)) / CLOCKS_PER_SEC
    );

    clock_t exec_end = clock();

    printf("Execution time: %f seconds\n", ((double) (exec_end - exec_start)) / CLOCKS_PER_SEC);

    return 0;
}
