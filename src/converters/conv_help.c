#include "s21_converters.h"

int get_float_exp(float src) {
    unsigned int bit = (*(unsigned int *)&src) >> 23;
    int exp = 0;
    for (int i = 0; i < 8; i++)
        exp += pow(2, i) * isBit(bit, i);
    return exp - 127;
}

int bad_float(float src) {
    return (S21_IS_INF(src) || S21_IS_NAN(src));
}

void cpy_mantis_to_low_dec(float src, s21_decimal *dst) {
    unsigned int bit = (*(unsigned int *)&src);
    for (int i = 22; i >= 0; i--)
        if (isBit(bit, i))
            dst->bits[LOW] = setBit(dst->bits[LOW], i);
}

void shift_mant_left(s21_decimal *dst, int count) {
    while (count--) {
        shiftleft(dst);
    }
}

void shift_mant_right(s21_decimal *dst) {
    while (!isBit(dst->bits[LOW], 0))
        shiftright(dst);
}

void set_invisible(s21_decimal *dst, int pos) {
    dst->bits[LOW] = setBit(dst->bits[LOW], pos);
}

// int find_first_rbit(s21_decimal num) {
//     int pos = 95;
//     for (int i = HIGH; i >= LOW; i--) {
//         for (int j = INT_BITS - 1; j >= 0; j--) {
//             if (isBit(num.bits[i], j))
//                 return pos;
//             pos--;
//         }
//     }
//     return 0;
// }

void get_bit_string(long double res, char *bits, int exponent) {
    // printf("%.30Lf\n", res * powl(10.0L, (long double)(25)));
    int mn = 0;
    if (exponent == 1) mn = 28;
    else mn = 28 - exponent - 1;
    res *= powl(10.0L, (long double)(mn));
    printf("RES = %Lf\n", res);
    res = roundl(res);
    for (int i = 0; res > 1e-6; i++) {
        res = floorl(res) / 2;
        if (res - floorl(res) > 1e-6)
            bits[i] = '1';
        else
            bits[i] = '0';
    }
}

void set_bits_from_string(char *bits, s21_decimal *result) {
    for (size_t i = strlen(bits) - 1; i < strlen(bits); i--)
        if (bits[i] - '0')
            result->bits[i / 32] = setBit(result->bits[i / 32], (i % 32));
}

int integer_part_count(long double num) {
    int exp = 0;
    while (num >= 1) {
        num /= 10;
        exp++;
    }
    return !exp ? 1 : exp;
}

