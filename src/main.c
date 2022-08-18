#include "s21_decimal.h"
#include "converters/s21_converters.h"
#include "helpers/s21_helpers.h"
#include "comparsion/s21_comparsion.h"
#include "other/s21_other.h"
#include "arithmetic/s21_arithmetic.h"
#include <time.h>

#define s21_INFINITY 1/0.0
#define s21_NAN 0.0/0.0

void random_decimal(s21_decimal *value) {
    value->type = rand() % 4;
    for (unsigned int i = 0; i < 3; i++)
        value->bits[i] = (rand() % 100) * 0.3456;
    value->bits[3] = rand() % 27;
}

int main () {
        s21_decimal dst;
    float f1 = 4.2;
    printf("%.28f\n", f1);
    s21_from_float_to_decimal(f1, &dst);

    s21_decimal dst2;
    float f2 = 2.0;
    printf("%.28f\n", f2);
    s21_from_float_to_decimal(f2, &dst2);

    s21_decimal result;
    s21_div(dst, dst2, &result);

    float resu = 0.0;
    s21_from_decimal_to_float(result, &resu);
    printf("result: %.30f\nres: %.30f", resu, (double) f1 / (double) f2);
    // srand(time(NULL));
    // s21_decimal a, b;
    // int count_ok = 0, count_not = 0;
    
    // s21_decimal result = ZERO_DECIMAL;
    // float a1 = -10.56789;
    // for (; a1 < 12.0823; a1 += 4.32486) {
    // float b1 = a1 * 0.5622;
    // s21_from_float_to_decimal(a1, &a);
    // s21_from_float_to_decimal(b1, &b);
    //     s21_mul(a, b, &result);
    // float a2, b2;
    // s21_from_decimal_to_float(a, &a2);
    // s21_from_decimal_to_float(b, &b2);
    // printf("before\na: %.30f\nafter\na: %.30f\n", a1, a2);
    // printf("before\nb: %.30f\nafter\nb: %.30f\n", b1, b2);
    //     float res;
    //     s21_from_decimal_to_float(result, &res);
    //     printf("%.30f\n", res);
    //     printf("%.30f\n", a1 * b1);
    // if (res == a1 * b1) count_ok++;
    // else count_not++;
    // printf("%d\n%d", count_ok, count_not);
    // }
    return 0;
}