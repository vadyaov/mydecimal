#include "s21_converters.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
    int convert_error = SUCCESS;
    if (dst && src.type == S21_NORMAL) {
        int sign = check_sign(src);
        int exp = get_dec_scale(src);
        long double temp = 0.0L;
        int k = 0;
        for (int i = LOW; i <= HIGH; i++) {
            for (int j = 0; j < INT_BITS; j++) {
                temp += powl(2.0L, k) * isBit(src.bits[i], j);
                k++;
            }
        }
        while (exp--)
            temp /= 10.0L;
        if (sign) temp *= -1.0L;
        *dst = temp;
    } else {
        convert_error = CONVERT_ERROR;
    }
    return convert_error;
}
