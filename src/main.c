#include "s21_decimal.h"
#include "converters/s21_converters.h"
#include "helpers/s21_helpers.h"
#include "comparsion/s21_comparsion.h"
#include "other/s21_other.h"
#include "arithmetic/s21_arithmetic.h"
#include <time.h>

int main () {
<<<<<<< HEAD
    s21_decimal a, b;
    float A = 0.9902;
    float B = 7.377;
    // printf("round %.30f = %.30f\nfloor %.30f = %.30f\n", B, round(B), B, floorf(B));
    printf("%.30f * %.30f = %.30f\n", A, B, A * B);
    s21_from_float_to_decimal(A, &a);
    s21_from_float_to_decimal(B, &b);
    print_decimal(a);
    print_decimal(b);
    printf("?%d\t%d\n", a.type, b.type);
    s21_from_decimal_to_float(a, &A);
    s21_from_decimal_to_float(b, &B);
    printf("%.30f %.30f\n", A, B);

    print_decimal(a);
    print_decimal(b);
    s21_decimal result = ZERO_DECIMAL;
    s21_add(a, b, &result);
    print_decimal(result);
    float res;
    s21_from_decimal_to_float(result, &res);
    printf("%.30f\n", res);
    return 0;
=======
    float a = -2125252230.0;
    printf("%f", floorf(a));
    // s21_decimal A = ZERO_DECIMAL;
    // s21_from_int_to_decimal(a, &A);
    // set_dec_scale(1, &A);
    // s21_decimal res = ZERO_DECIMAL;
    // s21_truncate(A, &res);
    // print_decimal(res);
>>>>>>> 7a5a4e2e80fe3bf5b73943a1eeaa010e3ff6719e
}