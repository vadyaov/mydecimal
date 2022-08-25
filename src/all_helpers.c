#include "s21_decimal.h"

int isBit(unsigned n, unsigned short pos) {
    return ((n & (1 << pos)) != 0);
}

int setBit(unsigned n, unsigned short pos) {
    return (n | (1 << pos));
}

int clearBit(unsigned n, unsigned short pos) {
    return (n & (~(1 << pos)));
}

int modBit(unsigned n, unsigned short pos, unsigned short bit) {
    return ((n & (~(1 << pos))) | (bit << pos));
}

void print_int_bits(unsigned num) {
    for (int i = 31; i >= 0; i--) {
        printf("%d", isBit(num, i));
        if (i == 24 || i == 16 || i == 8)
            printf(" ");
    }
}

// void print_64int_bits(unsigned long long num) {
//     for (int i = 63; i >= 0; i--) {
//         // printf("%d", isBit(num, i));
//         if (i == 32)
//             printf(" ");
//     }
// }

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

void init_decimal(s21_decimal *a) {
    a->bits[LOW] = a->bits[MID] =
    a->bits[HIGH] = a->bits[EXT] = 0;
    a->type = S21_NORMAL;
}

void decimal_pos_overflow(s21_decimal *a) {
    init_decimal(a);
    a->type = S21_INF;
}

void decimal_neg_overflow(s21_decimal *a) {
    init_decimal(a);
    a->type = S21_INF_NEG;
}

void decimal_nan_value(s21_decimal *a) {
    init_decimal(a);
    a->type = S21_NAN;
}

void cpy_decimal(s21_decimal src, s21_decimal *dst) {
    for (int i = LOW; i <= EXT; i++)
        dst->bits[i] = src.bits[i];
}

void set_sign(s21_decimal *dst, int sign) {
    dst->bits[EXT] = modBit(dst->bits[EXT], SIGNBIT, sign);
}

int check_sign(s21_decimal dst) {
    return (isBit(dst.bits[EXT], SIGNBIT));
}

int get_dec_scale(s21_decimal a) {
    unsigned int mask = (1U << 16);
    unsigned int stop = (1U << 23);
    int scale = 0;
    for (int i = 0; mask <= stop; mask <<= 1, i++)
        if (!!(mask & a.bits[EXT]))
            scale += pow(2, i);
    return scale;
}

void set_dec_scale(int scale, s21_decimal *a) {
    for (unsigned int mask = 1U, i = 16; i <= 23; mask <<= 1, i++)
            a->bits[EXT] = clearBit(a->bits[EXT], i);
    for (unsigned int mask = 1U, i = 16; i <= 23; mask <<= 1, i++)
        if (!!(scale & mask))
            a->bits[EXT] = setBit(a->bits[EXT], i);
}

int is_zero_mant(s21_decimal val) {
    return (val.bits[0] == 0
         && val.bits[1] == 0
         && val.bits[2] == 0);
}

int find_first_rbit(s21_decimal num) {
    int pos = 95;
    for (int i = HIGH; i >= LOW; i--) {
        for (int j = INT_BITS - 1; j >= 0; j--) {
            if (isBit(num.bits[i], j))
                return pos;
            pos--;
        }
    }
    return 0;
}

s21_decimal div10(s21_decimal in) {
    s21_decimal out = ZERO_DECIMAL;
    if (in.type == S21_NORMAL) {
        unsigned int remainder = 0;
        for (int i = HIGH; i >= LOW; i--) {
            unsigned long long tmp = ((unsigned long long)remainder << 32) | (unsigned int)in.bits[i];
            remainder = tmp % 10u;
            out.bits[i] = tmp / 10u;
        }
    }
    if (check_sign(in)) set_sign(&out, 1);
    return out;
}

s21_decimal mul10(s21_decimal in) {
    s21_decimal out = ZERO_DECIMAL;
    if (in.type == S21_NORMAL) {
        unsigned int carry = 0;
        for (int i = LOW; i <= HIGH; i++) {
            unsigned long long tmp = 0;
            tmp = (unsigned long long)in.bits[i] * 10u + carry;
            carry = tmp / 0x100000000;
            out.bits[i] = tmp % 0x100000000;
        }
        if (carry > 0) {
            init_decimal(&out);
            out.type = S21_INF;
        }
    }
    if (check_sign(in)) set_sign(&out, 1);
    return out;
}

int scale_low(s21_decimal *dec, unsigned int val) {
  int result = SUCCESS;
  unsigned int scale = get_dec_scale(*dec);
  if (val <= scale) {
    for (unsigned int n = 0; n < val; n++, scale--) {
      *dec = div10(*dec);
    }
    set_dec_scale(scale, dec);
  } else {
    result = FAIL;
  }
  return result;
}

int scale_up(s21_decimal *dec, unsigned int val) {
  int result = SUCCESS;
  unsigned int scale = get_dec_scale(*dec);
  s21_decimal dec_tmp = *dec;
  if ((scale + val) <= 28) {
    for (unsigned int n = 0; n < val; n++, scale++) {
      dec_tmp = mul10(dec_tmp);
      if (dec_tmp.type == S21_INF) {
        result = FAIL;
        break;
      }
    }
    if (!result) {
      *dec = dec_tmp;
      set_dec_scale(scale, dec);
    }
  } else {
    result = FAIL;
  }
  return result;
}

int is_normal_values(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int res = 1;
    if (value_1.type == S21_NAN || value_2.type == S21_NAN) {
        decimal_nan_value(result);
        res = 0;
    } else if (value_1.type == S21_INF) {
        if (value_2.type == S21_INF) {
            decimal_pos_overflow(result);
        } else if (value_2.type == S21_INF_NEG) {
            decimal_nan_value(result);
        }
        res = 0;
    } else if (value_1.type == S21_INF_NEG) {
        if (value_2.type == S21_INF) {
            decimal_nan_value(result);
        } else if (value_2.type == S21_INF_NEG) {
            decimal_neg_overflow(result);
        }
        res = 0;
    }
    /*} else if (value_2.type == S21_INF) {
        if (value_1.type == S21_INF) {
            decimal_pos_overflow(result);
        } else if (value_1.type == S21_INF_NEG) {
            decimal_nan_value(result);
        }
        res = 0;
    } else if (value_2.type == S21_INF_NEG) {
        if (value_1.type == S21_INF) {
            decimal_nan_value(result);
        } else if (value_1.type == S21_INF_NEG) {
            decimal_neg_overflow(result);
        }
        res = 0;
    }*/
    return res;
}

int simple_greater(s21_decimal value_1, s21_decimal value_2) {
    int res = 0;
    int pos1 = find_first_rbit(value_1);
    int pos2 = find_first_rbit(value_2);
    if (pos1 > pos2) {
        res = 1;
    } else if (pos1 < pos2) {
        res = 0;
    } else {
        int decision = 0;
        int j = pos1 % INT_BITS;
        for (int i = pos1 / INT_BITS; i >= LOW && !decision; i--) {
            for (; j >= 0 && !decision; j--) {
                int bit1 = isBit(value_1.bits[i], j);
                int bit2 = isBit(value_2.bits[i], j);
                if (bit1 != bit2) {
                    if (bit1 < bit2)
                        res = 0;
                    else
                        res = 1;
                    decision = 1;
                }
            }
            j = INT_BITS - 1;
        }
    }
    return res;
}

int simple_less(s21_decimal value_1, s21_decimal value_2) {
    return (!simple_greater(value_1, value_2));
}

int simple_equal(s21_decimal value_1, s21_decimal value_2) {
    int res = 1;
    for (int i = HIGH; i >= LOW && res; i--) {
        for (int j = INT_BITS - 1; j >= 0 && res; j--) {
            int bit1 = isBit(value_1.bits[i], j),
                bit2 = isBit(value_2.bits[i], j);
            if (bit1 != bit2) res = 0;
        }
    }
    return res;
}

int get_float_exp(float src) {
    unsigned int bit = (*(unsigned int *)&src) >> 23;
    int exp = 0;
    for (int i = 0; i < 8; i++)
        exp += pow(2, i) * isBit(bit, i);
    return exp - 127;
}

int bad_float(float src) {
    return (S21_IS_INF(src) || S21_IS_NAN(src));
}

void cpy_mantis_to_low_dec(float src, s21_decimal *dst) {
    unsigned int bit = (*(unsigned int *)&src);
    for (int i = 22; i >= 0; i--)
        if (isBit(bit, i))
            dst->bits[LOW] = setBit(dst->bits[LOW], i);
}

void shift_mant_left(s21_decimal *dst, int count) {
    while (count--) {
        shiftleft(dst);
    }
}

void shift_mant_right(s21_decimal *dst) {
    while (!isBit(dst->bits[LOW], 0))
        shiftright(dst);
}

void set_invisible(s21_decimal *dst, int pos) {
    dst->bits[LOW] = setBit(dst->bits[LOW], pos);
}

// int find_first_rbit(s21_decimal num) {
//     int pos = 95;
//     for (int i = HIGH; i >= LOW; i--) {
//         for (int j = INT_BITS - 1; j >= 0; j--) {
//             if (isBit(num.bits[i], j))
//                 return pos;
//             pos--;
//         }
//     }
//     return 0;
// }

int get_bit_string(long double res, char *bits, int exponent) {
    int mn = 0;
    if (exponent == 1 && !(unsigned int)res) mn = 28;
    else
        mn = 28 - exponent - 1;
    res *= powl(10.0L, (long double)(mn));
    res = roundl(res);
    for (int i = 0; res > 1e-6; i++) {
        res = floorl(res) / 2;
        if (res - floorl(res) > 1e-6)
            bits[i] = '1';
        else
            bits[i] = '0';
    }
    return mn;
}

void set_bits_from_string(char *bits, s21_decimal *result) {
    for (size_t i = strlen(bits) - 1; i < strlen(bits); i--)
        if (bits[i] - '0')
            result->bits[i / 32] = setBit(result->bits[i / 32], (i % 32));
}

int integer_part_count(long double num) {
    int exp = 0;
    while (num >= 1) {
        num /= 10;
        exp++;
    }
    return !exp ? 1 : exp;
}

int isBigExp(float exp) {return (exp > 95 || exp < -94);}

int count_int_part(float *src) {
    float _int;
    modff(*src, &_int);
    int count = 0;
    for (float _int_cp = _int; _int_cp >= 1.0;) {
        _int_cp /= 10.0;
        count++;
    }
    return count;
}

int multi10(float *src, int scale) {
    int integer = count_int_part(src);
    // printf("integer = %d\n", integer);
    // printf("SCALE = %d\n", scale);
    // printf("SRC = %.30f\n", *src);
    int ii = integer > 8 ? 0 : 8 - integer;
    long double srctmp = (long double)(*src);
    for (int i = 0; i < ii && scale < 28; i++) {
        int ex = get_float_exp(*src);
        if (ex > 95 || ex < -94) {
            srctmp /= 10.0L;
            break;
        }
        srctmp *= 10.0L;
        scale++;
    }
    // if (ii) {
    //     srctmp /= 10.0L;
    //     scale--;
    // }
    *src = srctmp;
    // printf("TMP = %.28Lf\n", srctmp);
    // printf("src = %.28f\n", *src);
    return scale;
}

void set1bit(s21_decimal *dst, int exp) {
    int pos = exp > 0 ? exp : abs(exp) - 1;
    if (exp < 32)
        dst->bits[0] = setBit(dst->bits[0], pos);
    else if (exp < 64)
        dst->bits[1] = setBit(dst->bits[1], pos - 32);
    else if (exp < 96)
        dst->bits[2] = setBit(dst->bits[2], pos - 64);
}

void put_mantiss_in_decimal(s21_decimal *dst, const char *str) {
    for (int i = 0; i < 32; i++) {
        if (str[i] == '1')
            dst->bits[0] = setBit(dst->bits[0], i);
    }
    for (int i = 32; i < 64; i++) {
        if (str[i] == '1')
        dst->bits[1] = setBit(dst->bits[1], i - 32);
    }
    for (int i = 64; i < 96; i++) {
        if (str[i] == '1')
        dst->bits[2] = setBit(dst->bits[2], i - 64);
    }
}

void put_exp_in_decimal(s21_decimal *dst, int e) {
    unsigned int bit = (*(unsigned int*)&e);
    unsigned int mask = 0x80000000;
    int position = 27;
    mask >>= position;
    int i = 20;
    while (position < 32) {
        if (!!(bit & mask))
            dst->bits[3] = setBit(dst->bits[3], i);
        position++;
        mask >>= 1;
        i--;
    }
}

void float_convert(s21_decimal *dst, float *src, int *scale, int exp) {
    unsigned int mask = 0x400000;
    unsigned int bit = *((unsigned int *)src);
    char dec_binStr[129];
    int i = 0;
    for (; i < 128; i++)
        dec_binStr[i] = '0';
    dec_binStr[i] = '\0';
    int start = exp - 1;
    for (; mask && start >= 0; mask >>= 1, start--) {
        if (!!(bit & mask)) dec_binStr[start] = '1';
    }
    put_mantiss_in_decimal(dst, dec_binStr);
    put_exp_in_decimal(dst, *scale);
}

int balance(s21_decimal *value_1, s21_decimal *value_2) {
    int scale1 = get_dec_scale(*value_1);
    int scale2 = get_dec_scale(*value_2);
    int scale_max = (scale1 >= scale2) ? scale1 : scale2;
    s21_decimal val1cpy = *value_1, val2cpy = *value_2;
    if (scale1 != scale_max) {
        while (scale1 != scale_max && !scale_up(&val1cpy, 1)) {
            if (val1cpy.type != S21_NORMAL) break;
            scale1 = get_dec_scale(val1cpy);
        }
        if (scale1 != scale2 || val1cpy.type != S21_NORMAL) {
            scale_up(value_1, (scale1 - get_dec_scale(*value_1)));
            while (scale1 != scale2 && !scale_low(value_2, 1)) {
                scale2 = get_dec_scale(*value_2);
            }
        } else {
            *value_1 = val1cpy;
        }
    } else if (scale2 != scale_max) {
        while (scale2 != scale_max && !scale_up(&val2cpy, 1)) {
            if (val2cpy.type != S21_NORMAL) break;
            scale2 = get_dec_scale(val2cpy);
        }
        if (scale1 != scale2 || val2cpy.type != S21_NORMAL) {
            scale_up(value_2, (scale2 - get_dec_scale(*value_2)));
            while (scale1 != scale2 && !scale_low(value_1, 1)) {
                scale1 = get_dec_scale(*value_1);
            }
        } else {
            *value_2 = val2cpy;
        }
    }
    return 0;
}

int shiftleft(s21_decimal *a) {
    int over = SUCCESS;
    int last_low_bit = isBit(a->bits[LOW], INT_BITS - 1);
    int last_mid_bit = isBit(a->bits[MID], INT_BITS - 1);
    int last_high_bit = isBit(a->bits[HIGH], INT_BITS - 1);
    a->bits[LOW] <<= 1;
    a->bits[MID] <<= 1;
    if (last_low_bit)
        a->bits[MID] = setBit(a->bits[MID], 0);
    a->bits[HIGH] <<= 1;
    if (last_mid_bit)
        a->bits[HIGH] = setBit(a->bits[HIGH], 0);
    if (last_high_bit) over = FAIL;
    return over;
}

int shiftright(s21_decimal *a) {
    int below = SUCCESS;
    int first_low_bit = isBit(a->bits[LOW], 0);
    int first_mid_bit = isBit(a->bits[MID], 0);
    int first_high_bit = isBit(a->bits[HIGH], 0);
    a->bits[HIGH] >>= 1;
    a->bits[MID] >>= 1;
    if (first_high_bit)
        a->bits[MID] = setBit(a->bits[MID], INT_BITS - 1);
    a->bits[LOW] >>= 1;
    if (first_mid_bit)
        a->bits[LOW] = setBit(a->bits[LOW], INT_BITS - 1);
    if (first_low_bit) below = FAIL;
    return below;
}
