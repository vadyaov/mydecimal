#include "s21_decimal.h"
#include "helpers/s21_helpers.h"

int main () {
    float a = 0 * S21_HUGE_VAL;
    unsigned int bitfl = (*(unsigned int *)&a);
    print_int_bits(bitfl);
    return 0;
}