#include "../decimal_test.h"

START_TEST(round_t1) {
    int x = rand();

    if (rand() % 2) x = -x;

    s21_decimal expected = {0};
    int sign = x > 0 ? 0 : 1;

    x = abs(x);
    int expected_int = x;

    if (x % 10 >= 5)
        expected_int = (expected_int / 10 + 1);
    else
        expected_int /= 10;

    expected_int = sign < 0 ? -expected_int : expected_int;
    s21_from_int_to_decimal(expected_int, &expected);

    s21_decimal got = {0};
    x = sign ? -x : x;
    s21_from_int_to_decimal(x, &got);
    set_dec_scale(1, &got);

    s21_decimal res = {0};
    int ret = s21_floor(got, &res);
    ck_assert_int_eq(s21_is_equal(expected, res), 1);
    ck_assert_int_eq(ret, SUCCESS);
  }
  END_TEST

  Suite *s21_round_test() {
      Suite *s = suite_create("[s21_round] Unit Test");
      TCase *tc1_s21_round = tcase_create("round_t1");

      tcase_add_loop_test(tc1_s21_round, round_t1, 0, 50);

      suite_add_tcase(s, tc1_s21_round);
      return s;
  }