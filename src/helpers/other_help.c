#include "s21_helpers.h"

void init_decimal(s21_decimal *a) {
    a->bits[LOW] = a->bits[MID] =
    a->bits[HIGH] = a->bits[EXT] = 0;
    a->type = S21_NORMAL;
}

void decimal_pos_overflow(s21_decimal *a) {
    init_decimal(a);
    a->type = S21_INF;
}

void decimal_neg_overflow(s21_decimal *a) {
    init_decimal(a);
    a->type = S21_INF_NEG;
}

void decimal_nan_value(s21_decimal *a) {
    init_decimal(a);
    a->type = S21_NAN;
}

void cpy_decimal(s21_decimal src, s21_decimal *dst) {
    for (int i = LOW; i <= EXT; i++)
        dst->bits[i] = src.bits[i];
}

void set_sign(s21_decimal *dst, int sign) {
    dst->bits[EXT] = modBit(dst->bits[EXT], SIGNBIT, sign);
}

int check_sign(s21_decimal dst) {
    return (isBit(dst.bits[EXT], SIGNBIT));
}

int get_dec_scale(s21_decimal a) {
    unsigned int mask = (1U << 16);
    unsigned int stop = (1U << 23);
    int scale = 0;
    for (int i = 0; mask <= stop; mask <<= 1, i++)
        if (!!(mask & a.bits[EXT]))
            scale += pow(2, i);
    return scale;
}

void set_dec_scale(int scale, s21_decimal *a) {
    for (unsigned int mask = 1U, i = 16; i <= 23; mask <<= 1, i++)
        if (!!(scale & mask))
            a->bits[EXT] = setBit(a->bits[EXT], i);
}

int is_zero_mant(s21_decimal val) {
    return (val.bits[0] == 0
         && val.bits[1] == 0
         && val.bits[2] == 0);
}

int find_first_rbit(s21_decimal num) {
    int pos = 95;
    for (int i = HIGH; i >= LOW; i--) {
        for (int j = INT_BITS - 1; j >= 0; j--) {
            if (isBit(num.bits[i], j))
                return pos;
            pos--;
        }
    }
    return 0;
}