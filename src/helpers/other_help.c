#include "s21_helpers.h"

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
