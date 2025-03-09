#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define N 100000
#define MAX_TOTAL 301
#define CHECK 5

//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa

void SelectionSort(struct Student arr[]){
    for (int i = 0; i < size - 1; i++){
        int j_max = i;
        for (int j = i + 1; j < size; j++){
            if (arr[j].total > arr[j_max].total){
                j_max = j;
            }
        }
        struct Student temp = arr[i];
        arr[i] = arr[j_max];
        arr[j_max] = temp;
        memset(&temp, 0, sizeof(struct Student));
    }
}

int main(){
    int a[] = {4, 2};
    int b = SelectionSort(a);
}