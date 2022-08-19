#include "../decimal_test.h"

START_TEST(negate_t1) {
    s21_decimal r = random_decimal(get_rand_int(0, 3), get_rand_int(0, 28)), rr;
    int signr = check_sign(r);
    s21_negate(r, &rr);
    int signrr = check_sign(rr);
    ck_assert_int_eq(signr, !signrr);
    ck_assert_int_eq(simple_equal(r, rr), 1);
} END_TEST

// START_TEST(negate_t2) {

// } END_TEST

// START_TEST(negate_t3) {
  
// } END_TEST

// START_TEST(negate_t4) {

// } END_TEST


Suite *s21_negate_test() {
    Suite *s = suite_create("[s21_negate] Unit Test");

    TCase *tc1_s21_negate = tcase_create("negate_t1");
    // TCase *tc2_s21_negate = tcase_create("negate_t1");
    // TCase *tc3_s21_negate = tcase_create("negate_t1");
    // TCase *tc4_s21_negate = tcase_create("negate_t1");

    tcase_add_loop_test(tc1_s21_negate, negate_t1, 0, 50);
    // tcase_add_test(tc2_s21_negate, negate_t2);
    // tcase_add_test(tc3_s21_negate, negate_t3);
    // tcase_add_test(tc4_s21_negate, negate_t4);

    suite_add_tcase(s, tc1_s21_negate);
    // suite_add_tcase(s, tc2_s21_negate);
    // suite_add_tcase(s, tc3_s21_negate);
    // suite_add_tcase(s, tc4_s21_negate);

    return s;
}