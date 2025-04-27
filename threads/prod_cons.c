#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define QUEUE_SIZE 10
#define NUM_CLIENTS 3
#define NUM_SERVERS 2

struct fifo {
    char* messages[QUEUE_SIZE];
    int head;
    int tail;
    int count;
    pthread_mutex_t mutex;
    pthread_cond_t not_full;
    pthread_cond_t not_empty;
};

void fifo_init(struct fifo* f) {
    f->head = 0;
    f->tail = 0;
    f->count = 0;
    for (int i = 0; i < QUEUE_SIZE; i++) {
        f->messages[i] = NULL;
    }
    pthread_mutex_init(&f->mutex, NULL);
    pthread_cond_init(&f->not_full, NULL);
    pthread_cond_init(&f->not_empty, NULL);
}

void fifo_put(struct fifo* f, char* msg) {
    pthread_mutex_lock(&f->mutex);
    while (f->count == QUEUE_SIZE) {
        pthread_cond_wait(&f->not_full, &f->mutex);
    }

    f->messages[f->tail] = strdup(msg);
    f->tail = (f->tail + 1) % QUEUE_SIZE;
    f->count++;
    pthread_cond_signal(&f->not_empty);
    pthread_mutex_unlock(&f->mutex);
}

void fifo_get(struct fifo* f, char** msg) {
    pthread_mutex_lock(&f->mutex);
    while (f->count == 0) {
        pthread_cond_wait(&f->not_empty, &f->mutex);
    }

    *msg = f->messages[f->head];
    f->messages[f->head] = NULL;
    f->head = (f->head + 1) % QUEUE_SIZE;
    f->count--;
    pthread_cond_signal(&f->not_full);
    pthread_mutex_unlock(&f->mutex);
}

void* client(void* arg) {
    struct fifo* f = (struct fifo*)arg;
    char msg[50]; // Ограничиваем длину имени клиента до 50 символов
    snprintf(msg, sizeof(msg), "Клиент %ld", pthread_self());

    for (int i = 0; i < 5; i++) {
        char message[256]; // Увеличиваем размер буфера message
        snprintf(message, sizeof(message), "Сообщение %d от %s", i + 1, msg);
        fifo_put(f, message);
        printf("[Отправлено] %s\n", message);
        usleep(rand() % 1000000);
    }
    return NULL;
}

void* server(void* arg) {
    struct fifo* f = (struct fifo*)arg;
    char* message;

    for (int i = 0; i < 5; i++) {
        fifo_get(f, &message);
        printf("[Сервер %ld] %s\n", pthread_self(), message);
        free(message);
        usleep(rand() % 2000000);
    }
    return NULL;
}

int main() {
    srand(time(NULL));
    struct fifo f;
    fifo_init(&f);

    pthread_t clients[NUM_CLIENTS];
    pthread_t servers[NUM_SERVERS];

    for (int i = 0; i < NUM_CLIENTS; i++) {
        pthread_create(&clients[i], NULL, client, &f);
    }
    for (int i = 0; i < NUM_SERVERS; i++) {
        pthread_create(&servers[i], NULL, server, &f);
    }

    for (int i = 0; i < NUM_CLIENTS; i++) {
        pthread_join(clients[i], NULL);
    }
    for (int i = 0; i < NUM_SERVERS; i++) {
        pthread_join(servers[i], NULL);
    }

    for (int i = 0; i < QUEUE_SIZE; i++) {
        if (f.messages[i] != NULL) {
            free(f.messages[i]);
        }
    }
    pthread_mutex_destroy(&f.mutex);
    pthread_cond_destroy(&f.not_full);
    pthread_cond_destroy(&f.not_empty);
    return 0;
}