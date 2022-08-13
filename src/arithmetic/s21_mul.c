#include "../s21_decimal.h"

int balance_sign_mul(s21_decimal *value_1, s21_decimal *value_2) {
    int status = 0, sign1 = check_sign(*value_1), sign2 = check_sign(*value_2);
    if ((!sign1 && sign2) || (sign1 && !sign2))
        status = 1;
    if (sign1) clearBit(value_1->bits[3], 31);
    if (sign2) clearBit(value_2->bits[3], 31);
    return status;
}

int norm_mul(s21_decimal *value_1, s21_decimal *value_2, s21_decimal *sum) {
    int status = 0;
    int begin = 0, j = 0;
    int position1 = find_first_rbit(*value_1), position2 = find_first_rbit(*value_2);
    printf("pos1 = %d  pos2 = %d\n", position1, position2);
    // даша, привет. j в цикле всегда 0, нигде нет j++;
    /* еще переменная begin может расти вплоть до 95(макс), функция isBit в случае когда
       begin > 31 работает некорректно */
    while (begin <= position2) {
        s21_decimal cat;
        init_decimal(&cat);
        int bit = isBit(value_2->bits[j], begin);
        printf("bit = %d\n", bit);
        if (bit) {
            cpy_decimal(*value_1, &cat);
            int count = begin;
            while(count-- > 0) {
                shiftleft(&cat);
            }
            status = simple_add(*sum, cat, sum);
        }
        begin++;
    }
    return status;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int status = 0, status_negative = balance_sign_mul(&value_1, &value_2);
    s21_decimal sum;
    init_decimal(&sum);
    init_decimal(result);
    if (!is_zero_mant(value_1) && !is_zero_mant(value_2)) {
        if (s21_is_greater(value_1, value_2)) {
            status = norm_mul(&value_1, &value_2, &sum);
        } else
            status = norm_mul(&value_2, &value_1, &sum);
        cpy_decimal(sum, result);
        result->bits[3] = 0;
        set_dec_scale(get_dec_scale(value_1) + get_dec_scale(value_2), result);
    }
    if (status_negative) set_sign(result, 1);
    return status;
}
