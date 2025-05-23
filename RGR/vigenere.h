#ifndef VIGENERE_H
#define VIGENERE_H

#define ALPHABET_SIZE 27 // 26 букв + пробел
#define THREAD_COUNT 4

extern const char *ALPHABET;

int char_to_index(char c);
char index_to_char(int index);

char *encrypt(const char *text, const char *key, int text_len, int key_len);
char *decrypt(const char *text, const char *key, int text_len, int key_len);
char *parallel_encrypt(const char *text, const char *key, int text_len, int key_len);
char *parallel_decrypt(const char *text, const char *key, int text_len, int key_len);

void free_memory(char *ptr);

#endif