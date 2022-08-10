#include "s21_decimal.h"
#include "converters/s21_converters.h"
#include "helpers/s21_helpers.h"
#include "comparsion/s21_comparsion.h"
#include "other/s21_other.h"
#include "arithmetic/s21_arithmetic.h"

int main () {
    s21_decimal a, b;
    float A = -12.0;
    float B = -3.0;
    printf("round %.30f = %.30f\nfloor %.30f = %.30f\n", B, round(B), B, floorf(B));
    printf("%.30f mod %.30f = %.30f\n", A, B, fmodf(A, B));
    s21_from_float_to_decimal(A, &a);
    s21_from_float_to_decimal(B, &b);
    print_decimal(a);
    print_decimal(b);

    s21_from_decimal_to_float(a, &A);
    s21_from_decimal_to_float(b, &B);
    printf("%.30f %.30f\n", A, B);
    s21_decimal result = ZERO_DECIMAL;
    s21_mod(a, b, &result);
    print_decimal(result);
    float res;
    s21_from_decimal_to_float(result, &res);
    printf("%.30f\n", res);
    return 0;
}