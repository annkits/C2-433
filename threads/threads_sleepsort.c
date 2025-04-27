#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void* sleep_and_print(void* arg){
    int value = *(int*)arg;
    sleep(value);
    printf("%d\n", value);
    return NULL;
}

int main(){
    int arr[25];

    for (int i = 0; i < 25; i++){
        arr[i] = rand()%50;
    }

    pthread_t threads[25];

    for (int i = 0; i < 25; i++){
        if (pthread_create(&threads[i], NULL, sleep_and_print, &arr[i]) != 0){
            printf("Ошибка создания потока\n");
            return 1;
        }
    }

    for (int i = 0; i < 25; i++){
        pthread_join(threads[i], NULL);
    }
}