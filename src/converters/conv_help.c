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

// int get_bit_string(long double res, char *bits, int exponent) {
//     int mn = 0;
//     if (exponent == 1 && !(unsigned int)res) mn = 28;
//     else mn = 28 - exponent - 1;
//     res *= powl(10.0L, (long double)(mn));
//     // printf("RES = %Lf\n", res);
//     res = roundl(res);
//     for (int i = 0; res > 1e-6; i++) {
//         res = floorl(res) / 2;
//         if (res - floorl(res) > 1e-6)
//             bits[i] = '1';
//         else
//             bits[i] = '0';
//     }
//     return mn;
// }

// void set_bits_from_string(char *bits, s21_decimal *result) {
//     for (size_t i = strlen(bits) - 1; i < strlen(bits); i--)
//         if (bits[i] - '0')
//             result->bits[i / 32] = setBit(result->bits[i / 32], (i % 32));
// }

int integer_part_count(long double num) {
    int exp = 0;
    while (num >= 1) {
        num /= 10;
        exp++;
    }
    return !exp ? 1 : exp;
}

int isBigExp(float exp) {return (exp > 95 || exp < -94);}

int count_int_part(float *src) {
    float _int;
    modff(*src, &_int);
    int count = 0;
    for (float _int_cp = _int; _int_cp >= 1.0;) {
        _int_cp /= 10.0;
        count++;
    }
    return count;
}

int multi10(float *src, int scale) {
    int integer = count_int_part(src);
    // printf("integer = %d\n", integer);
    // printf("SCALE = %d\n", scale);
    // printf("SRC = %.30f\n", *src);
    int ii = integer > 8 ? 0 : 8 - integer;
    long double srctmp = (long double)(*src);
    for (int i = 0; i < ii && scale < 28; i++) {
        int ex = get_float_exp(*src);
        if (ex > 95 || ex < -94) {
            srctmp /= 10.0L;
            break;
        }
        srctmp *= 10.0L;
        scale++;
    }
    // if (ii) {
    //     srctmp /= 10.0L;
    //     scale--;
    // }
    *src = srctmp;
    // printf("TMP = %.28Lf\n", srctmp);
    // printf("src = %.28f\n", *src);
    return scale;
}

void set1bit(s21_decimal *dst, int exp) {
    int pos = exp > 0 ? exp : abs(exp) - 1;
    if (exp < 32)
        dst->bits[0] = setBit(dst->bits[0], pos);
    else if (exp > 31 && exp < 64)
        dst->bits[1] = setBit(dst->bits[1], pos - 32);
    else if (exp > 63 && exp < 96)
        dst->bits[2] = setBit(dst->bits[2], pos - 64);
}

void put_mantiss_in_decimal(s21_decimal *dst, char *str) {
    for (int i = 0; i < 32; i++) {
        if (str[i] == '1')
            dst->bits[0] = setBit(dst->bits[0], i);
    }
    for (int i = 32; i < 64; i++) {
        if (str[i] == '1')
        dst->bits[1] = setBit(dst->bits[1], i - 32);
    }
    for (int i = 64; i < 96; i++) {
        if (str[i] == '1')
        dst->bits[2] = setBit(dst->bits[2], i - 64);
    }
}

void put_exp_in_decimal(s21_decimal *dst, int e) {
    unsigned int bit = (*(unsigned int*)&e);
    unsigned int mask = 0x80000000;
    int position = 27;
    mask >>= position;
    int i = 20;
    while (position < 32) {
        if (!!(bit & mask))
            dst->bits[3] = setBit(dst->bits[3], i);
        position++;
        mask >>= 1;
        i--;
    }
}

void float_convert(s21_decimal *dst, float *src, int *scale, int exp) {
    unsigned int mask = 0x400000;
    unsigned int bit = *((unsigned int *)src);
    char dec_binStr[129];
    int i = 0;
    for (; i < 128; i++)
        dec_binStr[i] = '0';
    dec_binStr[i] = '\0';
    int start = exp - 1;
    for (; mask && start >= 0; mask >>= 1, start--) {
        if (!!(bit & mask)) dec_binStr[start] = '1';
    }
    put_mantiss_in_decimal(dst, dec_binStr);
    put_exp_in_decimal(dst, *scale);
}
