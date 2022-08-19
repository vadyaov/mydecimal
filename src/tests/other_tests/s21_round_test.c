#include "../decimal_test.h"

START_TEST(round_t1) {
    s21_decimal a = {{0, 12345, 6789, 0}, S21_NORMAL}, res = {{0, 12345, 6789, 0}, S21_NORMAL};
    s21_decimal round_a = {0};

    s21_round(a, &round_a);
    ck_assert_int_eq(s21_is_equal(round_a, res), 1);
} END_TEST

START_TEST(round_t2) {
    s21_decimal a = {{2147483648, 12345, 6789, 0}, S21_NORMAL}, res = {{2147483648, 12345, 6789, 0}, S21_NORMAL};
    s21_decimal round_a = {0};

    s21_round(a, &round_a);
    ck_assert_int_eq(s21_is_equal(round_a, res), 1);
} END_TEST

START_TEST(round_t3) {
    s21_decimal a, res, round_a;
    s21_from_float_to_decimal(-5555.0, &a);
    set_dec_scale(26, &a);
    s21_from_float_to_decimal(-6.0, &res);
    s21_round(a, &round_a);
    ck_assert_int_eq(s21_is_equal(round_a, res), 1);
} END_TEST

START_TEST(round_t4) {
    s21_decimal a, res, round_a;
    s21_from_float_to_decimal(-5.5, &a);
    s21_from_float_to_decimal(-6, &res);
    s21_round(a, &round_a);
    ck_assert_int_eq(s21_is_equal(round_a, res), 1);
} END_TEST


Suite *s21_round_test() {
    Suite *s = suite_create("[s21_round] Unit Test");

    TCase *tc1_s21_round = tcase_create("round_t1");
    TCase *tc2_s21_round = tcase_create("round_t1");
    TCase *tc3_s21_round = tcase_create("round_t1");
    TCase *tc4_s21_round = tcase_create("round_t1");

    tcase_add_test(tc1_s21_round, round_t1);
    tcase_add_test(tc2_s21_round, round_t2);
    tcase_add_test(tc3_s21_round, round_t3);
    tcase_add_test(tc4_s21_round, round_t4);

    suite_add_tcase(s, tc1_s21_round);
    suite_add_tcase(s, tc2_s21_round);
    suite_add_tcase(s, tc3_s21_round);
    suite_add_tcase(s, tc4_s21_round);

    return s;
}