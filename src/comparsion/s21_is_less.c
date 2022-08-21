#include "s21_comparsion.h"

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
    int result = 0;
    if ((value_1.type == S21_INF && value_2.type == S21_INF) ||
        (value_1.type == S21_NAN || value_2.type == S21_NAN) ||
        (value_1.type == S21_INF_NEG && value_2.type == S21_INF_NEG)) {
        result = 0;
    } else if ((value_1.type == S21_INF_NEG &&
               (value_2.type == S21_INF || value_2.type == S21_NORMAL)) ||
               (value_1.type == S21_NORMAL && value_2.type == S21_INF)) {
        result = 1;
    } else if ((value_1.type == S21_INF) && (value_2.type == S21_INF_NEG)) {
        result = 0;
    } else if ((value_1.type == S21_INF && value_2.type == S21_NORMAL) ||
             (value_1.type == S21_NORMAL && value_2.type == S21_INF_NEG)) {
        result = 0;
    } else if (value_1.type == S21_NORMAL && value_2.type == S21_NORMAL) {
        int sign1 = check_sign(value_1),
            sign2 = check_sign(value_2);
        if (sign1 != sign2) {
            if (sign1 < sign2) {
                result = 0;
            } else {
                result = 1;
            }
        } else {
            balance(&value_1, &value_2);
            if (simple_equal(value_1, value_2)) {
                result = 0;
            } else {
                result = simple_less(value_1, value_2);
                if (sign1) result = !result;
            }
        }
    }
    return result;
}
