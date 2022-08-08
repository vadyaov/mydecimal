#include "s21_comparsion.h"

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
    int result = 0;
    if ((value_1.type == S21_INF && value_2.type == S21_INF) ||
        (value_1.type == S21_INF_NEG && value_2.type == S21_INF_NEG)) {
        result = 1;
    } else if ((value_1.type == S21_NAN || value_2.type == S21_NAN) ||
               (value_1.type == S21_NORMAL && value_2.type != S21_NORMAL) ||
               (value_1.type != S21_NORMAL && value_2.type == S21_NORMAL)) {
        result = 0;
    } else if (value_1.type == S21_NORMAL && value_2.type == S21_NORMAL) {
        if (is_zero_mant(value_1)) set_sign(&value_1, 0);  // избавляюсь от -0 надеюсь это правильно
        if (is_zero_mant(value_2)) set_sign(&value_2, 0);
        int sign1 = check_sign(value_1),
            sign2 = check_sign(value_2);
        if (sign1 == sign2) {
            balance(&value_1, &value_2);
            result = simple_equal(value_1, value_2);
        } else {
            result = 0;
        }
    }
    return result;
}
