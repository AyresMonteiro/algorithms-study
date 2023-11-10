#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct array {
    int length;
    int size;
    int * vector;
} arrayi;

arrayi * arrayi_create(int size) {
    arrayi * arr = (arrayi *) malloc(sizeof(arrayi));
    arr->length = 0;
    arr->size = size;
    arr->vector = size == 0 ? NULL : (int *) calloc(size, sizeof(int));
    return arr;
}

void arrayi_push(arrayi * arr, int num) {
    if (arr->vector == NULL) {
        arr->size = 2;
        arr->length = 0;
        arr->vector = calloc(2, sizeof(int));
    }

    if (arr->length == arr->size) {
        arr->size *= 2;
        arr->vector = realloc(arr->vector, arr->size * sizeof(int));
    }

    arr->vector[arr->length] = num;
    arr->length++;
}

arrayi * arrayi_create_random(int size) {
    arrayi * arr = arrayi_create(size);

    for (int i = 0; i < size; i++) {
        arrayi_push(arr, rand() % 10);
    }

    return arr;
}

arrayi * arrayi_create_asc(int size) {
    arrayi * arr = arrayi_create(size);

    for (int i = 0; i < size; i++) {
        arrayi_push(arr, i + 1);
    }

    return arr;
}

void arrayi_print(arrayi * arr) {
    for (int i = 0; i < arr->length; i++) {
        printf("%d ", arr->vector[i]);
    }
    printf("\n");
}

void arrayi_destroy(arrayi * arr) {
    if (arr->vector != NULL) free(arr->vector);

    free(arr);
}

arrayi * arrayi_reverse (arrayi * arr) {
    arrayi * reversed = arrayi_create(arr->length);

    for (int i = arr->length - 1; i >= 0; i--) {
        arrayi_push(reversed, arr->vector[i]);
    }

    return reversed;
}

arrayi * arrayi_slice(arrayi * arr, int start, int end) {
    int size = end - start;

    arrayi * sliced = arrayi_create(size);

    for (int i = start; i < end; i++) {
        arrayi_push(sliced, arr->vector[i]);
    }

    return sliced;
}

arrayi * arrayi_convolution (arrayi * a, arrayi * b) {
    arrayi * reversed_b = arrayi_reverse(b);
    arrayi * convoluted = arrayi_create(0);

    int a_size = a->length;
    int b_size = b->length;

    for (int i = 1; i <= (a_size + b_size - 1); i++) {
        int sum = 0;

        for (int j = 0; j < i; j++) {
            int ia = j, ib = b_size - i + j;

            if (ia >= a_size || ib < 0) continue;

            sum += a->vector[ia] * reversed_b->vector[ib];
        }

        arrayi_push(convoluted, sum);
    }

    arrayi_destroy(reversed_b);

    return convoluted;
}

int main () {
    srand(time(NULL));

    arrayi * a = arrayi_create_asc(6);
    arrayi * b = arrayi_create_asc(6);

    printf("a: ");
    arrayi_print(a);
    printf("b: ");
    arrayi_print(b);

    arrayi * convoluted = arrayi_convolution(a, b);

    printf("convoluted: ");
    arrayi_print(convoluted);
    printf("convoluted length: %i\n", convoluted->length);

    arrayi_destroy(a);
    arrayi_destroy(b);
    arrayi_destroy(convoluted);

    return 0;
}
