#include "s21_helpers.h"

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
    printf("OUT %d\n", out.type);
    print_decimal(out);
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

int balance(s21_decimal *value_1, s21_decimal *value_2) {
    unsigned int scale1 = get_dec_scale(*value_1);
    unsigned int scale2 = get_dec_scale(*value_2);
    unsigned int scale_max = (scale1 >= scale2) ? scale1 : scale2;
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
}
