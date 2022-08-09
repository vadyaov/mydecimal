#include "s21_arithmetic.h"

int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    balance(&value_1, &value_2);
    // printf("AFTER:\n");
    // print_decimal(value_1);
    // print_decimal(value_2);
    int e = get_dec_scale(value_1);
    int er = simple_mod(value_1, value_2, result);
    set_dec_scale(e, result);
    return er;
}

int simple_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int status = is_zero_mant(value_2);  // div by zero! 
    if (!status) {
        int sign1 = check_sign(value_1);
        printf("sign1 = %d\n", sign1);
        if (simple_less(value_1, value_2)) {
            result->bits[0] = value_1.bits[0];
            result->bits[1] = value_1.bits[1];
            result->bits[2] = value_1.bits[2];
            result->bits[3] = value_1.bits[3];
        } else if (simple_equal(value_1, value_2)) {
            result->bits[0] = result->bits[1] = result->bits[2] = result->bits[3] = 0;
        } else {
            *result = int_div(value_1, value_2);
            // printf_decimal(result);
        }
        sign1 ? set_sign(result, 1) : set_sign(result, 0);
    }
    return status;
}
