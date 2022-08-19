#include "../decimal_test.h"
#include <limits.h>

START_TEST(sub_t1) {
    float a = -4556.789123;
    for (; a < 4556.789123; a += 0.12378) {
        float b = 7.45 * a;

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

        ck_assert_double_eq(a - b, res);
        ck_assert_int_eq(s21_is_equal(result, resdec_expected), 1);
    }
}
END_TEST


Suite *s21_sub_test() {
    Suite *s = suite_create("[s21_sub] Unit Test");
    TCase *tc1_s21_sub = tcase_create("sub_t1");

    tcase_add_test(tc1_s21_sub, sub_t1);

    suite_sub_tcase(s, tc1_s21_sub);

    return s;
}