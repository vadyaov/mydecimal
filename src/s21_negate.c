#include "s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
    cpy_decimal(value, result);
    set_sign(result, !check_sign(value));
    return SUCCESS;
}
