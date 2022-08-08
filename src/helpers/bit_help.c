#include "s21_helpers.h"

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
