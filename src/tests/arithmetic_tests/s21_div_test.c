#include "../decimal_test.h"

START_TEST(div_t1) {
  float a = 25.0;
  for (; a > 8.5; a -= 0.5) {
    float b = 0.25;

    s21_decimal adec;
    s21_from_float_to_decimal(a, &adec);

    s21_decimal bdec;
    s21_from_float_to_decimal(b, &bdec);

    s21_decimal result;
    init_decimal(&result);

    s21_div(adec, bdec, &result);

    // printf("a: %.30f\nb: %.30f\n", a, b);

    float res = 0.0;
    s21_from_decimal_to_float(result, &res);
    // printf("exp: %.30f\nour: %.30f\n", a / b, res);

    float res_expected = a / b;
    ck_assert_double_eq_tol(res_expected, res, 1e-6);
  }
}
END_TEST

Suite *s21_div_test() {
  Suite *s = suite_create("[s21_div] Unit Test");

  TCase *tc1_s21_div = tcase_create("div_t1");

  tcase_add_test(tc1_s21_div, div_t1);

  suite_add_tcase(s, tc1_s21_div);

  return s;
}