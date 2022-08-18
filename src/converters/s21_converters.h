#include "../s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

int bad_float(float src);
int get_float_exp(float src);
void cpy_mantis_to_low_dec(float src, s21_decimal *dst);
void shift_mant_right(s21_decimal *dst);
void shift_mant_left(s21_decimal *dst, int count);
void set_invisible(s21_decimal *dst, int pos);
// int find_first_rbit(s21_decimal num);
int get_bit_string(long double res, char *bits, int exponent);
void set_bits_from_string(char *bits, s21_decimal *result);
int integer_part_count(long double num);