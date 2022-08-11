#include "s21_converters.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
    int convert_error = SUCCESS;
    if (dst) {
        if (bad_float(src) || src > MAX_DECIMAL || src < MIN_DECIMAL)
            convert_error = CONVERT_ERROR;
        if (!convert_error) {
            int sign = __builtin_signbit(src);
            src = fabsf(src);
            int exp = get_float_exp(src);
            if (exp >= -94 && exp <= 95) {
                init_decimal(dst);
                if (exp >= 23) {
                    cpy_mantis_to_low_dec(src, dst);
                    set_invisible(dst, 23);
                    shift_mant_left(dst, exp - 23);
                } else {
                    long double srctmp = (long double)src;
                    printf("srtcmp = %.30Lf\n", srctmp);
                    char bits[129] = {'\0'};
                    exp = integer_part_count(srctmp);
                    printf("exp = %d\n", exp);
                    get_bit_string(srctmp, bits, exp);
                    set_bits_from_string(bits, dst);
                    set_dec_scale(28 - exp - 1, dst);
                }
                if (sign) set_sign(dst, 1);
            } else {
                if (exp < -94) init_decimal(dst);
                convert_error = CONVERT_ERROR;
            }
        }
    } else {
        convert_error = CONVERT_ERROR;
    }
    return convert_error;
}
