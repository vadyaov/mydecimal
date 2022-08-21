#include "../decimal_test.h"

START_TEST(_is_not_equal_t1) {
    s21_decimal r = random_decimal(3, 25);
    r.type = S21_NORMAL;
    s21_decimal rcpy = r;
    ck_assert_int_eq(s21_is_not_equal(r, rcpy), 0);
} END_TEST

START_TEST(_is_not_equal_t2) {
    s21_decimal a1 = random_decimal(3, 25);
    a1.type = S21_NORMAL;
    s21_decimal a2 = random_decimal(1, 5);
    a2.type = S21_NORMAL;
    ck_assert_int_eq(s21_is_not_equal(a1, a2), 1);
} END_TEST

START_TEST(_is_not_equal_t3) {
    s21_decimal a1 = random_decimal(3, 25);
    a1.type = S21_INF;
    s21_decimal a2 = random_decimal(2, 15);
    a2.type = S21_INF;
    ck_assert_int_eq(s21_is_not_equal(a1, a2), 0);
} END_TEST

START_TEST(_is_not_equal_t4) {
    s21_decimal a1 = random_decimal(3, 25);
    a1.type = S21_INF_NEG;
    s21_decimal a2 = random_decimal(2, 15);
    a2.type = S21_INF_NEG;
    ck_assert_int_eq(s21_is_not_equal(a1, a2), 0);
} END_TEST

START_TEST(_is_not_equal_t5) {
    s21_decimal a1 = random_decimal(3, 25);
    a1.type = S21_NAN;
    s21_decimal a2 = random_decimal(2, 15);
    a2.type = S21_NORMAL;
    ck_assert_int_eq(s21_is_not_equal(a1, a2), 1);
} END_TEST

START_TEST(_is_not_equal_t6) {
    s21_decimal a1 = random_decimal(3, 25);
    a1.type = S21_NORMAL;
    s21_decimal a2 = random_decimal(2, 15);
    a2.type = S21_NAN;
    ck_assert_int_eq(s21_is_not_equal(a1, a2), 1);
} END_TEST

START_TEST(_is_not_equal_t7) {
    s21_decimal a1 = random_decimal(3, 25);
    a1.type = S21_NORMAL;
    s21_decimal a2 = random_decimal(2, 15);
    a2.type = S21_INF;
    ck_assert_int_eq(s21_is_not_equal(a1, a2), 1);
} END_TEST

START_TEST(_is_not_equal_t8) {
    s21_decimal a1 = random_decimal(3, 25);
    a1.type = S21_INF;
    s21_decimal a2 = random_decimal(2, 15);
    a2.type = S21_NORMAL;
    ck_assert_int_eq(s21_is_not_equal(a1, a2), 1);
} END_TEST

Suite *s21_is_not_equal_test() {
    Suite *s = suite_create("[s21_is_not_equal] Unit Test");

    TCase *tc1_s21_is_not_equal = tcase_create("_is_not_equal_t1");
    TCase *tc2_s21_is_not_equal = tcase_create("_is_not_equal_t2");
    TCase *tc3_s21_is_not_equal = tcase_create("_is_not_equal_t3");
    TCase *tc4_s21_is_not_equal = tcase_create("_is_not_equal_t4");
    TCase *tc5_s21_is_not_equal = tcase_create("_is_not_equal_t5");
    TCase *tc6_s21_is_not_equal = tcase_create("_is_not_equal_t6");
    TCase *tc7_s21_is_not_equal = tcase_create("_is_not_equal_t7");
    TCase *tc8_s21_is_not_equal = tcase_create("_is_not_equal_t8");

    tcase_add_test(tc1_s21_is_not_equal, _is_not_equal_t1);
    tcase_add_test(tc2_s21_is_not_equal, _is_not_equal_t2);
    tcase_add_test(tc3_s21_is_not_equal, _is_not_equal_t3);
    tcase_add_test(tc4_s21_is_not_equal, _is_not_equal_t4);
    tcase_add_test(tc5_s21_is_not_equal, _is_not_equal_t5);
    tcase_add_test(tc6_s21_is_not_equal, _is_not_equal_t6);
    tcase_add_test(tc7_s21_is_not_equal, _is_not_equal_t7);
    tcase_add_test(tc8_s21_is_not_equal, _is_not_equal_t8);

    suite_add_tcase(s, tc1_s21_is_not_equal);
    suite_add_tcase(s, tc2_s21_is_not_equal);
    suite_add_tcase(s, tc3_s21_is_not_equal);
    suite_add_tcase(s, tc4_s21_is_not_equal);
    suite_add_tcase(s, tc5_s21_is_not_equal);
    suite_add_tcase(s, tc6_s21_is_not_equal);
    suite_add_tcase(s, tc7_s21_is_not_equal);
    suite_add_tcase(s, tc8_s21_is_not_equal);

    return s;
}
