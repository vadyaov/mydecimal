#include "s21_decimal.h"
#include "converters/s21_converters.h"
#include "helpers/s21_helpers.h"
#include "comparsion/s21_comparsion.h"
#include "other/s21_other.h"
#include "arithmetic/s21_arithmetic.h"

int main () {
    s21_decimal a, b;
    int count_ok = 0, count_not = 0;
    float A = -9138.672456787213215545455;
    for (; A < 465.3134354256565; A += 127.56351351) {
    float B = A * (0.4567789789765451);

    // printf("round %.30f = %.30f\nfloor %.30f = %.30f\n", B, round(B), B, floorf(B));
    // printf("%.30f mod %.30f = %.30f\n", A, B, fmodf(A, B));
    s21_from_float_to_decimal(A, &a);
    s21_from_float_to_decimal(B, &b);
    // print_decimal(a);
    // print_decimal(b);

    s21_from_decimal_to_float(a, &A);
    s21_from_decimal_to_float(b, &B);
    // printf("%.30f %.30f\n", A, B);
    s21_decimal result = ZERO_DECIMAL;
    s21_mul(a, b, &result);
    // print_decimal(result);
    float res;
    s21_from_decimal_to_float(result, &res);
    printf("%.30f\n", res);
    printf("result: %.28f\n", A * B);
    if (res == A * B) count_ok++;
    else count_not++;
    }
    printf("%d\n%d", count_ok, count_not);
    return 0;
}