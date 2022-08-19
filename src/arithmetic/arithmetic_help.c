#include "s21_arithmetic.h"

int simple_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int status = 0;
    int membit = 0;
    int bit1, bit2;
    for (int i = LOW; i <= HIGH; i++) {
        for (int j = 0; j < INT_BITS; j++) {
            bit1 = isBit(value_1.bits[i], j);
            bit2 = isBit(value_2.bits[i], j);
            //printf("j:%d  1)%d\t2)%d\tmem = %d\n", j, bit1, bit2, membit);
            if (!bit1 && !bit2) {
                if (!membit) {
                    result->bits[i] = clearBit(result->bits[i], j);
                }
                else {
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

// функция целочисленного деления, возвращает остаток
// запомнили знаки и скейлы
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
        while ((simple_greater(value_1, value_2) || simple_equal(value_1, value_2)) && !isBit(value_2.bits[HIGH], 95)) {
            shiftleft(&value_2);
        }
        if (simple_greater(value_2, value_1))
            shiftright(&value_2);
        simple_sub(value_1, value_2, &tmp);
        res = int_div(tmp, cpy2);
    }
    return res;
}

int is_normal_values(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int res = 1;
    if (value_1.type == S21_NAN || value_2.type == S21_NAN) {
        decimal_nan_value(result);
        res = 0;
    } else if (value_1.type == S21_INF) {
        if (value_2.type == S21_INF) {
            decimal_pos_overflow(result);
        } else if (value_2.type == S21_INF_NEG) {
            decimal_nan_value(result);
        }
        res = 0;
    } else if (value_1.type == S21_INF_NEG) {
        if (value_2.type == S21_INF) {
            decimal_nan_value(result);
        } else if (value_2.type == S21_INF_NEG) {
            decimal_neg_overflow(result);
        }
        res = 0;
    } else if (value_2.type == S21_INF) {
        if (value_1.type == S21_INF) {
            decimal_pos_overflow(result);
        } else if (value_1.type == S21_INF_NEG) {
            decimal_nan_value(result);
        }
        res = 0;
    } else if (value_2.type == S21_INF_NEG) {
        if (value_1.type == S21_INF) {
            decimal_nan_value(result);
        } else if (value_1.type == S21_INF_NEG) {
            decimal_neg_overflow(result);
        }
        res = 0;
    }
    return res;
}