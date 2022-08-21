#include "../s21_decimal.h"

int balance_sign_mul(s21_decimal *value_1, s21_decimal *value_2) {
    int status = 0, sign1 = check_sign(*value_1), sign2 = check_sign(*value_2);
    if ((!sign1 && sign2) || (sign1 && !sign2)) status = 1;
    if (sign1) clearBit(value_1->bits[3], 31);
    if (sign2) clearBit(value_2->bits[3], 31);
    return status;
}

int norm_mul(s21_decimal *value_1, s21_decimal *value_2, s21_decimal *sum) {
    int status = 0;
    int begin = 0, j = 0;
    int /*position1 = find_first_rbit(*value_1)*/ position2 =
        find_first_rbit(*value_2);
    int scale1 = get_dec_scale(*value_1), scale2 = get_dec_scale(*value_2);
    scale_low(value_1, scale1 - 10);
    scale_low(value_2, scale2 - 10);
    // даша, привет. j в цикле всегда 0, нигде нет j++;
    /* еще переменная begin может расти вплоть до 95(макс), функция isBit в случае
        когда begin > 31 работает некорректно */
    while (begin <= position2) {
        s21_decimal cat;
        init_decimal(&cat);
        int bit = isBit(value_2->bits[j], begin);
        if (bit) {
        cpy_decimal(*value_1, &cat);
        int count = begin;
        while (count-- > 0) {
            shiftleft(&cat);
        }
        status = simple_add(*sum, cat, sum);
        }
        begin++;
        if (begin > 31 && j == 0)
        j++;
        else if (begin > 63 && j == 1)
        j++;
    }
    return status;
}

int check_scale(s21_decimal value_1, s21_decimal value_2) {
    int status = 0, scale1 = get_dec_scale(value_1),
        scale2 = get_dec_scale(value_2);
    if ((scale1 > 28) || (scale2 > 28)) status = 1;
    return status;
}

void mul_neadekvat_value(s21_decimal value_1, s21_decimal value_2,
                         s21_decimal *result) {
    if (value_1.type == S21_INF) {
        if (value_2.type == S21_INF)
        result->type = S21_INF;
        else if (value_2.type == S21_NORMAL && !check_sign(value_2))
        result->type = S21_INF;
        else if (value_2.type == S21_NORMAL && check_sign(value_2))
        result->type = S21_INF_NEG;
        else if (value_2.type == S21_INF_NEG)
        result->type = S21_INF_NEG;
        else
        result->type = S21_NAN;
    } else if (value_1.type == S21_INF_NEG) {
        if (value_2.type == S21_INF)
        result->type = S21_INF_NEG;
        else if (value_2.type == S21_NORMAL && !check_sign(value_2))
        result->type = S21_INF_NEG;
        else if (value_2.type == S21_NORMAL && check_sign(value_2))
        result->type = S21_INF;
        else if (value_2.type == S21_INF_NEG)
        result->type = S21_INF;
        else
        result->type = S21_NAN;
    } else if (value_1.type == S21_NAN) {
        result->type = S21_NAN;
    }
}

// вернет 0 если типы децимал нормальные
// вернет 1 и поменяет result если типы не normal

int check_type(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int status = 0, number = 0;
    while (number == 0) {
        if (value_1.type == S21_INF)
        number = 1;
        else if (value_2.type == S21_INF)
        number = 2;
        else if (value_1.type == S21_INF_NEG)
        number = 1;
        else if (value_2.type == S21_INF_NEG)
        number = 2;
        else if (value_1.type == S21_NAN)
        number = 1;
        else if (value_2.type == S21_NAN)
        number = 2;
        else if (value_1.type == S21_NORMAL)
        number = 1;
    }
    if (number == 1 && value_1.type != S21_NORMAL) {
        mul_neadekvat_value(value_1, value_2, result);
        status++;
    } else if (number == 2 && value_2.type != S21_NORMAL) {
        mul_neadekvat_value(value_2, value_1, result);
        status++;
    }
    return status;
}

int check_adekvat_value(s21_decimal value_1, s21_decimal value_2,
                        s21_decimal *result) {
    int status = 0;
    status = check_scale(value_1, value_2) + check_type(value_1, value_2, result);
    return status;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int status = 0, status_negative = balance_sign_mul(&value_1, &value_2);
    status = check_adekvat_value(value_1, value_2, result);
    if (!status) {
        s21_decimal sum;
        init_decimal(&sum);
        init_decimal(result);
        if (!is_zero_mant(value_1) && !is_zero_mant(value_2)) {
        if (s21_is_greater(value_1, value_2)) {
            status = norm_mul(&value_1, &value_2, &sum);
        } else {
            status = norm_mul(&value_2, &value_1, &sum);
        }
        cpy_decimal(sum, result);
        result->bits[3] = 0;
        set_dec_scale(get_dec_scale(value_1) + get_dec_scale(value_2), result);
        }
        if (status_negative) set_sign(result, 1);
    }
    return status;
}
