#ifndef SRC_TESTS_DECIMAL_TEST_H_
#define SRC_TESTS_DECIMAL_TEST_H_

#include <check.h>
#include <float.h>
#include <stdio.h>
#include <time.h>

#include "../s21_decimal.h"

// test helpers
int get_rand_int(int min, int max);
float get_rand_float(float min, float max);
s21_decimal random_decimal(int dec_size, int exp_size);
__int128_t int128_pow(int val, int exponent);
s21_decimal ll_to_decimal(long long val);
s21_decimal bigint_to_decimal(__int128_t src);
long long get_random_ll(void);
short int get_random_short(void);

// Suites
Suite *s21_from_int_to_decimal_test();
Suite *s21_from_float_to_decimal_test();
Suite *s21_from_decimal_to_int_test();
Suite *s21_from_decimal_to_float_test();
Suite *s21_floor_test();
Suite *s21_round_test();
Suite *s21_truncate_test();
Suite *s21_negate_test();
Suite *s21_add_test();
Suite *s21_sub_test();
Suite *s21_mul_test();
Suite *s21_div_test();
Suite *s21_mod_test();
Suite *s21_is_equal_test();
Suite *s21_is_greater_or_equal_test();
Suite *s21_is_less_test();
Suite *s21_is_greater_test();
Suite *s21_is_not_equal_test();
Suite *s21_is_less_or_equal_test();

#endif  // SRC_TESTS_DECIMAL_TEST_H_
