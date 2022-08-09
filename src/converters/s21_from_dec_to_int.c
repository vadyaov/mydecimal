#include "s21_converters.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
    int convert_error = SUCCESS;
    if (dst && src.type == S21_NORMAL) {
        s21_decimal after_trunc = ZERO_DECIMAL;
        convert_error = s21_truncate(src, &after_trunc);
        if (src.bits[MID] || src.bits[HIGH])
            convert_error = CONVERT_ERROR;
        if (!convert_error) {
            int sign = check_sign(src);
            *dst = 0;
            for (int i = 0; i < INT_BITS; i++)
                *dst += pow(2, i) * isBit(after_trunc.bits[LOW], i);
            if (sign) *dst = -(*dst);
        }
    } else {
        convert_error = CONVERT_ERROR;
    }
    return convert_error;
}
