#include "../decimal_test.h"

START_TEST(truncate_t1) {
    __int128_t a = llabs(get_random_ll() * rand());

    int exp = rand() % 11;
    __int128_t b = int128_pow(10, exp);
    __int128_t sum = a / b;

    s21_decimal expected = bigint_to_decimal(sum);

    s21_decimal val = bigint_to_decimal(a);
    set_dec_scale(exp, &val);

    s21_decimal got = {0};

    int ret = s21_truncate(val, &got);

    ck_assert_int_eq(s21_is_equal(expected, got), 1);
    ck_assert_int_eq(ret, SUCCESS);
}
END_TEST

Suite *s21_truncate_test() {
    Suite *s = suite_create("[s21_truncate] Unit Test");
    TCase *tc1_s21_truncate = tcase_create("truncate_t1");

    tcase_add_loop_test(tc1_s21_truncate, truncate_t1, 0, 50);

    suite_add_tcase(s, tc1_s21_truncate);
    return s;
}
