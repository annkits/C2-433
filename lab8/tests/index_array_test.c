#include <check.h>
#include <stdlib.h>
#include "index_array.h"

START_TEST(test_create_array_success) {
    int *array = NULL;
    int size = 5;
    ck_assert_int_eq(create_array(&array, size), 0);
    ck_assert_ptr_nonnull(array);
    for (int i = 0; i < size; i++) {
        ck_assert_int_eq(array[i], 0);
    }
    free_array(&array);
}
END_TEST

START_TEST(test_create_array_invalid_size) {
    int *array = NULL;
    ck_assert_int_eq(create_array(&array, 0), -1);
    ck_assert_int_eq(create_array(&array, -1), -1);
    ck_assert_ptr_null(array);
}
END_TEST

START_TEST(test_free_array_valid) {
    int *array = NULL;
    int size = 5;
    create_array(&array, size);
    free_array(&array);
    ck_assert_ptr_null(NULL);
}
END_TEST

START_TEST(test_free_array_null) {
    int *array = NULL;
    free_array(&array);
    ck_assert_ptr_null(array);
}
END_TEST

START_TEST(test_insert_element_success) {
    int *array = NULL;
    int size = 5;
    create_array(&array, size);
    size = 0;
    ck_assert_int_eq(insert_element(array, &size, 0, 42), 0);
    ck_assert_int_eq(size, 1);
    ck_assert_int_eq(array[0], 42);
    ck_assert_int_eq(insert_element(array, &size, 1, 100), 0);
    ck_assert_int_eq(size, 2);
    ck_assert_int_eq(array[1], 100);
    free_array(&array);
}
END_TEST

START_TEST(test_insert_element_invalid_index) {
    int *array = NULL;
    int size = 5;
    create_array(&array, size);
    size = 0;
    ck_assert_int_eq(insert_element(array, &size, -1, 42), -1);
    ck_assert_int_eq(insert_element(array, &size, 1, 42), -1);
    free_array(&array);
}
END_TEST

START_TEST(test_insert_element_max_size) {
    int *array = NULL;
    int size = MAX_SIZE;
    create_array(&array, size);
    size = MAX_SIZE;
    ck_assert_int_eq(insert_element(array, &size, 0, 42), -1);
    free_array(&array);
}
END_TEST

START_TEST(test_delete_element_success) {
    int *array = NULL;
    int size = 5;
    create_array(&array, size);
    size = 0;
    insert_element(array, &size, 0, 42);
    insert_element(array, &size, 1, 100);
    ck_assert_int_eq(delete_element(array, &size, 0), 0);
    ck_assert_int_eq(size, 1);
    ck_assert_int_eq(array[0], 100);
    free_array(&array);
}
END_TEST

START_TEST(test_delete_element_invalid_index) {
    int *array = NULL;
    int size = 5;
    create_array(&array, size);
    size = 0;
    ck_assert_int_eq(delete_element(array, &size, 0), -1);
    ck_assert_int_eq(delete_element(array, &size, -1), 0);
    free_array(&array);
}
END_TEST

Suite* index_array_suite(void) {
    Suite* s = suite_create("IndexArray");
    TCase* tc_create = tcase_create("CreateArray");
    TCase* tc_free = tcase_create("FreeArray");
    TCase* tc_insert = tcase_create("InsertElement");
    TCase* tc_delete = tcase_create("DeleteElement");

    tcase_add_test(tc_create, test_create_array_success);
    tcase_add_test(tc_create, test_create_array_invalid_size);
    tcase_add_test(tc_free, test_free_array_valid);
    tcase_add_test(tc_free, test_free_array_null);
    tcase_add_test(tc_insert, test_insert_element_success);
    tcase_add_test(tc_insert, test_insert_element_invalid_index);
    tcase_add_test(tc_insert, test_insert_element_max_size);
    tcase_add_test(tc_delete, test_delete_element_success);
    tcase_add_test(tc_delete, test_delete_element_invalid_index);

    suite_add_tcase(s, tc_create);
    suite_add_tcase(s, tc_free);
    suite_add_tcase(s, tc_insert);
    suite_add_tcase(s, tc_delete);

    return s;
}

int main(void) {
    Suite* s = index_array_suite();
    SRunner* sr = srunner_create(s);
    srunner_run_all(sr, CK_VERBOSE);
    int number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}