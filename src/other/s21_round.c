#include "s21_other.h"

int s21_round(s21_decimal value, s21_decimal *result) {
    int status = SUCCESS;
    if (result && value.type == S21_NORMAL) {
        init_decimal(result);
        int sign = check_sign(value);
        s21_decimal point_part = ZERO_DECIMAL;
        s21_decimal one = {{1, 0, 0, 0}, 0};
        s21_decimal o5 = {{5, 0, 0, 0}, 0};
        set_dec_scale(1, &o5);

        s21_mod(value, one, &point_part);
        s21_truncate(value, result);
        set_sign(&point_part, 0);

        balance(&point_part, &o5);

        if (simple_greater(point_part, o5) || simple_equal(point_part, o5))
            simple_add(*result, one, result);
        set_sign(result, sign);
    } else {
        status = FAIL;
    }
    return status;
}
