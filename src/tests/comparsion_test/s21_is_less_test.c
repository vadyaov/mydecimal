#include "../decimal_test.h"

START_TEST(_is_less_t1) {
  s21_decimal r = random_decimal(3, 25);
  r.type = S21_NORMAL;
  s21_decimal rcpy = r;
  ck_assert_int_eq(s21_is_less(r, rcpy), 0);
}
END_TEST

START_TEST(_is_less_t2) {
  s21_decimal a, b;
  float A = 1.998;
  float B = 1.999;
  s21_from_float_to_decimal(A, &a);
  s21_from_float_to_decimal(B, &b);
  ck_assert_int_eq(s21_is_less(a, b), 1);
}
END_TEST

START_TEST(_is_less_t3) {
  s21_decimal a1 = random_decimal(3, 25);
  a1.type = S21_INF;
  s21_decimal a2 = random_decimal(2, 15);
  a2.type = S21_INF;
  ck_assert_int_eq(s21_is_less(a1, a2), 0);
}
END_TEST

START_TEST(_is_less_t4) {
  s21_decimal a1 = random_decimal(3, 25);
  a1.type = S21_INF_NEG;
  s21_decimal a2 = random_decimal(2, 15);
  a2.type = S21_INF_NEG;
  ck_assert_int_eq(s21_is_less(a1, a2), 0);
}
END_TEST

START_TEST(_is_less_t5) {
  s21_decimal a1 = random_decimal(3, 25);
  a1.type = S21_NAN;
  s21_decimal a2 = random_decimal(2, 15);
  a2.type = S21_NORMAL;
  ck_assert_int_eq(s21_is_less(a1, a2), 0);
}
END_TEST

START_TEST(_is_less_t6) {
  s21_decimal a1 = random_decimal(3, 25);
  a1.type = S21_NORMAL;
  s21_decimal a2 = random_decimal(2, 15);
  a2.type = S21_NAN;
  ck_assert_int_eq(s21_is_less(a1, a2), 0);
}
END_TEST

START_TEST(_is_less_t7) {
  s21_decimal a1 = random_decimal(3, 25);
  a1.type = S21_NORMAL;
  s21_decimal a2 = random_decimal(2, 15);
  a2.type = S21_INF;
  ck_assert_int_eq(s21_is_less(a1, a2), 1);
}
END_TEST

START_TEST(_is_less_t8) {
  s21_decimal a1 = random_decimal(3, 25);
  a1.type = S21_INF;
  s21_decimal a2 = random_decimal(2, 15);
  a2.type = S21_NORMAL;
  ck_assert_int_eq(s21_is_less(a1, a2), 0);
}
END_TEST

START_TEST(_is_less_t9) {
  s21_decimal a, b;
  float A = 1.0;
  float B = 2.0;
  s21_from_float_to_decimal(A, &a);
  s21_from_float_to_decimal(B, &b);
  ck_assert_int_eq(s21_is_less(a, b), 1);
}
END_TEST

START_TEST(_is_less_t10) {
  s21_decimal a, b;
  a.type = S21_NORMAL;
  b.type = S21_NORMAL;
  float A = 1.0;
  float B = 1.0;
  s21_from_float_to_decimal(A, &a);
  s21_from_float_to_decimal(B, &b);
  ck_assert_int_eq(s21_is_less(a, b), 0);
}
END_TEST

START_TEST(_is_less_t11) {
  s21_decimal a, b;
  a.type = S21_NORMAL;
  b.type = S21_NORMAL;
  float A = 1.0;
  float B = 2.0;
  s21_from_float_to_decimal(A, &a);
  s21_from_float_to_decimal(B, &b);
  ck_assert_int_eq(s21_is_less(b, a), 0);
}
END_TEST

START_TEST(_is_less_t12) {
  s21_decimal a, b;
  a.type = S21_NORMAL;
  b.type = S21_NORMAL;
  float A = 1.0;
  float B = -2.0;
  s21_from_float_to_decimal(A, &a);
  s21_from_float_to_decimal(B, &b);
  ck_assert_int_eq(s21_is_less(a, b), 0);
}
END_TEST

START_TEST(_is_less_t13) {
  s21_decimal a, b;
  float A = 1.0;
  float B = -2.0;
  s21_from_float_to_decimal(A, &a);
  s21_from_float_to_decimal(B, &b);
  a.type = S21_INF_NEG;
  b.type = S21_NORMAL;
  ck_assert_int_eq(s21_is_less(a, b), 1);
}
END_TEST

START_TEST(_is_less_t14) {
  s21_decimal a, b;
  float A = 1.0;
  float B = -2.0;
  s21_from_float_to_decimal(A, &a);
  s21_from_float_to_decimal(B, &b);
  a.type = S21_INF;
  b.type = S21_INF_NEG;
  ck_assert_int_eq(s21_is_less(a, b), 0);
}
END_TEST

START_TEST(_is_less_t15) {
  s21_decimal a, b;
  float A = -1.0;
  float B = 2.0;
  s21_from_float_to_decimal(A, &a);
  s21_from_float_to_decimal(B, &b);
  a.type = S21_NORMAL;
  b.type = S21_NORMAL;
  ck_assert_int_eq(s21_is_less(a, b), 1);
}
END_TEST

Suite *s21_is_less_test() {
  Suite *s = suite_create("[s21_is_less] Unit Test");

  TCase *tc1_s21_is_less = tcase_create("_is_less_t1");
  TCase *tc2_s21_is_less = tcase_create("_is_less_t2");
  TCase *tc3_s21_is_less = tcase_create("_is_less_t3");
  TCase *tc4_s21_is_less = tcase_create("_is_less_t4");
  TCase *tc5_s21_is_less = tcase_create("_is_less_t5");
  TCase *tc6_s21_is_less = tcase_create("_is_less_t6");
  TCase *tc7_s21_is_less = tcase_create("_is_less_t7");
  TCase *tc8_s21_is_less = tcase_create("_is_less_t8");
  TCase *tc9_s21_is_less = tcase_create("_is_less_t9");
  TCase *tc10_s21_is_less = tcase_create("_is_less_t10");
  TCase *tc11_s21_is_less = tcase_create("_is_less_t11");
  TCase *tc12_s21_is_less = tcase_create("_is_less_t12");
  TCase *tc13_s21_is_less = tcase_create("_is_less_t13");
  TCase *tc14_s21_is_less = tcase_create("_is_less_t14");
  TCase *tc15_s21_is_less = tcase_create("_is_less_t15");

  tcase_add_test(tc1_s21_is_less, _is_less_t1);
  tcase_add_test(tc2_s21_is_less, _is_less_t2);
  tcase_add_test(tc3_s21_is_less, _is_less_t3);
  tcase_add_test(tc4_s21_is_less, _is_less_t4);
  tcase_add_test(tc5_s21_is_less, _is_less_t5);
  tcase_add_test(tc6_s21_is_less, _is_less_t6);
  tcase_add_test(tc7_s21_is_less, _is_less_t7);
  tcase_add_test(tc8_s21_is_less, _is_less_t8);
  tcase_add_test(tc9_s21_is_less, _is_less_t9);
  tcase_add_test(tc10_s21_is_less, _is_less_t10);
  tcase_add_test(tc11_s21_is_less, _is_less_t11);
  tcase_add_test(tc12_s21_is_less, _is_less_t12);
  tcase_add_test(tc13_s21_is_less, _is_less_t13);
  tcase_add_test(tc14_s21_is_less, _is_less_t14);
  tcase_add_test(tc15_s21_is_less, _is_less_t15);

  suite_add_tcase(s, tc1_s21_is_less);
  suite_add_tcase(s, tc2_s21_is_less);
  suite_add_tcase(s, tc3_s21_is_less);
  suite_add_tcase(s, tc4_s21_is_less);
  suite_add_tcase(s, tc5_s21_is_less);
  suite_add_tcase(s, tc6_s21_is_less);
  suite_add_tcase(s, tc7_s21_is_less);
  suite_add_tcase(s, tc8_s21_is_less);
  suite_add_tcase(s, tc9_s21_is_less);
  suite_add_tcase(s, tc10_s21_is_less);
  suite_add_tcase(s, tc11_s21_is_less);
  suite_add_tcase(s, tc12_s21_is_less);
  suite_add_tcase(s, tc13_s21_is_less);
  suite_add_tcase(s, tc14_s21_is_less);
  suite_add_tcase(s, tc15_s21_is_less);

  return s;
}
