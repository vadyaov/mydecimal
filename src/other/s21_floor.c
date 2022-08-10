#include "s21_other.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
    int status = SUCCESS;
    if (result && value.type == S21_NORMAL) {
        init_decimal(result);
        int sign = check_sign(value);
        s21_decimal one, point_part = ZERO_DECIMAL;
        s21_from_int_to_decimal(1, &one);
        s21_mod(value, one, &point_part);
        s21_truncate(value, result);
        if (sign && !is_zero_mant(point_part)) {
            balance(result, &one);
            simple_add(*result, one, result);
        }
        set_sign(result, sign);
    } else {
        status = FAIL;
    }
    return status;
}