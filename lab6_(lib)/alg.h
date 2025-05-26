#ifndef STUDENT_H
#define STUDENT_H

#define N 100000
#define MAX_TOTAL 301
#define CHECK 5

struct Student {
    char name[64];
    int math;
    int physics;
    int cs;
    int total;
};

struct Student addStudent(char *name, int math, int physics, int cs);
void printStudentInfo(struct Student student);
unsigned long long int CheckSum(struct Student arr[], int size);
int RunNumber(struct Student arr[], int size);
void SelectionSort(struct Student arr[], int size);
void CountingSort(struct Student arr[], int size);
void QuickSort(struct Student arr[], int left, int right);
void PrintCPUInfo(void);

#endif