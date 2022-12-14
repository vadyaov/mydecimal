#include <limits.h>

#include "../decimal_test.h"

START_TEST(add_t1) {
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

  s21_add(adec, bdec, &result);

  float res = 0.0;
  s21_from_decimal_to_float(result, &res);

  s21_decimal resdec_expected;
  s21_from_float_to_decimal(a + b, &resdec_expected);

  ck_assert_double_eq_tol(a + b, res, 1e-3);
}
END_TEST

START_TEST(add_t2) {
  int a = 0;
  for (; a < 234567; a += 456) {
    int b = 3 * a;

    s21_decimal adec;
    s21_from_int_to_decimal(a, &adec);

    s21_decimal bdec;
    s21_from_int_to_decimal(b, &bdec);

    s21_decimal result;
    init_decimal(&result);
    s21_add(adec, bdec, &result);
    int res = 0.0;
    s21_from_decimal_to_int(result, &res);

    s21_decimal resdec_expected;
    s21_from_int_to_decimal(a + b, &resdec_expected);
    // print_decimal(result);

    ck_assert_int_eq(a + b, res);
  }
}
END_TEST

START_TEST(add_t3) {
  int a = -234567;
  for (; a < 123; a += 456) {
    int b = 3 * a;

    s21_decimal adec;
    s21_from_int_to_decimal(a, &adec);

    s21_decimal bdec;
    s21_from_int_to_decimal(b, &bdec);

    s21_decimal result;
    init_decimal(&result);
    s21_add(adec, bdec, &result);

    int res = 0.0;
    s21_from_decimal_to_int(result, &res);

    s21_decimal resdec_expected;
    s21_from_int_to_decimal(a + b, &resdec_expected);

    ck_assert_int_eq(a + b, res);
  }
}
END_TEST

START_TEST(add_t4) {
  s21_decimal adec;
  s21_decimal bdec;

  adec.type = 3;
  bdec.type = get_rand_int(0, 3);

  s21_decimal result;
  s21_add(adec, bdec, &result);

  ck_assert_int_eq(result.type, S21_NAN);
}
END_TEST

Suite *s21_add_test() {
  Suite *s = suite_create("[s21_add] Unit Test");
  TCase *tc1_s21_add = tcase_create("add_t1");
  TCase *tc2_s21_add = tcase_create("add_t2");
  TCase *tc3_s21_add = tcase_create("add_t3");
  TCase *tc4_s21_add = tcase_create("add_t4");

  tcase_add_loop_test(tc1_s21_add, add_t1, 0, 100);
  tcase_add_test(tc2_s21_add, add_t2);
  tcase_add_test(tc3_s21_add, add_t3);
  tcase_add_loop_test(tc4_s21_add, add_t4, 0, 10);

  suite_add_tcase(s, tc1_s21_add);
  suite_add_tcase(s, tc2_s21_add);
  suite_add_tcase(s, tc3_s21_add);
  suite_add_tcase(s, tc4_s21_add);
  return s;
}
