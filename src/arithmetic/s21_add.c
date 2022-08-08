#include "s21_arithmetic.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int status = SUCCESS;
    if (result) {
        int sign1 = check_sign(value_1),
            sign2 = check_sign(value_2);
        balance(&value_1, &value_2);
        printf("AFTER BALANCE\n");
        print_decimal(value_1);
        print_decimal(value_2);
        printf("\n");
        init_decimal(result);
        int scale = get_dec_scale(value_1);
        if (!sign1 && !sign2) {
            status = simple_add(value_1, value_2, result);
        } else if (!sign1 && sign2) {
            s21_negate(value_2, &value_2);
            if (simple_greater(value_1, value_2)) {
                simple_sub(value_1, value_2, result);
            } else {
                simple_sub(value_2, value_1, result);
                set_sign(result, 1);
            }
        } else if (sign1 && !sign2) {
            s21_negate(value_1, &value_1);
            if (simple_greater(value_1, value_2)) {
                simple_sub(value_1, value_2, result);
                set_sign(result, 1);
            } else {
                simple_sub(value_2, value_1, result);
            }
        } else if (sign1 && sign2) {
            s21_negate(value_1, &value_1);
            s21_negate(value_2, &value_2);
            status = simple_add(value_1, value_2, result);
            set_sign(result, 1);
            print_decimal(*result);
        }
        set_dec_scale(scale, result);
        if (is_zero_mant(*result)) set_sign(result, 0);
    } else {
        status = FAIL;
    }
    return status;
}

// 11000110011001001110010000010000001111111010000110011110100101101001100110011001100110011001100
// 11100111111111101111111100011111101111111111110110011110100101101001100110011001100110011001100