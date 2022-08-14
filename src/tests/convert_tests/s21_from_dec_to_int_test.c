#include "../decimal_test.h"

START_TEST(dec_to_int_t1) {
    s21_decimal input = {0};

    int got = 0;
    int exp = get_rand_int(1, 5);
    int expected = get_rand_int(0, INT32_MAX);

    input.bits[0] = expected;

    if (rand() % 2) {
        expected = -expected;
    }

    set_dec_scale(exp, &input);

    expected = expected / (pow(10, exp));

    if (expected < 0)
        set_sign(&input, NEGATIVE);

    int code = s21_from_decimal_to_int(input, &got);

    if (expected > INT32_MIN && expected < INT32_MAX) {
        ck_assert_int_eq(got, expected);
        ck_assert_int_eq(code, SUCCESS);
    } else {
        ck_assert_int_eq(code, CONVERT_ERROR);
    }
} END_TEST

START_TEST(dec_to_int_t2) {
    int *dest = NULL;
    s21_decimal a = random_decimal(3, 0);
    int status = s21_from_decimal_to_int(a, dest);
    ck_assert_int_eq(status, CONVERT_ERROR);
} END_TEST

START_TEST(dec_to_int_t3) {
    int dest;
    s21_decimal a = {{255, 0, 0, 0}, 2};
    int status = s21_from_decimal_to_int(a, &dest);
    ck_assert_int_eq(status, CONVERT_ERROR);
} END_TEST

START_TEST(dec_to_int_t4) {
    int dest;
    s21_decimal a = {{255, 1, 0, 0}, 0};
    int status = s21_from_decimal_to_int(a, &dest);
    ck_assert_int_eq(status, CONVERT_ERROR);
} END_TEST

START_TEST(dec_to_int_t5) {
    int dest;
    s21_decimal a = {{255, 0, 15, 0}, 0};
    int status = s21_from_decimal_to_int(a, &dest);
    ck_assert_int_eq(status, CONVERT_ERROR);
} END_TEST

Suite *s21_from_decimal_to_int_test() {
    Suite *s = suite_create("[s21_from_decimal_to_int] Unit Test");

    TCase *tc1_s21_from_int_to_dec = tcase_create("dec_to_int_t1");
    TCase *tc2_s21_from_int_to_dec = tcase_create("dec_to_int_t2");
    TCase *tc3_s21_from_int_to_dec = tcase_create("dec_to_int_t3");
    TCase *tc4_s21_from_int_to_dec = tcase_create("dec_to_int_t4");
    TCase *tc5_s21_from_int_to_dec = tcase_create("dec_to_int_t5");

    tcase_add_loop_test(tc1_s21_from_int_to_dec, dec_to_int_t1, 0, 100);
    tcase_add_test(tc2_s21_from_int_to_dec, dec_to_int_t2);
    tcase_add_test(tc3_s21_from_int_to_dec, dec_to_int_t3);
    tcase_add_test(tc4_s21_from_int_to_dec, dec_to_int_t4);
    tcase_add_test(tc5_s21_from_int_to_dec, dec_to_int_t5);

    suite_add_tcase(s, tc1_s21_from_int_to_dec);
    suite_add_tcase(s, tc2_s21_from_int_to_dec);
    suite_add_tcase(s, tc3_s21_from_int_to_dec);
    suite_add_tcase(s, tc4_s21_from_int_to_dec);
    suite_add_tcase(s, tc5_s21_from_int_to_dec);

    return s;
}
