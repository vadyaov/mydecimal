#include "s21_comparsion.h"

int simple_greater(s21_decimal value_1, s21_decimal value_2) {
    if (simple_equal(value_1, value_2)) return 0;
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
                    if (bit1 < bit2) res = 0;
                    else res = 1;
                    decision = 1;
                }
            }
            j = INT_BITS - 1;
        }
    }
    return res;
}

int simple_less(s21_decimal value_1, s21_decimal value_2) {
    if (simple_equal(value_1, value_2)) return 0;
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
