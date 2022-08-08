#include "s21_other.h"
#include "../converters/s21_converters.h"
#include "../helpers/s21_helpers.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
    int error = SUCCESS;
    if (result) {
        init_decimal(result);
        if (value.type == S21_INF) {
            decimal_pos_overflow(result);
        } else if (value.type == S21_INF_NEG) {
            decimal_neg_overflow(result);
        } else if (value.type == S21_NAN) {
            decimal_nan_value(result);
        } else if (value.type == S21_NORMAL) {
            int scale = get_dec_scale(value);
            if (!scale) {
                *result = value;
            } else {
                int sign = check_sign(value);
                // value.bits[EXT] = 0;                // need this for correct division
                // s21_decimal ten = {{0, 0, 0, 10}, 0};
                // while (scale-- && error == SUCCESS) {
                //     error = s21_div(value, ten, result);       // need s21_div :(
                //     value = *result;
                // }
                scale_low(&value, scale);
                *result = value;
                if (sign) set_sign(result, 1);
            }
        }
    } else {
        error = FAIL;
    }
    return error;
}

