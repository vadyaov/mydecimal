#include "../decimal_test.h"

START_TEST(truncate_t1) {
    __int128_t a = llabs(get_random_ll() * rand());

    int exp = rand() % 11;
    __int128_t b = int128_pow(10, exp);
    __int128_t sum = a / b;

    s21_decimal expected = bigint_to_decimal(sum);

    s21_decimal val = bigint_to_decimal(a);
    set_dec_scale(exp, &val);

    s21_decimal got = {0};

    int ret = s21_truncate(val, &got);

    ck_assert_int_eq(s21_is_equal(expected, got), 1);
    ck_assert_int_eq(ret, SUCCESS);
}
END_TEST

START_TEST(truncate_t2) {
    s21_decimal before_trunc, after_trunc;
    float before = 12345.55;
    float after = 12345.0;
    s21_from_float_to_decimal(before, &before_trunc);

    s21_truncate(before_trunc, &after_trunc);
    s21_from_decimal_to_float(after_trunc, &before);

    ck_assert_float_eq_tol(before, after, 1e-6);
} END_TEST

START_TEST(truncate_t3) {
    s21_decimal before_trunc, after_trunc;
    float before = 12345.55;
    float after = 12345.0;
    s21_from_float_to_decimal(before, &before_trunc);

    s21_truncate(before_trunc, &after_trunc);
    s21_from_decimal_to_float(after_trunc, &before);

    ck_assert_float_eq_tol(before, after, 1e-6);
} END_TEST

START_TEST(truncate_t4) {
    s21_decimal before_trunc, after_trunc;
    float before = 12345.55;
    float after = 12345.0;
    s21_from_float_to_decimal(before, &before_trunc);

    s21_truncate(before_trunc, &after_trunc);
    s21_from_decimal_to_float(after_trunc, &before);

    ck_assert_float_eq_tol(before, after, 1e-6);
} END_TEST

START_TEST(truncate_t5) {
    s21_decimal before_trunc, after_trunc;
    float before = 12345.55;
    float after = 12345.0;
    s21_from_float_to_decimal(before, &before_trunc);

    s21_truncate(before_trunc, &after_trunc);
    s21_from_decimal_to_float(after_trunc, &before);

    ck_assert_float_eq_tol(before, after, 1e-6);
} END_TEST

START_TEST(truncate_t6) {
    s21_decimal before_trunc, after_trunc;
    float before = 12345.55;
    float after = 12345.0;
    s21_from_float_to_decimal(before, &before_trunc);

    s21_truncate(before_trunc, &after_trunc);
    s21_from_decimal_to_float(after_trunc, &before);

    ck_assert_float_eq_tol(before, after, 1e-6);
} END_TEST

START_TEST(truncate_t7) {
    s21_decimal before_trunc, after_trunc;
    float before = -12345.55;
    float after = -12345.0;
    s21_from_float_to_decimal(before, &before_trunc);

    s21_truncate(before_trunc, &after_trunc);
    s21_from_decimal_to_float(after_trunc, &before);

    ck_assert_float_eq_tol(before, after, 1e-6);
} END_TEST

START_TEST(truncate_t8) {
    s21_decimal before_trunc, after_trunc;
    float before = 0;
    float after = 0;
    s21_from_float_to_decimal(before, &before_trunc);

    s21_truncate(before_trunc, &after_trunc);
    s21_from_decimal_to_float(after_trunc, &before);

    ck_assert_float_eq_tol(before, after, 1e-6);
} END_TEST

START_TEST(truncate_t9) {
    s21_decimal before_trunc, after_trunc;
    float before = 5;
    float after = 5;
    s21_from_float_to_decimal(before, &before_trunc);

    s21_truncate(before_trunc, &after_trunc);
    s21_from_decimal_to_float(after_trunc, &before);

    ck_assert_float_eq_tol(before, after, 1e-6);
} END_TEST

START_TEST(truncate_t10) {
    s21_decimal before_trunc, after_trunc;
    float before = 0.9235892;
    float after = 0;
    s21_from_float_to_decimal(before, &before_trunc);

    s21_truncate(before_trunc, &after_trunc);
    s21_from_decimal_to_float(after_trunc, &before);

    ck_assert_float_eq_tol(before, after, 1e-6);
} END_TEST


Suite *s21_truncate_test() {
    Suite *s = suite_create("[s21_truncate] Unit Test");

    TCase *tc1_s21_truncate = tcase_create("truncate_t1");
    TCase *tc2_s21_truncate = tcase_create("truncate_t2");
    TCase *tc3_s21_truncate = tcase_create("truncate_t3");
    TCase *tc4_s21_truncate = tcase_create("truncate_t4");
    TCase *tc5_s21_truncate = tcase_create("truncate_t5");
    TCase *tc6_s21_truncate = tcase_create("truncate_t6");
    TCase *tc7_s21_truncate = tcase_create("truncate_t7");
    TCase *tc8_s21_truncate = tcase_create("truncate_t8");
    TCase *tc9_s21_truncate = tcase_create("truncate_t9");
    TCase *tc10_s21_truncate = tcase_create("truncate_t10");

    tcase_add_loop_test(tc1_s21_truncate, truncate_t1, 0, 50);
    tcase_add_test(tc2_s21_truncate, truncate_t2);
    tcase_add_test(tc3_s21_truncate, truncate_t3);
    tcase_add_test(tc4_s21_truncate, truncate_t4);
    tcase_add_test(tc5_s21_truncate, truncate_t5);
    tcase_add_test(tc6_s21_truncate, truncate_t6);
    tcase_add_test(tc7_s21_truncate, truncate_t7);
    tcase_add_test(tc8_s21_truncate, truncate_t8);
    tcase_add_test(tc9_s21_truncate, truncate_t9);
    tcase_add_test(tc10_s21_truncate, truncate_t10);

    suite_add_tcase(s, tc1_s21_truncate);
    suite_add_tcase(s, tc2_s21_truncate);
    suite_add_tcase(s, tc3_s21_truncate);
    suite_add_tcase(s, tc4_s21_truncate);
    suite_add_tcase(s, tc5_s21_truncate);
    suite_add_tcase(s, tc6_s21_truncate);
    suite_add_tcase(s, tc7_s21_truncate);
    suite_add_tcase(s, tc8_s21_truncate);
    suite_add_tcase(s, tc9_s21_truncate);
    suite_add_tcase(s, tc10_s21_truncate);
    return s;
}

