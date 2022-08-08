#include "../s21_decimal.h"
#include "../converters/s21_converters.h"
#include "../helpers/s21_helpers.h"
#include "../comparsion/s21_comparsion.h"
#include "../other/s21_other.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int simple_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int simple_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);