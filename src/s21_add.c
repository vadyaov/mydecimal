#include "s21_decimal.h"

int simple_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int status = 0;
    int membit = 0;
    int bit1, bit2;
    for (int i = LOW; i <= HIGH; i++) {
        for (int j = 0; j < INT_BITS; j++) {
            bit1 = isBit(value_1.bits[i], j);
            bit2 = isBit(value_2.bits[i], j);
            if (!bit1 && !bit2) {
                if (!membit) {
                    result->bits[i] = clearBit(result->bits[i], j);
                } else {
                    result->bits[i] = setBit(result->bits[i], j);
                    membit = 0;
                }
            } else if ((!bit1 && bit2) || (bit1 && !bit2)) {
                if (!membit) {
                    result->bits[i] = setBit(result->bits[i], j);
                } else {
                    result->bits[i] = clearBit(result->bits[i], j);
                }
            } else if (bit1 && bit2) {
                if (!membit) {
                    result->bits[i] = clearBit(result->bits[i], j);
                    membit = 1;
                } else {
                    result->bits[i] = setBit(result->bits[i], j);
                }
            }
        }
    }
    if (membit) status = DATA_OVERFLOW;
    return status;
}

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int status = SUCCESS;
    if (result) {
        if (is_normal_values(value_1, value_2, result)) {
            int sign1 = check_sign(value_1),
                sign2 = check_sign(value_2);
            balance(&value_1, &value_2);
            // printf("AFTER BALANCE:\n");
            // print_decimal(value_1);
            // print_decimal(value_2);
            if (!is_zero_mant(value_1) && !is_zero_mant(value_2)) {
                while (!isBit(value_1.bits[LOW], 0) && !isBit(value_2.bits[LOW], 0)
                        && get_dec_scale(value_1) && get_dec_scale(value_2)) {
                    scale_low(&value_1, 1);
                    scale_low(&value_2, 1);
                }
            }
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
            }
            // если произошло переполнение из-за дробной части (экспоненты не нулевые и статус 1)
            // if (status && get_dec_scale(value_1) && get_dec_scale(value_2)) {
            //     // что то типо bank_round
            // }
            set_dec_scale(scale, result);
            if (is_zero_mant(*result)) set_sign(result, 0);
        }
    } else {
        status = FAIL;
    }
    return status;
}
