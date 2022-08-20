#include "s21_decimal.h"
#include "converters/s21_converters.h"
#include "helpers/s21_helpers.h"
#include "comparsion/s21_comparsion.h"
#include "other/s21_other.h"
#include "arithmetic/s21_arithmetic.h"
#include <time.h>

int main () {
    float a = -2125252230.0;
    printf("%f", floorf(a));
    // s21_decimal A = ZERO_DECIMAL;
    // s21_from_int_to_decimal(a, &A);
    // set_dec_scale(1, &A);
    // s21_decimal res = ZERO_DECIMAL;
    // s21_truncate(A, &res);
    // print_decimal(res);
}