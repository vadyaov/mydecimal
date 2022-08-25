#ifndef SRC_TESTS_DECIMAL_TEST_H_
#define SRC_TESTS_DECIMAL_TEST_H_

#include <check.h>
#include <time.h>
#include <float.h>
#include <stdio.h>
#include <assert.h>

#include "../s21_decimal.h"

// test helpers
int get_rand_int(int min, int max);
float get_rand_float(float min, float max);
s21_decimal random_decimal(int dec_size, int exp_size);

// Suites
Suite *s21_from_int_to_decimal_test();
Suite *s21_from_float_to_decimal_test();
Suite *s21_from_decimal_to_int_test();

#endif  // SRC_TESTS_DECIMAL_TEST_H_