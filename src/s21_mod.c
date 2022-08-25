#include "s21_decimal.h"

s21_decimal int_div(s21_decimal value_1, s21_decimal value_2) {
    s21_decimal res;
    s21_decimal cpy2 = value_2;
    s21_decimal tmp = ZERO_DECIMAL;
    value_1.bits[EXT] = value_2.bits[EXT] = 0;
    if (simple_less(value_1, value_2)) {
        return value_1;
    } else if (simple_equal(value_1, value_2)) {
        return tmp;
    } else {
        while ((simple_greater(value_1, value_2) || simple_equal(value_1, value_2))
               && !isBit(value_2.bits[HIGH], 95)) {
            shiftleft(&value_2);
        }
        if (simple_greater(value_2, value_1))
            shiftright(&value_2);
        simple_sub(value_1, value_2, &tmp);
        res = int_div(tmp, cpy2);
    }
    return res;
}

int simple_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int status = is_zero_mant(value_2);  // div by zero!
    if (!status) {
        int sign1 = check_sign(value_1);
        if (simple_less(value_1, value_2)) {
        result->bits[0] = value_1.bits[0];
        result->bits[1] = value_1.bits[1];
        result->bits[2] = value_1.bits[2];
        result->bits[3] = value_1.bits[3];
        } else if (simple_equal(value_1, value_2)) {
        init_decimal(result);
        } else {
        *result = int_div(value_1, value_2);
        }
        sign1 ? set_sign(result, 1) : set_sign(result, 0);
    }
    return status;
}

int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    balance(&value_1, &value_2);
    // printf("AFTER BALANCE:\n");
    // print_decimal(value_1);
    // print_decimal(value_2);
    int e = get_dec_scale(value_1);
    int er = simple_mod(value_1, value_2, result);
    set_dec_scale(e, result);
    return er;
}

