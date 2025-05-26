#include <stdio.h>
#include <stdlib.h>
#include "index_array.h"

int create_array(int **array, int size) {
    if (size <= 0) return -1;
    *array = (int *)malloc(size * sizeof(int));
    if (*array == NULL) return -1;
    for (int i = 0; i < size; i++) {
        (*array)[i] = 0;
    }
    return 0;
}

void free_array(int **array) {
    if (*array != NULL) {
        free(*array);
        *array = NULL;
    }
}

int insert_element(int *array, int *size, int index, int value) {
    if (index < 0 || index > *size) return -1;
    if (*size >= MAX_SIZE) return -1;
    
    for (int i = *size; i > index; i--) {
        array[i] = array[i - 1];
    }
    array[index] = value;
    (*size)++;
    return 0;
}

int delete_element(int *array, int *size, int index) {
    if (index < 0 || index >= *size) return -1;
    for (int i = index; i < *size - 1; i++) {
        array[i] = array[i + 1];
    }
    (*size)--;
    return 0;
}