#include "../s21_decimal.h"

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

// shifts
int shiftleft(s21_decimal *a);
int shiftright(s21_decimal *a);