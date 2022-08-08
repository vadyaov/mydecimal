#include "s21_helpers.h"

void print_int_bits(unsigned num) {
    for (int i = 31; i >= 0; i--) {
        printf("%d", isBit(num, i));
        if (i == 24 || i == 16 || i == 8)
            printf(" ");
    }
}

void print_64int_bits(unsigned long long num) {
    for (int i = 63; i >= 0; i--) {
        printf("%d", isBit(num, i));
        if (i == 32)
            printf(" ");
    }
}

void print_float_bits(float a) {
    unsigned int bits = *(unsigned int *)&a;
    printf("%d ", isBit(bits, INT_BITS - 1));
    for (int i = 30; i >= 23; i--)
        printf("%d", isBit(bits, i));
    printf(" ");
    for (int i = 22; i >= 0; i--)
        printf("%d", isBit(bits, i));
    printf("\n");
}

void print_decimal(s21_decimal n) {
    for (int i = EXT; i >= LOW; i--) {
       print_int_bits(n.bits[i]);
       printf("  ");
    }
    printf("\n");
}