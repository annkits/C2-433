#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int** A;
    int** B;
    int** C;
    int N;
    int start_row;
    int end_row;
} ThreadData;

void* matrix_multiply(void* arg){
    ThreadData* data = (ThreadData*)arg;
    for (int i = data->start_row; i < data->end_row; i++){
        for (int j = 0; j < data->N; j++){
            data->C[i][j] = 0;
            for (int k = 0; k < data->N; k++){
                data->C[i][j] += data->A[i][k] * data->B[k][j];
            }
        }
    }
    return NULL;
}

void print_matrix(int** matrix, int N, const char* name){
    printf("Матрица %s:\n", name);
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char* argv[]){
    if (argc != 3){
        printf("Использование: %s <размер матрицы> <число потоков>\n", argv[0]);
        return 1;
    }

    int N = atoi(argv[1]);
    int num_threads = atoi(argv[2]);

    int** A = malloc(N * sizeof(int*));
    int** B = malloc(N * sizeof(int*));
    int** C = malloc(N * sizeof(int*));
    for (int i = 0; i < N; i++){
        A[i] = malloc(N * sizeof(int));
        B[i] = malloc(N * sizeof(int));
        C[i] = malloc(N * sizeof(int));
    }

    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            A[i][j] = 1;
            B[i][j] = 1;
            C[i][j] = 0;
        }
    }

    if (N < 5){
        print_matrix(A, N, "A");
        print_matrix(B, N, "B");
    }

    pthread_t* threads = malloc(num_threads * sizeof(pthread_t)); //массив pthread_t
    ThreadData* thread_data = malloc(num_threads * sizeof(ThreadData)); //по структуре на поток

    int rows_per_thread = N / num_threads;
    int remaining_rows = N % num_threads;

    for (int i = 0; i < num_threads; i++){
        thread_data[i].A = A;
        thread_data[i].B = B;
        thread_data[i].C = C;
        thread_data[i].N = N;
        thread_data[i].start_row = i * rows_per_thread;
        thread_data[i].end_row = (i + 1) * rows_per_thread;
        if (i == num_threads - 1){
            thread_data[i].end_row += remaining_rows;
        }
        pthread_create(&threads[i], NULL, matrix_multiply, &thread_data[i]);
    }

    for (int i = 0; i < num_threads; i++){
        pthread_join(threads[i], NULL);
    }

    if (N < 5){
        print_matrix(C, N, "C");
    }

    for (int i = 0; i < N; i++){
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }

    free(A);
    free(B);
    free(C);
    free(threads);
    free(thread_data);

    return 0;
}