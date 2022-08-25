#include "s21_decimal.h"

int simple_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int membit = 0;
    int bit1, bit2;
    for (int i = LOW; i <= HIGH; i++) {
        for (int j = 0; j < INT_BITS; j++) {
            bit1 = isBit(value_1.bits[i], j);
            bit2 = isBit(value_2.bits[i], j);
            if (!bit1 && !bit2) {
                if (!membit)
                    result->bits[i] = clearBit(result->bits[i], j);
                else
                    result->bits[i] = setBit(result->bits[i], j);
            } else if (!bit1 && bit2) {
                if (!membit) {
                    result->bits[i] = setBit(result->bits[i], j);
                    membit = 1;
                } else {
                    result->bits[i] = clearBit(result->bits[i], j);
                }
            } else if (bit1 && !bit2) {
                if (!membit) {
                    result->bits[i] = setBit(result->bits[i], j);
                } else {
                    result->bits[i] = clearBit(result->bits[i], j);
                    membit = 0;
                }
            } else if (bit1 && bit2) {
                if (!membit) {
                    result->bits[i] = clearBit(result->bits[i], j);
                } else {
                    result->bits[i] = setBit(result->bits[i], j);
                }
            }
        }
    }
    return SUCCESS;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int status = SUCCESS;
    if (result) {
        int sign1 = check_sign(value_1),
            sign2 = check_sign(value_2);
        balance(&value_1, &value_2);
        init_decimal(result);
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
