#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <ctype.h>
#include "vigenere.h"

const char *ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ";

// Структура ждя передачи данных в потоки
typedef struct {
    const char *text; // Указатель на входной текст
    const char *key; // Указатель на ключ
    char *result; // Указатель на массив результатов
    int start;
    int end;
    int key_len;
    int is_encrypt; // 1 - шифровать, 0 - дешифровать
} ThreadData;

int char_to_index(char c) {
    if (c == ' ') return 26;
    c = toupper(c);
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (ALPHABET[i] == c) return i;
    }
    return -1;
}

char index_to_char(int index) {
    if (index >= 0 && index < ALPHABET_SIZE) return ALPHABET[index];
    return '\0';
}

void *thread_process(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    for (int i = data->start; i < data->end; i++) {
        int text_idx = char_to_index(data->text[i]);
        if (text_idx == -1) {
            data->result[i] = data->text[i];
            continue;
        }
        int key_idx = char_to_index(data->key[i % data->key_len]); // Циклическое повторение ключа
        if (key_idx == -1) continue;
        int new_idx = data->is_encrypt ? (text_idx + key_idx) % ALPHABET_SIZE : (text_idx - key_idx + ALPHABET_SIZE) % ALPHABET_SIZE;
        data->result[i] = index_to_char(new_idx);
    }
    return NULL;
}

char *encrypt(const char *text, const char *key, int text_len, int key_len) {
    char *result = (char *)malloc(text_len + 1);
    if (!result) return NULL;
    for (int i = 0; i < text_len; i++) {
        int text_idx = char_to_index(text[i]);
        if (text_idx == -1) {
            result[i] = text[i];
            continue;
        }
        int key_idx = char_to_index(key[i % key_len]);
        if (key_idx == -1) {
            result[i] = text[i];
            continue;
        }
        result[i] = index_to_char((text_idx + key_idx) % ALPHABET_SIZE);
    }
    result[text_len] = '\0';
    return result;
}

char *decrypt(const char *text, const char *key, int text_len, int key_len) {
    char *result = (char *)malloc(text_len + 1);
    if (!result) return NULL;
    for (int i = 0; i < text_len; i++) {
        int text_idx = char_to_index(text[i]);
        if (text_idx == -1) {
            result[i] = text[i];
            continue;
        }
        int key_idx = char_to_index(key[i % key_len]);
        if (key_idx == -1) {
            result[i] = text[i];
            continue;
        }
        result[i] = index_to_char((text_idx - key_idx + ALPHABET_SIZE) % ALPHABET_SIZE);
    }
    result[text_len] = '\0';
    return result;
}

char *parallel_encrypt(const char *text, const char *key, int text_len, int key_len) {
    char *result = (char *)malloc(text_len + 1);
    if (!result) return NULL;
    pthread_t threads[THREAD_COUNT];
    ThreadData thread_data[THREAD_COUNT];
    int chunk_size = text_len / THREAD_COUNT;
    for (int i = 0; i < THREAD_COUNT; i++) {
        thread_data[i].text = text;
        thread_data[i].key = key;
        thread_data[i].result = result;
        thread_data[i].start = i * chunk_size;
        thread_data[i].end = (i == THREAD_COUNT - 1) ? text_len : (i + 1) * chunk_size;
        thread_data[i].key_len = key_len;
        thread_data[i].is_encrypt = 1;
        pthread_create(&threads[i], NULL, thread_process, &thread_data[i]);
    }
    for (int i = 0; i < THREAD_COUNT; i++) {
        pthread_join(threads[i], NULL);
    }
    result[text_len] = '\0';
    return result;
}

char *parallel_decrypt(const char *text, const char *key, int text_len, int key_len) {
    char *result = (char *)malloc(text_len + 1);
    if (!result) return NULL;
    pthread_t threads[THREAD_COUNT];
    ThreadData thread_data[THREAD_COUNT];
    int chunk_size = text_len / THREAD_COUNT;
    for (int i = 0; i < THREAD_COUNT; i++) {
        thread_data[i].text = text;
        thread_data[i].key = key;
        thread_data[i].result = result;
        thread_data[i].start = i * chunk_size;
        thread_data[i].end = (i == THREAD_COUNT - 1) ? text_len : (i + 1) * chunk_size;
        thread_data[i].key_len = key_len;
        thread_data[i].is_encrypt = 0;
        pthread_create(&threads[i], NULL, thread_process, &thread_data[i]);
    }
    for (int i = 0; i < THREAD_COUNT; i++) {
        pthread_join(threads[i], NULL);
    }
    result[text_len] = '\0';
    return result;
}

void free_memory(char *ptr) {
    if (ptr) free(ptr);
}