#include "../decimal_test.h"

START_TEST(float_to_dec_t1) {
    s21_decimal result;
    float float_number1 = get_rand_float(-98765.43, 98765.43);
    int status = s21_from_float_to_decimal(float_number1, &result);
    float float_number2;
    s21_from_decimal_to_float(result, &float_number2);
    ck_assert_int_eq(status, SUCCESS);
    ck_assert_float_eq_tol(float_number1, float_number2, 1e-6);
} END_TEST

START_TEST(float_to_dec_t2) {
    s21_decimal result;
    float nan_float = S21_NAN_VAL;
    int status = s21_from_float_to_decimal(nan_float, &result);
    ck_assert_int_eq(status, FAIL);
} END_TEST

START_TEST(float_to_dec_t3) {
    s21_decimal result;
    float posinf_float = S21_HUGE_VAL;
    int status = s21_from_float_to_decimal(posinf_float, &result);
    ck_assert_int_eq(status, FAIL);
} END_TEST

START_TEST(float_to_dec_t4) {
    s21_decimal result;
    float neginf_float = -S21_HUGE_VAL;
    int status = s21_from_float_to_decimal(neginf_float, &result);
    ck_assert_int_eq(status, FAIL);
} END_TEST

START_TEST(float_to_dec_t5) {
    s21_decimal result;
    float big_float = 12345678999999991245565745456456.0f;  // exp = 103
    int status = s21_from_float_to_decimal(big_float, &result);
    ck_assert_int_eq(status, FAIL);
} END_TEST

START_TEST(float_to_dec_t6) {
    s21_decimal result;
    float tiny_float = 1e-29;  // exp = 103
    int status = s21_from_float_to_decimal(tiny_float, &result);
    ck_assert_int_eq(status, FAIL);
} END_TEST

START_TEST(float_to_dec_t7) {
    s21_decimal result;
    float float_number1 = 2342343232523523524235235.0f;
    int status = s21_from_float_to_decimal(float_number1, &result);
    float float_number2;
    s21_from_decimal_to_float(result, &float_number2);
    ck_assert_int_eq(status, SUCCESS);
    ck_assert_float_eq_tol(float_number1, float_number2, 1e-6);
} END_TEST

START_TEST(float_to_dec_t8) {
    s21_decimal *result = NULL;
    float tiny_float = 1e-29;  // exp = 103
    int status = s21_from_float_to_decimal(tiny_float, result);
    ck_assert_int_eq(status, FAIL);
} END_TEST

// START_TEST(float_to_dec_t9) {

// } END_TEST

// START_TEST(float_to_dec_t10) {

// } END_TEST

Suite *s21_from_float_to_decimal_test() {
    Suite *s = suite_create("[s21_from_float_to_decimal] Unit Test");

    TCase *tc1_s21_from_float_to_dec = tcase_create("float_to_dec_t1");
    TCase *tc2_s21_from_float_to_dec = tcase_create("float_to_dec_t2");
    TCase *tc3_s21_from_float_to_dec = tcase_create("float_to_dec_t3");
    TCase *tc4_s21_from_float_to_dec = tcase_create("float_to_dec_t4");
    TCase *tc5_s21_from_float_to_dec = tcase_create("float_to_dec_t5");
    TCase *tc6_s21_from_float_to_dec = tcase_create("float_to_dec_t6");
    TCase *tc7_s21_from_float_to_dec = tcase_create("float_to_dec_t7");
    TCase *tc8_s21_from_float_to_dec = tcase_create("float_to_dec_t8");
    // TCase *tc9_s21_from_float_to_dec = tcase_create("float_to_dec_t9");
    // TCase *tc10_s21_from_float_to_dec = tcase_create("float_to_dec_t10");

    tcase_add_loop_test(tc1_s21_from_float_to_dec, float_to_dec_t1, 0, 10);
    tcase_add_test(tc2_s21_from_float_to_dec, float_to_dec_t2);
    tcase_add_test(tc3_s21_from_float_to_dec, float_to_dec_t3);
    tcase_add_test(tc4_s21_from_float_to_dec, float_to_dec_t4);
    tcase_add_test(tc5_s21_from_float_to_dec, float_to_dec_t5);
    tcase_add_test(tc6_s21_from_float_to_dec, float_to_dec_t6);
    tcase_add_loop_test(tc7_s21_from_float_to_dec, float_to_dec_t7, 0, 10);
    tcase_add_test(tc8_s21_from_float_to_dec, float_to_dec_t8);
    // tcase_add_test(tc9_s21_from_float_to_dec, float_to_dec_t9);
    // tcase_add_test(tc10_s21_from_float_to_dec, float_to_dec_t10);

    suite_add_tcase(s, tc1_s21_from_float_to_dec);
    suite_add_tcase(s, tc2_s21_from_float_to_dec);
    suite_add_tcase(s, tc3_s21_from_float_to_dec);
    suite_add_tcase(s, tc4_s21_from_float_to_dec);
    suite_add_tcase(s, tc5_s21_from_float_to_dec);
    suite_add_tcase(s, tc6_s21_from_float_to_dec);
    suite_add_tcase(s, tc7_s21_from_float_to_dec);
    suite_add_tcase(s, tc8_s21_from_float_to_dec);
    // suite_add_tcase(s, tc9_s21_from_float_to_dec);
    // suite_add_tcase(s, tc10_s21_from_float_to_dec);

    return s;
}
