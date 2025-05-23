#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <cmocka.h>
#include <string.h>
#include "../vigenere.h"

static void test_encrypt_decrypt(void **state) {
    (void)state;
    const char *text = "HELLO";
    const char *key = "KEY";
    char *encrypted = encrypt(text, key, strlen(text), strlen(key));
    assert_non_null(encrypted);
    char *decrypted = decrypt(encrypted, key, strlen(text), strlen(key));
    assert_non_null(decrypted);
    assert_string_equal(text, decrypted);
    free_memory(encrypted);
    free_memory(decrypted);
}

static void test_parallel_encrypt_decrypt(void **state) {
    (void)state;
    const char *text = "HELLO";
    const char *key = "KEY";
    char *encrypted = parallel_encrypt(text, key, strlen(text), strlen(key));
    assert_non_null(encrypted);
    char *decrypted = parallel_decrypt(encrypted, key, strlen(text), strlen(key));
    assert_non_null(decrypted);
    assert_string_equal(text, decrypted);
    free_memory(encrypted);
    free_memory(decrypted);
}

static void test_encrypt_decrypt_with_spaces(void **state) {
    (void)state;
    const char *text = "HELLO WORLD";
    const char *key = "KEY";
    char *encrypted = parallel_encrypt(text, key, strlen(text), strlen(key));
    assert_non_null(encrypted);
    char *decrypted = parallel_decrypt(encrypted, key, strlen(text), strlen(key));
    assert_non_null(decrypted);
    assert_string_equal(text, decrypted);
    free_memory(encrypted);
    free_memory(decrypted);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_encrypt_decrypt),
        cmocka_unit_test(test_parallel_encrypt_decrypt),
        cmocka_unit_test(test_encrypt_decrypt_with_spaces),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}