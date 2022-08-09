#include "s21_arithmetic.h"

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int status = SUCCESS;
    if (result) {
        int sign1 = check_sign(value_1),
            sign2 = check_sign(value_2);
        balance(&value_1, &value_2);
        int scale = get_dec_scale(value_1);
        if (!sign1 && !sign2) {
            if (simple_greater(value_1, value_2)) {
                simple_sub(value_1, value_2, result);
            } else {
                simple_sub(value_2, value_1, result);
                set_sign(result, 1);
            }
        } else if (!sign1 && sign2) {
            s21_negate(value_2, &value_2);
            status = simple_add(value_1, value_2, result);
        } else if (sign1 && !sign2) {
            s21_negate(value_1, &value_1);
            status = simple_add(value_1, value_2, result);
            set_sign(result, 1);
        } else if (sign1 && sign2) {
            s21_negate(value_2, &value_2);
            if (simple_greater(value_1, value_2)) {
                s21_negate(value_1, &value_1);
                simple_sub(value_1, value_2, result);
                set_sign(result, 1);
            } else {
                simple_sub(value_2, value_1, result);
            }
        }
        set_dec_scale(scale, result);
    } else {
        status = FAIL;
    }
    return status;
}
