#include "../decimal_test.h"
#include <limits.h>
#include <math.h>

START_TEST(mod_t1) {
    float x = 50000.0;
    float a = (float)rand()/(float)(RAND_MAX/x);
    float b = (float)rand()/(float)(RAND_MAX/x);

    if (rand() % 2)
        a = -a;
    if (rand() % 2)
        b = -b;
    s21_decimal adec;
    s21_from_float_to_decimal(a, &adec);

    s21_decimal bdec;
    s21_from_float_to_decimal(b, &bdec);

    s21_decimal result;
    init_decimal(&result);

    // if (rand() % 100 == 55) {
    //     s21_mod(adec, bdec, &result);

    //     float res = 0.0;
    //     s21_from_decimal_to_float(result, &res);

    //     ck_assert_double_eq_tol(fmod(a, b), res, 1e-3);
    // } else {
        s21_mod(adec, bdec, &result);

        float res = 0.0;
        s21_from_decimal_to_float(result, &res);

        ck_assert_double_eq_tol(fmod(a, b), res, 1e-3);
    // }
}
END_TEST



Suite *s21_mod_test() {
    Suite *s = suite_create("[s21_mod] Unit Test");

    TCase *tc1_s21_mod = tcase_create("mod_t1");

    tcase_add_loop_test(tc1_s21_mod, mod_t1, 0, 100);

    suite_add_tcase(s, tc1_s21_mod);

    return s;
}