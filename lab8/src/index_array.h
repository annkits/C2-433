#ifndef INDEX_ARRAY_H
#define INDEX_ARRAY_H

#define MAX_SIZE 100

int create_array(int **array, int size);
void free_array(int **array);
int insert_element(int *array, int *size, int index, int value);
int delete_element(int *array, int *size, int index);

#endif