#include "../decimal_test.h"

START_TEST(floor_t1) {
    int x = rand();

    if (rand() % 2) x = -x;

    s21_decimal expected = {0};
    int expected_int = abs(x);

    if (x < 0 && expected_int % 10 != 0)
        expected_int = (expected_int / 10 + 1);
    else
        expected_int /= 10;

    expected_int = x < 0 ? -expected_int : expected_int;

    s21_from_int_to_decimal(expected_int, &expected);

    s21_decimal got = {0};
    s21_from_int_to_decimal(x, &got);
    set_dec_scale(&got, 1);

    s21_decimal res = {0};
    int ret = s21_floor(got, &res);

    ck_assert_int_eq(s21_is_equal(expected, res), TRUE);
    ck_assert_int_eq(ret, CONVERTATION_OK);
  }
  END_TEST

  Suite *s21_floor_test() {
      Suite *s = suite_create("s21_floor");
      TCase *tc = tcase_create("s21_floor_tc");

      tcase_add_loop_test(tc, floor_t1, 0, 10);

      suite_add_tcase(s, tc);
      return s;
  }