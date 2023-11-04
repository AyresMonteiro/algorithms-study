#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <limits.h>

typedef struct bucket {
    int size;
    int * vector;
} bucket;

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

int * push_vector(int * original, int size, int num) {
    int * newVector = copy_vector(original, size, size + 1);
    clean_vector(original);
    newVector[size] = num;
    return newVector;
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

bucket * create_buckets(int base) {
    bucket * buckets = (bucket *) calloc(base, sizeof(bucket));

    for (int i = 0; i < base; i++) {
        buckets[i].size = 0;
        buckets[i].vector = NULL;
    }

    return buckets;
}

void clean_buckets(bucket * buckets, int base) {
    for (int i = 0; i < base; i++) {
        clean_vector(buckets[i].vector);
    }

    free(buckets);
}

void radix_sort (int base, int * vector, int size) {
    int max_radix = get_max_radix(base, vector, size);

    for(int i = 0; i < max_radix; i++) {
        bucket * buckets = create_buckets(base);

        for (int j = 0; j < size; j++) {
            int radix = get_digit(base, vector[j], i);

            buckets[radix].vector = push_vector(buckets[radix].vector, buckets[radix].size, vector[j]);
            buckets[radix].size++;
        }

        int k = 0;

        for (int j = 0; j < base; j++) {
            for (int l = 0; l < buckets[j].size; l++) {
                vector[k] = buckets[j].vector[l];
                k++;
            }
        }

        clean_buckets(buckets, base);
    }
}

void print_vector(int * vector, int size) {
    for (int i = 0; i < size - 1; i++) {
        printf("%d, ", vector[i]);
    }
    
    printf("%d ", vector[size - 1]);

    printf("\n");
}

void print_line() {
    printf("\n\n\n--------------------------------------------------\n\n\n");
}

int main () {
    srand(time(NULL));

    int base = 512;
    int number_of_items = 100000;
    int max = 1000;

    int * vector = create_random_vector(number_of_items, 0, max);

    print_vector(vector, number_of_items);

    print_line();

    radix_sort(base, vector, number_of_items);

    print_vector(vector, number_of_items);

    clean_vector(vector);

    return 0;
}
