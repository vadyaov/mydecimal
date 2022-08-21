#ifndef SRC_COMPARSION_S21_COMPARSION_H_
#define SRC_COMPARSION_S21_COMPARSION_H_

#include "../s21_decimal.h"

int s21_is_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater(s21_decimal value_1, s21_decimal value_2);
int s21_is_less(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2);

int simple_equal(s21_decimal value_1, s21_decimal value_2);
int simple_greater(s21_decimal value_1, s21_decimal value_2);
int simple_less(s21_decimal value_1, s21_decimal value_2);

#endif  // SRC_COMPARSION_S21_COMPARSION_H_
