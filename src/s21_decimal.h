#ifndef SRC_S21_DECIMAL_H_
#define SRC_S21_DECIMAL_H_

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define S21_HUGE_VAL (__builtin_inff())
#define S21_NAN_VAL (__builtin_nanf(""))
#define S21_IS_INF(x) __builtin_isinf_sign(x)
#define S21_IS_NAN(x) __builtin_isnan(x)

#define ZERO_DECIMAL {{0, 0, 0, 0}, S21_NORMAL}
#define SIGNBIT 31
#define INT_BITS 32
#define MAX_DECIMAL 79228162514264337593543950335.0F
#define MIN_DECIMAL -79228162514264337593543950335.0F

typedef enum type {
    S21_NORMAL,
    S21_INF,
    S21_INF_NEG,
    S21_NAN
} dec_value_t;

typedef struct decimal {
    unsigned int bits[4];
    dec_value_t type;
} s21_decimal;

typedef enum {
    SUCCESS,
    CONVERT_ERROR,
    FAIL = 1,
    DATA_OVERFLOW
} error;

enum dec_bits {LOW, MID, HIGH, EXT};

enum sign {POSITIVE, NEGATIVE};

//  ARITHMETIC
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int simple_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int simple_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int simple_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int is_normal_values(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// COMPARSION
int s21_is_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater(s21_decimal value_1, s21_decimal value_2);
int s21_is_less(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2);

int simple_equal(s21_decimal value_1, s21_decimal value_2);
int simple_greater(s21_decimal value_1, s21_decimal value_2);
int simple_less(s21_decimal value_1, s21_decimal value_2);

// CONVERTERS
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
int find_first_rbit(s21_decimal num);
int get_bit_string(long double res, char *bits, int exponent);
void set_bits_from_string(char *bits, s21_decimal *result);
int integer_part_count(long double num);

int isBigExp(float exp);
void set1bit(s21_decimal *dst, int exp);
int multi10(float *src, int scale);
int count_int_part(float *src);
void float_convert(s21_decimal *dst, float *src, int *scale, int exp);
void put_mantiss_in_decimal(s21_decimal *dst, const char *str);
void put_exp_in_decimal(s21_decimal *dst, int e);

// OTHER
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_floor(s21_decimal value, s21_decimal *result);

// HELPERS
// bit
int isBit(unsigned n, unsigned short pos);
int setBit(unsigned n, unsigned short pos);
int clearBit(unsigned n, unsigned short pos);
int modBit(unsigned n, unsigned short pos, unsigned short bit);
// print
void print_int_bits(unsigned num);
void print_64int_bits(unsigned long long num);
void print_float_bits(float a);
void print_decimal(s21_decimal n);
// decimal
void init_decimal(s21_decimal *a);
void decimal_pos_overflow(s21_decimal *a);
void decimal_neg_overflow(s21_decimal *a);
void decimal_nan_value(s21_decimal *a);
void set_sign(s21_decimal *dst, int sign);
int check_sign(s21_decimal dst);
void set_dec_scale(int scale, s21_decimal *a);
int get_dec_scale(s21_decimal a);
void cpy_decimal(s21_decimal src, s21_decimal *dst);
int is_zero_mant(s21_decimal val);
int find_first_rbit(s21_decimal num);
int balance(s21_decimal *value_1, s21_decimal *value_2);
int scale_low(s21_decimal *dec, unsigned int val);
int scale_up(s21_decimal *dec, unsigned int val);
s21_decimal mul10(s21_decimal in);
s21_decimal div10(s21_decimal in);
// shifts
int shiftleft(s21_decimal *a);
int shiftright(s21_decimal *a);

#endif  // SRC_S21_DECIMAL_H_
