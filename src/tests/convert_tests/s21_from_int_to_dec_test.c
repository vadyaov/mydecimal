#include "../decimal_test.h"

START_TEST(int_to_dec_t1) {
    int test = 1;
    s21_decimal *a = NULL;
    int status = s21_from_int_to_decimal(test, a);
    ck_assert_int_eq(status, CONVERT_ERROR);
} END_TEST

START_TEST(int_to_dec_t2) {
    int test = 0;
    s21_decimal a = ZERO_DECIMAL;
    int status = s21_from_int_to_decimal(test, &a);
    ck_assert_int_eq(status, SUCCESS);
    ck_assert_int_eq(a.bits[LOW], test);
    ck_assert_int_eq(a.bits[MID], 0);
    ck_assert_int_eq(a.bits[HIGH], 0);
    ck_assert_int_eq(a.bits[EXT], 0);
    ck_assert_int_eq(check_sign(a), 0);
} END_TEST

START_TEST(int_to_dec_t3) {
    int test = INT32_MAX;
    s21_decimal a = ZERO_DECIMAL;
    int status = s21_from_int_to_decimal(test, &a);
    ck_assert_int_eq(status, SUCCESS);
    ck_assert_int_eq(a.bits[LOW], test);
    ck_assert_int_eq(a.bits[MID], 0);
    ck_assert_int_eq(a.bits[HIGH], 0);
    ck_assert_int_eq(a.bits[EXT], 0);
    ck_assert_int_eq(check_sign(a), POSITIVE);
} END_TEST

START_TEST(int_to_dec_t4) {
    int test = INT32_MIN;
    unsigned int test_u = (unsigned int)(INT32_MAX) + 1;
    s21_decimal a = ZERO_DECIMAL;
    int status = s21_from_int_to_decimal(test, &a);
    ck_assert_int_eq(status, SUCCESS);
    ck_assert_uint_eq(a.bits[LOW], test_u);
    ck_assert_int_eq(a.bits[MID], 0);
    ck_assert_int_eq(a.bits[HIGH], 0);
    ck_assert_int_eq(get_dec_scale(a), 0);
    ck_assert_int_eq(check_sign(a), NEGATIVE);
} END_TEST

START_TEST(int_to_dec_t5) {
    int test = -228;
    s21_decimal a = ZERO_DECIMAL;
    int status = s21_from_int_to_decimal(test, &a);
    ck_assert_int_eq(status, SUCCESS);
    ck_assert_int_eq(a.bits[LOW], -test);
    ck_assert_int_eq(a.bits[MID], 0);
    ck_assert_int_eq(a.bits[HIGH], 0);
    ck_assert_int_eq(get_dec_scale(a), 0);
    ck_assert_int_eq(check_sign(a), NEGATIVE);
} END_TEST

START_TEST(int_to_dec_t6) {
    int test = 228;
    s21_decimal a = ZERO_DECIMAL;
    int status = s21_from_int_to_decimal(test, &a);
    ck_assert_int_eq(status, SUCCESS);
    ck_assert_int_eq(a.bits[LOW], test);
    ck_assert_int_eq(a.bits[MID], 0);
    ck_assert_int_eq(a.bits[HIGH], 0);
    ck_assert_int_eq(get_dec_scale(a), 0);
    ck_assert_int_eq(check_sign(a), POSITIVE);
} END_TEST

START_TEST(int_to_dec_t7) {
    int test = 20000001;
    s21_decimal a = ZERO_DECIMAL;
    int status = s21_from_int_to_decimal(test, &a);
    ck_assert_int_eq(status, SUCCESS);
    ck_assert_int_eq(a.bits[LOW], test);
    ck_assert_int_eq(a.bits[MID], 0);
    ck_assert_int_eq(a.bits[HIGH], 0);
    ck_assert_int_eq(get_dec_scale(a), 0);
    ck_assert_int_eq(check_sign(a), POSITIVE);
} END_TEST

START_TEST(int_to_dec_t8) {
    int test = get_rand_int(0, INT32_MAX);
    if (rand() % 2)
        test = -test;
    s21_decimal a = ZERO_DECIMAL;
    int status = s21_from_int_to_decimal(test, &a);
    int got = a.bits[0];
    got = test > 0 ? got : -got;
    ck_assert_int_eq(status, SUCCESS);
    ck_assert_int_eq(test, got);
    ck_assert_int_eq(0, a.bits[1]);
    ck_assert_int_eq(0, a.bits[2]);
    ck_assert_int_eq((test < 0), check_sign(a));
    ck_assert_int_eq(0, get_dec_scale(a));
} END_TEST

// START_TEST(int_to_dec_t9) {

// } END_TEST

// START_TEST(int_to_dec_t10) {

// } END_TEST

Suite *s21_from_int_to_decimal_test() {
    Suite *s = suite_create("[s21_from_int_to_decimal] Unit Test");

    TCase *tc1_s21_from_int_to_dec = tcase_create("int_to_dec_t1");
    TCase *tc2_s21_from_int_to_dec = tcase_create("int_to_dec_t2");
    TCase *tc3_s21_from_int_to_dec = tcase_create("int_to_dec_t3");
    TCase *tc4_s21_from_int_to_dec = tcase_create("int_to_dec_t4");
    TCase *tc5_s21_from_int_to_dec = tcase_create("int_to_dec_t5");
    TCase *tc6_s21_from_int_to_dec = tcase_create("int_to_dec_t6");
    TCase *tc7_s21_from_int_to_dec = tcase_create("int_to_dec_t7");
    TCase *tc8_s21_from_int_to_dec = tcase_create("int_to_dec_t8");
    // TCase *tc9_s21_from_int_to_dec = tcase_create("int_to_dec_t9");
    // TCase *tc10_s21_from_int_to_dec = tcase_create("int_to_dec_t10");

    tcase_add_test(tc1_s21_from_int_to_dec, int_to_dec_t1);
    tcase_add_test(tc2_s21_from_int_to_dec, int_to_dec_t2);
    tcase_add_test(tc3_s21_from_int_to_dec, int_to_dec_t3);
    tcase_add_test(tc4_s21_from_int_to_dec, int_to_dec_t4);
    tcase_add_test(tc5_s21_from_int_to_dec, int_to_dec_t5);
    tcase_add_test(tc6_s21_from_int_to_dec, int_to_dec_t6);
    tcase_add_test(tc7_s21_from_int_to_dec, int_to_dec_t7);
    tcase_add_loop_test(tc8_s21_from_int_to_dec, int_to_dec_t8, 0, 493);
    // tcase_add_test(tc9_s21_from_int_to_dec, int_to_dec_t9);
    // tcase_add_test(tc10_s21_from_int_to_dec, int_to_dec_t10);

    suite_add_tcase(s, tc1_s21_from_int_to_dec);
    suite_add_tcase(s, tc2_s21_from_int_to_dec);
    suite_add_tcase(s, tc3_s21_from_int_to_dec);
    suite_add_tcase(s, tc4_s21_from_int_to_dec);
    suite_add_tcase(s, tc5_s21_from_int_to_dec);
    suite_add_tcase(s, tc6_s21_from_int_to_dec);
    suite_add_tcase(s, tc7_s21_from_int_to_dec);
    suite_add_tcase(s, tc8_s21_from_int_to_dec);
    // suite_add_tcase(s, tc9_s21_from_int_to_dec);
    // suite_add_tcase(s, tc10_s21_from_int_to_dec);

    return s;
}