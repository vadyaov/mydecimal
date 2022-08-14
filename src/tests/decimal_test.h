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

// Suites
Suite *s21_from_int_to_decimal_test();

#endif  // SRC_TESTS_DECIMAL_TEST_H_