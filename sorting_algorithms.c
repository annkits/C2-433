#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define N 100000
#define MAX_TOTAL 301
#define CHECK 5

struct Student{
    char name[64];
    int math;
    int physics;
    int cs;
    int total;
};

struct Student addStudent(char *name, int math, int physics, int cs){
    struct Student newStudent;
    strncpy(newStudent.name, name, 63);
    newStudent.name[63] = '\0';
    newStudent.math = math;
    newStudent.physics = physics;
    newStudent.cs = cs;
    newStudent.total = math + physics + cs;
    return newStudent;
}

void printStudentInfo(struct Student student){
    printf("Имя: %s, Математика: %d, Физика: %d, Информатика: %d, Общий балл: %d\n", student.name, student.math, student.physics, student.cs, student.total);   
}

//подсчёт контрольной суммы элементов массива А
unsigned long long int CheckSum(struct Student arr[], int size){
    unsigned long long int sum = 0;
    for (int i = 0; i < size; i++){
        sum += arr[i].total;
    }
    printf("Контрольная сумма: %lld\n", sum);
    return sum;
}

//подсчёт серий в массиве А
int RunNumber(struct Student arr[], int size){
    if (size == 0) return 0;
    int cnt = 1;
    for (int i = 1; i < size; i++){
        if (arr[i].total >= arr[i + 1].total){
            cnt++;
        }
    }
    printf("Количество серий: %d\n", cnt);
    return cnt;
}

void SelectionSort(struct Student arr[], int size){
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

void CountingSort(struct Student arr[], int size){
    struct Student *output = (struct Student *)calloc(size, sizeof(struct Student));
    int count[MAX_TOTAL] = {0};

    for (int i = 0; i < size; i++){ //цикл считает, сколько студентов имеют каждый возможный балл
        count[arr[i].total]++;
    }

    for (int i = MAX_TOTAL - 2; i >= 0; i--){ //цикл преобразует массив частот в позиции студентов в списке
        count[i] += count[i + 1];
    }

    for (int i = size - 1; i >= 0; i--){ //цикл размещает эл-ты по убыванию
        output[count[arr[i].total] - 1] = arr[i];
        count[arr[i].total]--;
    }

    for (int i = 0; i < size; i++){
        arr[i] = output[i];
    }

    free(output);
}

void PrintCPUInfo(){
    printf("\nИнформация о процессоре:\n");
    system("cat /proc/cpuinfo | grep 'model name' | head -1");
    system("cat /proc/cpuinfo | grep 'cpu MHz' | head -1");
}

void QuickSort(struct Student arr[], int left, int right){
    if (left < right){
        int pivot_ind = left + rand() % (right - left + 1); //выбор случайного опорного элемента
        struct Student temp = arr[pivot_ind];
        arr[pivot_ind] = arr[right];
        arr[right] = temp;

        struct Student pivot = arr[right];

        int l = left; //поиск эл-в меньше pivot
        int r = right - 1; //поиск эл-в больше pivot

        while (1){
            while (l <= r && arr[l].total > pivot.total) l++; //пропуск эл-в, к-е больше pivot
            while (r >= l && arr[r].total < pivot.total) r--; //пропуск эл-в, к-е меньше pivot
            if (l >= r) break;

            struct Student temp = arr[l]; //если l < r, меняем местами эл-ы
            arr[l] = arr[r];
            arr[r] = temp;
            l++;
            r--;
        }

        arr[right] = arr[l]; //ставим pivot на место, куда дошла левая граница
        arr[l] = pivot;

        QuickSort(arr, left, l - 1);
        QuickSort(arr, l + 1, right);
    }
}

int main(){
    struct Student students[N];
    srand(time(NULL));

    for (int i = 0; i < N; i++){
        char name[64];
        snprintf(name, 64, "Студент %d", i + 1);
        students[i] = addStudent(name, rand()%101, rand()%101, rand()%101);
        printStudentInfo(students[i]);
    }

    CheckSum(students, N);
    RunNumber(students, N);

    printf("\n");

    clock_t start = clock();

    if (CHECK == 0){
        SelectionSort(students, N);
    } else if (CHECK == 1){
        CountingSort(students, N);
    } else {
        QuickSort(students, 0, N - 1);
    }
    
    clock_t end = clock();
    double time_taken = difftime(end, start) / CLOCKS_PER_SEC;

    CheckSum(students, N);
    RunNumber(students, N);

    for (int i = 0; i < N; i++){
        printStudentInfo(students[i]);
    }

    PrintCPUInfo();

    printf("\nВремя сортировки: %.6f секунд для %d данных\n", time_taken, N);

    return 0;

}