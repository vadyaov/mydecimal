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

//   00011000 00111011 11011010 11000110  10101110 10011011 11000001 11001000  11001100 11001100 11001100 11001100
// + 01001010 11110110 10010111 01000001  01110001 00110101 00001101 10000010  10000000 00000000 00000000 00000000