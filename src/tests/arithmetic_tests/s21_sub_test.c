#include <limits.h>

#include "../decimal_test.h"

START_TEST(sub_t1) {
  float x = 100.0;
  float a = (float)rand() / (float)(RAND_MAX / x);
  float b = (float)rand() / (float)(RAND_MAX / x);

  if (rand() % 2) a = -a;
  if (rand() % 2) b = -b;

  s21_decimal adec;
  s21_from_float_to_decimal(a, &adec);

  s21_decimal bdec;
  s21_from_float_to_decimal(b, &bdec);

  s21_decimal result;
  init_decimal(&result);
  s21_sub(adec, bdec, &result);

  float res = 0.0;
  s21_from_decimal_to_float(result, &res);

  s21_decimal resdec_expected;
  s21_from_float_to_decimal(a - b, &resdec_expected);

  ck_assert_double_eq_tol(a - b, res, 1e-4);
}
END_TEST

START_TEST(sub_t2) {
  s21_decimal *result = NULL;
  s21_decimal a1 = random_decimal(2, 5);
  s21_decimal a2 = random_decimal(2, 5);
  int status = s21_sub(a1, a2, result);
  ck_assert_int_eq(status, FAIL);
}
END_TEST

Suite *s21_sub_test() {
  Suite *s = suite_create("[s21_sub] Unit Test");

  TCase *tc1_s21_sub = tcase_create("sub_t1");
  TCase *tc2_s21_sub = tcase_create("sub_t2");

  tcase_add_loop_test(tc1_s21_sub, sub_t1, 0, 100);
  tcase_add_test(tc2_s21_sub, sub_t2);

  suite_add_tcase(s, tc1_s21_sub);
  suite_add_tcase(s, tc2_s21_sub);

  return s;
}