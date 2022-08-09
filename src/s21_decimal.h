#ifndef S21_DECIMAL_H_
#define S21_DECIMAL_H_

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define S21_HUGE_VAL (__builtin_inff())
/**
  * returns float NaN value
  */
#define S21_NAN_VAL (__builtin_nanf(""))
/**
  * check for infinity: returns 1 if infinite, -1 if -infinite and 0 if finite
  */
#define S21_IS_INF(x) __builtin_isinf_sign(x)
/**
 * check for nan value: returns 1 if NaN and 0 if not 
 */
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

#include "arithmetic/s21_arithmetic.h"
#include "converters/s21_converters.h"
#include "comparsion/s21_comparsion.h"
#include "helpers/s21_helpers.h"
#include "other/s21_other.h"

#endif // S21_DECIMAL_H_
