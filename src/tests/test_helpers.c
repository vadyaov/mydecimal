#include "decimal_test.h"

int get_rand_int(int min, int max) {
    return (rand() % (max - min + 1) + min);
}

float get_rand_float(float min, float max) {
    // max always bigger than min
    float rand1 = (float) rand() / (float) RAND_MAX;
    float range = max - min;
    return rand1 * range + min;
}

s21_decimal random_decimal(int dec_size, int exp_size) {
    int exp = get_rand_int(0, exp_size);
    int sign = rand() % 2;
    s21_decimal result = ZERO_DECIMAL;
    for (int i = LOW; i < dec_size; i++) {
        for (int j = 0; j < INT_BITS; j++) {
            int bit = rand() % 2;
            if (bit) result.bits[i] = setBit(result.bits[i], j);
        }
    }
    set_dec_scale(exp, &result);
    set_sign(&result, sign);
    return result;
}

__int128_t int128_pow(int val, int exponent) {
    __int128_t res = 1;
    while (exponent--)
        res *= val;
    return res;
}

s21_decimal ll_to_decimal(long long val) {
    s21_decimal res = {0};
    if (val < 0) {
        set_sign(&res, 1);
        val = -val;
    }

    for (uint64_t i = 0; val; i++, val /= 2) {
        if (val % 2)
            res.bits[i / 32] |= (1U << i);
    }

    return res;
}

s21_decimal bigint_to_decimal(__int128_t src) {
    s21_decimal res = {0};

    if (src < 0) {
        set_sign(&res, 1);
        src = -src;
    }
    for (int i = 0, k = 0; i < 3; i++)
        for (int j = 0; j < 32; j++, k++)
            if (isBit(src, k))
                res.bits[i] = setBit(res.bits[i], j);

    return res;
}

long long get_random_ll(void) {
    long long int val = 0;

    for (uint64_t i = 0; i < 64; i++)
        if (rand() % 2)
            val |= (1U << i);

    return val;
}

int setshortBit(short int n, unsigned int pos) {
    return (n | (1 << pos));
}


short int get_random_short(void) {
    short int val = 0;
    for (int i = 0; i < 16; i++)
        if (rand() % 2)
            val = setshortBit(val, i);

    return val;
}