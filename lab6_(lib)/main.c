#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "alg.h"

int main() {
    struct Student students[N];
    srand(time(NULL));

    for (int i = 0; i < N; i++) {
        char name[64];
        snprintf(name, 64, "Студент %d", i + 1);
        students[i] = addStudent(name, rand() % 101, rand() % 101, rand() % 101);
        // printStudentInfo(students[i]);
    }

    CheckSum(students, N);
    RunNumber(students, N);

    printf("\n");

    clock_t start = clock();

    if (CHECK == 0) {
        SelectionSort(students, N);
    } else if (CHECK == 1) {
        CountingSort(students, N);
    } else {
        QuickSort(students, 0, N - 1);
    }

    clock_t end = clock();
    double time_taken = difftime(end, start) / CLOCKS_PER_SEC;

    CheckSum(students, N);
    RunNumber(students, N);

    // for (int i = 0; i < N; i++) {
    //     printStudentInfo(students[i]);
    // }

    PrintCPUInfo();

    printf("\nВремя сортировки: %.6f секунд для %d данных\n", time_taken, N);

    return 0;
}