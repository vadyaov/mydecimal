#include "s21_decimal.h"

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
                    char bits[129] = {'\0'};
                    exp = integer_part_count(srctmp);
                    int scale = get_bit_string(srctmp, bits, exp);
                    set_bits_from_string(bits, dst);
                    set_dec_scale(scale, dst);
                    // float dst_see = 0.0;
                    // s21_from_decimal_to_float(*dst, &dst_see);
                    // printf("dst: %.30f", dst_see);
                    /*
                    int floatExp = get_float_exp(src);
                    convert_error = isBigExp(floatExp);
                    if (!convert_error) {
                        int scale = 0;
                        for (; !((int)src); src *= 10, scale++) {}
                        if (scale > 28) {
                            src /= powf(10.0f, scale - 28);
                            scale -= (scale - 28);
                        }
                        scale = multi10(&src, scale);
                        floatExp = get_float_exp(src);
                        convert_error = isBigExp(floatExp);
                        if (!convert_error) {
                            set1bit(dst, floatExp);
                            float_convert(dst, &src, &scale, floatExp);
                        }
                    }
                    */
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

// int s21_from_float_to_decimal(float src, s21_decimal *dst) {
//     int convert_error = SUCCESS;
//     if (dst) {
//         init_decimal(dst);
//         int new = (int)src;
//         int i = 0;
//         if (src < 0) {
//             set_sign(dst, NEGATIVE);
//             src *= -1;
//         }
//         while (src - ((float)new / (int)(pow(10, i))) != 0) {
//             i++;
//             new = src * (int)(pow(10, i));
//         }
//         dst->bits[LOW] = new;
//         set_dec_scale(i, dst);
//     } else {
//         convert_error = FAIL;
//     }
//     return convert_error;
// }
