#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "vigenere.h"

char *trim(char *str) {
    if (!str) return NULL;
    char *start = str;
    while (isspace((unsigned char)*start)) start++;
    char *end = start + strlen(start) - 1;
    while (end > start && isspace((unsigned char)*end)) end--;
    *(end + 1) = '\0';
    return start;
}

char *read_file(const char *filename, int *length) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Ошибка: невозможно открыть файл %s\n", filename);
        return NULL;
    }
    fseek(file, 0, SEEK_END);
    *length = ftell(file);
    rewind(file);
    char *text = (char *)malloc(*length + 1);
    if (!text) {
        fclose(file);
        printf("Ошибка: невозможно выделить память\n");
        return NULL;
    }
    fread(text, 1, *length, file);
    text[*length] = '\0';
    fclose(file);

    return text;
}

int write_file(const char *filename, const char *text) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Ошибка: невозможно открыть файл %s для записи\n", filename);
        return 0;
    }
    fprintf(file, "%s", text);
    fclose(file);
    return 1;
}

int main(int argc, char **argv) {
    if (argc != 4) {
        printf("Использование: %s <input_file> <output_file> <key>\n", argv[0]);
        return 1;
    }

    const char *input_file = argv[1];
    const char *output_file = argv[2];
    char *key = strdup(argv[3]);
    if (!key) {
        printf("Ошибка: невозможно выделить память для ключа\n");
        return 1;
    }

    key = trim(key);
    int key_len = strlen(key);

    printf("Проверка ключа '%s'\n", key);
    for (int i = 0; i < key_len; i++) {
        int idx = char_to_index(key[i]);
        printf("Символ '%c' (код: %d), индекс в алфавите: %d\n", key[i], (unsigned char)key[i], idx);
        if (idx == -1 || isspace(key[i])) {
            printf("Ошибка: неверный ключ\n");
            free(key);
            return 1;
        }
    }

    int text_len;
    char *input_text = read_file(input_file, &text_len);
    if (!input_text) {
        free(key);
        return 1;
    }

    char *encrypted = parallel_encrypt(input_text, key, text_len, key_len);
    if (!encrypted) {
        free_memory(input_text);
        free(key);
        printf("Ошибка: невозможно зашифровать текст\n");
        return 1;
    }

    if (!write_file(output_file, encrypted)) {
        free_memory(input_text);
        free_memory(encrypted);
        free(key);
        return 1;
    }

    char *decrypted = parallel_decrypt(encrypted, key, text_len, key_len);
    if (!decrypted) {
        free_memory(input_text);
        free_memory(encrypted);
        free(key);
        printf("Ошибка: невозомжно расшифровать текст\n");
        return 1;
    }

    printf("Входной текст:\n%s\n\n", input_text);
    printf("Зашифрованный текст:\n%s\n\n", encrypted);
    printf("Расшифрованный текст:\n%s\n\n", decrypted);

    char *input_text_upper = (char *)malloc(text_len + 1);
    if (input_text_upper) {
        strncpy(input_text_upper, input_text, text_len);
        input_text_upper[text_len] = '\0';
        for (int i = 0; i < text_len; i++) {
            input_text_upper[i] = toupper((unsigned char)input_text_upper[i]);
        }
        if (strcmp(input_text_upper, decrypted) == 0) {
            printf("Проверка: входной и расшифрованный тексты совпадают\n");
        } else {
            printf("Ошибка: входной и расшифрованный тексты не совпадают\n");
        }
        free(input_text_upper);
    } else {
        printf("Ошибка: невозможно выделить память для сравнения\n");
    }

    free_memory(input_text);
    free_memory(encrypted);
    free_memory(decrypted);
    free(key);
    return 0;
}