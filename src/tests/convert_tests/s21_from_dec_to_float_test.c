#include "../decimal_test.h"

START_TEST(dec_to_float_t1) {
    s21_decimal value = random_decimal(2, 15);

    int int_expected = 0;
    s21_decimal to_int = value;

    /* zero the exponent to avoid number truncation */
    set_dec_scale(0, &to_int);

    int overflow = s21_from_decimal_to_int(to_int, &int_expected);
    int exp_expected = get_dec_scale(value);

    float expected = int_expected;

    /* recover the exponent */
    while (exp_expected--)
        expected /= 10.0;

    float got = 0;
    int code = s21_from_decimal_to_float(value, &got);

    if (overflow == SUCCESS) {
        ck_assert_float_eq_tol(expected, got, 1e+3);
        ck_assert_int_eq(code, SUCCESS);
    }
} END_TEST

// START_TEST(dec_to_float_t2) {

// } END_TEST

// START_TEST(dec_to_float_t3) {

// } END_TEST

// START_TEST(dec_to_float_t4) {

// } END_TEST

// START_TEST(dec_to_float_t5) {

// } END_TEST

// START_TEST(dec_to_float_t6) {

// } END_TEST

// START_TEST(dec_to_float_t7) {

// } END_TEST

// START_TEST(dec_to_float_t8) {

// } END_TEST

// START_TEST(dec_to_float_t9) {

// } END_TEST

// START_TEST(dec_to_float_t10) {

// } END_TEST

Suite *s21_from_decimal_to_float_test() {
    Suite *s = suite_create("[s21_from_decimal_to_float] Unit Test");

    TCase *tc1_s21_from_dec_to_float = tcase_create("dec_to_float_t1");
    // TCase *tc2_s21_from_dec_to_float = tcase_create("dec_to_float_t2");
    // TCase *tc3_s21_from_dec_to_float = tcase_create("dec_to_float_t3");
    // TCase *tc4_s21_from_dec_to_float = tcase_create("dec_to_float_t4");
    // TCase *tc5_s21_from_dec_to_float = tcase_create("dec_to_float_t5");
    // TCase *tc6_s21_from_dec_to_float = tcase_create("dec_to_float_t6");
    // TCase *tc7_s21_from_dec_to_float = tcase_create("dec_to_float_t7");
    // TCase *tc8_s21_from_dec_to_float = tcase_create("dec_to_float_t8");
    // TCase *tc9_s21_from_dec_to_float = tcase_create("dec_to_float_t9");
    // TCase *tc10_s21_from_dec_to_float = tcase_create("dec_to_float_t10");

    tcase_add_loop_test(tc1_s21_from_dec_to_float, dec_to_float_t1, 0, 100);
    // tcase_add_test(tc2_s21_from_dec_to_float, dec_to_float_t2);
    // tcase_add_test(tc3_s21_from_dec_to_float, dec_to_float_t3);
    // tcase_add_test(tc4_s21_from_dec_to_float, dec_to_float_t4);
    // tcase_add_test(tc5_s21_from_dec_to_float, dec_to_float_t5);
    // tcase_add_test(tc6_s21_from_dec_to_float, dec_to_float_t6);
    // tcase_add_test(tc7_s21_from_dec_to_float, dec_to_float_t7);
    // tcase_add_loop_test(tc8_s21_from_dec_to_float, dec_to_float_t8, 0, 493);
    // tcase_add_test(tc9_s21_from_dec_to_float, dec_to_float_t9);
    // tcase_add_test(tc10_s21_from_dec_to_float, dec_to_float_t10);

    suite_add_tcase(s, tc1_s21_from_dec_to_float);
    // suite_add_tcase(s, tc2_s21_from_dec_to_float);
    // suite_add_tcase(s, tc3_s21_from_dec_to_float);
    // suite_add_tcase(s, tc4_s21_from_dec_to_float);
    // suite_add_tcase(s, tc5_s21_from_dec_to_float);
    // suite_add_tcase(s, tc6_s21_from_dec_to_float);
    // suite_add_tcase(s, tc7_s21_from_dec_to_float);
    // suite_add_tcase(s, tc8_s21_from_dec_to_float);
    // suite_add_tcase(s, tc9_s21_from_dec_to_float);
    // suite_add_tcase(s, tc10_s21_from_dec_to_float);

    return s;
}
