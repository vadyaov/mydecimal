#include "s21_helpers.h"

int balance(s21_decimal *value_1, s21_decimal *value_2) {
    int scale1 = get_dec_scale(*value_1);
    int scale2 = get_dec_scale(*value_2);
    int scale_max = (scale1 >= scale2) ? scale1 : scale2;
    s21_decimal val1cpy = *value_1, val2cpy = *value_2;
    if (scale1 != scale_max) {
        while (scale1 != scale_max && !scale_up(&val1cpy, 1)) {
            if (val1cpy.type != S21_NORMAL) break;
            scale1 = get_dec_scale(val1cpy);
        }
        if (scale1 != scale2 || val1cpy.type != S21_NORMAL) {
            scale_up(value_1, (scale1 - get_dec_scale(*value_1)));
            while (scale1 != scale2 && !scale_low(value_2, 1)) {
                scale2 = get_dec_scale(*value_2);
            }
        } else {
            *value_1 = val1cpy;
        }
    } else if (scale2 != scale_max) {
        while (scale2 != scale_max && !scale_up(&val2cpy, 1)) {
            if (val2cpy.type != S21_NORMAL) break;
            scale2 = get_dec_scale(val2cpy);
        }
        if (scale1 != scale2 || val2cpy.type != S21_NORMAL) {
            scale_up(value_2, (scale2 - get_dec_scale(*value_2)));
            while (scale1 != scale2 && !scale_low(value_1, 1)) {
                scale1 = get_dec_scale(*value_1);
            }
        } else {
            *value_2 = val2cpy;
        }
    }
    return 0;
}
