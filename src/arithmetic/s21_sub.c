#include "s21_arithmetic.h"

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int status = SUCCESS;
    if (result) {
        int sign1 = check_sign(value_1),
            sign2 = check_sign(value_2);
        balance(&value_1, &value_2);
        int scale = get_dec_scale(value_1);
        if (!sign1 && !sign2) {
            if (simple_greater(value_1, value_2)) {
                simple_sub(value_1, value_2, result);
            } else {
                simple_sub(value_2, value_1, result);
                set_sign(result, 1);
            }
        } else if (!sign1 && sign2) {
            s21_negate(value_2, &value_2);
            status = simple_add(value_1, value_2, result);
        } else if (sign1 && !sign2) {
            s21_negate(value_1, &value_1);
            status = simple_add(value_1, value_2, result);
            set_sign(result, 1);
        } else if (sign1 && sign2) {
            s21_negate(value_2, &value_2);
            if (simple_greater(value_1, value_2)) {
                s21_negate(value_1, &value_1);
                simple_sub(value_1, value_2, result);
                set_sign(result, 1);
            } else {
                simple_sub(value_2, value_1, result);
            }
        }
        set_dec_scale(scale, result);
    } else {
        status = FAIL;
    }
    return status;
}

int main () {
    s21_decimal a, b;
    float A = -456456.3463;
    float B = -0.00021;
    printf("%f - %f = %.30f\n", A, B, A - B);
    s21_from_float_to_decimal(A, &a);
    s21_from_float_to_decimal(B, &b);
    print_decimal(a);
    print_decimal(b);

    s21_from_decimal_to_float(a, &A);
    s21_from_decimal_to_float(b, &B);
    printf("%f %f\n", A, B);
    s21_decimal result = ZERO_DECIMAL;
    s21_truncate(a, &result);
    print_decimal(result);
    float res;
    s21_from_decimal_to_float(result, &res);
    printf("%.30f\n", res);
    return 0;
}

//  00110000011101111011010110001101010111010011011110000011100100011001100110011001100110011001100
//  10010101111011010010111010000010111000100110101000011011000001010000000000000000000000000000000
//  11100111111111101111111100011111101111111111110110011110100101101001100110011001100110011001100 - my
//  11000110011001001110010000010000001111111010000110011110100101101001100110011001100110011001100 - true