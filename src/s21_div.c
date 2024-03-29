#include "s21_decimal.h"

int s21_div2(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
void count_div_part(s21_decimal value_1, s21_decimal value_2, s21_decimal *result, s21_decimal *res2);

#define setBit2(X, POS, BIT) ((X) |= (BIT << (POS)))

void prebalance_value2(s21_decimal value_1, s21_decimal *value_2) {
     while (simple_less(*value_2, value_1)) {
        shiftleft(value_2);
    }
    if (simple_greater(*value_2, value_1))
        shiftright(value_2);
}

int balance_value2(s21_decimal *value_2, s21_decimal result, int pos_begin) {
    int count = 0, pos_now = find_first_rbit(*value_2);;
    while (simple_greater(*value_2, result) && (pos_now >= pos_begin)) {
        shiftright(value_2);
        count++;
        pos_now = find_first_rbit(*value_2);
    }
    return count;
}

void str_convert(s21_decimal *result, char *mantis) {
    int j = 0, begin = strlen(mantis) - 1;
    for (; j < 3; j++) {
        int pos = 0;
        while (pos < 32 && begin > -1) {
            if (mantis[begin] == '0') setBit2(result->bits[j], pos, 0);
            else
                setBit2(result->bits[j], pos, 1);
            pos++;
            begin--;
        }
    }
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int status = 0;
    init_decimal(result);

    s21_decimal res2;  //  convert whole part from string to decimal, result is a fract part

    count_div_part(value_1, value_2, result, &res2);
    s21_decimal res3;

    float res_exp = 0.0;
    s21_from_decimal_to_float(*result, &res_exp);

    if (!is_zero_mant(*result)) {
        while (simple_greater(value_2, *result))
            scale_low(&value_2, 1);
        count_div_part(*result, value_2, result, &res3);
    }

    set_dec_scale(28, &res3);
    s21_from_decimal_to_float(res3, &res_exp);

    s21_add(res2, res3, result);

    return status = 0;
}

void count_div_part(s21_decimal value_1, s21_decimal value_2, s21_decimal *result, s21_decimal *res2) {
    int  count, i = 0;
    char mantis[128] = {'0'};

    balance(&value_1, &value_2);
    int pos_begin = find_first_rbit(value_2);

    prebalance_value2(value_1, &value_2);
    simple_sub(value_1, value_2, result);
    mantis[i++] = '1';

    if (simple_greater(value_2, *result)) {
        count = balance_value2(&value_2, *result, pos_begin);
        if (count > 1)
            while (count-- > 1)
                mantis[i++] = '0';
    }

    int pos_now = find_first_rbit(value_2);
    while (pos_now >= pos_begin) {
        if (simple_greater(*result, value_2)) {
            simple_sub(*result, value_2, result);
            mantis[i++] = '1';
        }
        if (simple_equal(*result, value_2)) {
            simple_sub(*result, value_2, result);
            mantis[i++] = '1';
            pos_now = find_first_rbit(value_2);
            while (pos_now > pos_begin) {  // если вал2 не на своем месте то смещать и добавлять 0
                shiftright(&value_2);
                mantis[i++] = '0';
                pos_now = find_first_rbit(value_2);
            }
        }
        if (simple_greater(value_2, *result)) {
            if (pos_now > pos_begin) {  // если вал2 не на своем месте то смещать и добавлять 0
                count = balance_value2(&value_2, *result, pos_begin);
                if (count > 1)
                    while (count-- > 1)
                        mantis[i++] = '0';
            } else {
                break;
            }
        }
        pos_now = find_first_rbit(value_2);
    }
    init_decimal(res2);
    str_convert(res2, mantis);
}
