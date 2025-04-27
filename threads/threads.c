#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define NUM_THREADS 4
#define NUM_LINES 5

void cleanup_handler(void* arg){
    printf("Поток %ld: завершение\n", pthread_self());
}

void* child_thread(void* arg){
    for (int i = 0; i < 5; i++){
        printf("Дочерний поток: строка %d\n", i + 1);
    }
    return NULL;
}

void* print_strings(void* arg){
    pthread_cleanup_push(cleanup_handler, NULL); //указ-ль на ф-ию чей вызов необходимо добавить в стек, арг ф-ии

    char** strings = (char**)arg;
    for (int i = 0; i < NUM_LINES; i++){
        printf("Поток %ld: %s\n", pthread_self(), strings[i]);
        sleep(1);
    }

    pthread_cleanup_pop(0); //обработчик прерывания потока, 0 - не требуется выполнение
    return NULL;
}

int main(){
    pthread_t threads[NUM_THREADS];

    char* strings[NUM_THREADS][NUM_LINES] = {
        {"Поток 1: строка 1", "Поток 1: строка 2", "Поток 1: строка 3", "Поток 1: строка 4", "Поток 1: строка 5"},
        {"Поток 2: строка 1", "Поток 2: строка 2", "Поток 2: строка 3", "Поток 2: строка 4", "Поток 2: строка 5"},
        {"Поток 3: строка 1", "Поток 3: строка 2", "Поток 3: строка 3", "Поток 3: строка 4", "Поток 3: строка 5"},
        {"Поток 4: строка 1", "Поток 4: строка 2", "Поток 4: строка 3", "Поток 4: строка 4", "Поток 4: строка 5"}
    };

    for (int i = 0; i < NUM_THREADS; i++){
        if (pthread_create(&threads[i], NULL, print_strings, strings[i]) != 0){
            printf("Ошибка создания потока\n");
            return 1;
        }
    }

    for (int i = 0; i < 5; i++){
        printf("Родительский поток: строка %d\n", i + 1);
    }

    sleep(2);

    for (int i = 0; i < NUM_THREADS; i++){
        pthread_cancel(threads[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++){
        pthread_join(threads[i], NULL);
    }

    printf("Все потоки завершены\n");

    return 0;
}
