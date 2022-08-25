#include "s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
    int convert_error = SUCCESS;
    if (dst) {
        init_decimal(dst);
        if (src < 0) {
            src = -src;
            set_sign(dst, NEGATIVE);
        }
        dst->bits[LOW] = src;
    } else {
        convert_error = CONVERT_ERROR;
    }
    return convert_error;
}
