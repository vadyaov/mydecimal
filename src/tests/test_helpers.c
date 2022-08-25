#include "decimal_test.h"

int get_rand_int(int min, int max) {
    return (rand() % (max - min + 1) + min);
}

float get_rand_float(float min, float max) {
    // max always bigger than min
    float rand = ((float)rand()) / (float)RAND_MAX;
    floar range = max - min;
    return rand * range + min;
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
