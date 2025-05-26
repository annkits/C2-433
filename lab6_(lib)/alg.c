#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "alg.h"

struct Student addStudent(char *name, int math, int physics, int cs) {
    struct Student newStudent;
    strncpy(newStudent.name, name, 63);
    newStudent.name[63] = '\0';
    newStudent.math = math;
    newStudent.physics = physics;
    newStudent.cs = cs;
    newStudent.total = math + physics + cs;
    return newStudent;
}

// void printStudentInfo(struct Student student) {
//     printf("Имя: %s, Математика: %d, Физика: %d, Информатика: %d, Общий балл: %d\n", 
//            student.name, student.math, student.physics, student.cs, student.total);
// }

unsigned long long int CheckSum(struct Student arr[], int size) {
    unsigned long long int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i].total;
    }
    printf("Контрольная сумма: %lld\n", sum);
    return sum;
}

int RunNumber(struct Student arr[], int size) {
    if (size <= 1) return size == 0 ? 0 : 1;
    int cnt = 1;
    for (int i = 0; i < size - 1; i++) {
        if (arr[i].total <= arr[i + 1].total) {
            cnt++;
        }
    }
    printf("Количество серий: %d\n", cnt);
    return cnt;
}

void SelectionSort(struct Student arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        int j_max = i;
        for (int j = i + 1; j < size; j++) {
            if (arr[j].total > arr[j_max].total) {
                j_max = j;
            }
        }
        struct Student temp = arr[i];
        arr[i] = arr[j_max];
        arr[j_max] = temp;
    }
}

void CountingSort(struct Student arr[], int size) {
    struct Student *output = (struct Student *)calloc(size, sizeof(struct Student));
    int count[MAX_TOTAL] = {0};

    for (int i = 0; i < size; i++) {
        count[arr[i].total]++;
    }

    for (int i = MAX_TOTAL - 2; i >= 0; i--) {
        count[i] += count[i + 1];
    }

    for (int i = size - 1; i >= 0; i--) {
        output[count[arr[i].total] - 1] = arr[i];
        count[arr[i].total]--;
    }

    for (int i = 0; i < size; i++) {
        arr[i] = output[i];
    }

    free(output);
}

void QuickSort(struct Student arr[], int left, int right) {
    if (left < right) {
        int pivot_ind = left + rand() % (right - left + 1);
        struct Student temp = arr[pivot_ind];
        arr[pivot_ind] = arr[right];
        arr[right] = temp;

        struct Student pivot = arr[right];
        int l = left;
        int r = right - 1;

        while (1) {
            while (l <= r && arr[l].total > pivot.total) l++;
            while (r >= l && arr[r].total < pivot.total) r--;
            if (l >= r) break;

            struct Student temp = arr[l];
            arr[l] = arr[r];
            arr[r] = temp;
            l++;
            r--;
        }

        arr[right] = arr[l];
        arr[l] = pivot;

        QuickSort(arr, left, l - 1);
        QuickSort(arr, l + 1, right);
    }
}

void PrintCPUInfo() {
    printf("\nИнформация о процессоре:\n");
    system("cat /proc/cpuinfo | grep 'model name' | head -1");
    system("cat /proc/cpuinfo | grep 'cpu MHz' | head -1");
}