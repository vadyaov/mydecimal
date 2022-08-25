#include "../decimal_test.h"

START_TEST(floor_t1) {
  int x = rand();

  if (rand() % 2) x = -x;

  s21_decimal expected = ZERO_DECIMAL;
  int expected_int = abs(x);

  if (x < 0 && expected_int % 10 != 0)
    expected_int = (expected_int / 10 + 1);
  else
    expected_int /= 10;

  expected_int = x < 0 ? -expected_int : expected_int;

  s21_from_int_to_decimal(expected_int, &expected);
  // printf("exp: ");print_decimal(expected);
  s21_decimal got = ZERO_DECIMAL;
  s21_from_int_to_decimal(x, &got);
  set_dec_scale(1, &got);

  s21_decimal res = ZERO_DECIMAL;
  // printf("got: ");print_decimal(got);
  int ret = s21_floor(got, &res);
  // printf("res: ");print_decimal(res);
  ck_assert_int_eq(s21_is_equal(expected, res), 1);
  ck_assert_int_eq(ret, SUCCESS);
}
END_TEST

START_TEST(floor_t2) {
  s21_decimal a, res;
  s21_decimal *round_a = NULL;
  s21_from_float_to_decimal(-5.5, &a);
  s21_from_float_to_decimal(-6, &res);
  int sttaus = s21_floor(a, round_a);
  ck_assert_int_eq(sttaus, FAIL);
}
END_TEST

Suite *s21_floor_test() {
  Suite *s = suite_create("[s21_floor] Unit Test");

  TCase *tc1_s21_floor = tcase_create("floor_t1");
  TCase *tc2_s21_floor = tcase_create("floor_t2");

  tcase_add_loop_test(tc1_s21_floor, floor_t1, 0, 25);
  tcase_add_test(tc1_s21_floor, floor_t2);

  suite_add_tcase(s, tc1_s21_floor);
  suite_add_tcase(s, tc2_s21_floor);
  return s;
}
