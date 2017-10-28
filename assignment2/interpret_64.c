#include <math.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "mt19937-64.h"

#define NUM_CHARS 8

typedef union {
    uint64_t bits;
    double   d;
    int64_t  l;
    char     c[8];
} bit_pattern;

int main() {
    const char* n_strings[NUM_CHARS] = {
        "first",
        "second",
        "third",
        "fourth",
        "fifth",
        "sixth",
        "seventh",
        "eighth"
    };

    init_genrand64(time(NULL));
    bit_pattern val;
    val.bits = genrand64_int64();
    int exp;
    double result = frexp(val.d, &exp);
    bool negative_d = result < 0;
    double mantissa = 2 * fabs(result);
    exp--;
    bool negative_l = val.l < 0;
    
    printf("A 64-bit value has been generated using the Mersenne Twister.\n\n");
    printf("If we interpret this bit pattern as a double:\n");
    printf("\t%-26s%f\n", "Its mantissa is:", mantissa);
    if (negative_d)
        printf("\t%-26s1 (negative)\n", "Its sign is:");
    else
        printf("\t%-26s0 (positive)\n", "Its sign is:");
    printf("\t%-26s%d\n\n", "Its exponent is:", exp);

    printf("If we interpret this bit pattern as a long:\n");
    printf("\t%-26s%d\n", "Its value is:", abs(val.l));
    if (negative_l)
        printf("\t%-26s1 (negative)\n\n", "Its sign is:");
    else
        printf("\t%-26s0 (positive)\n\n", "Its sign is:");

    printf("If we interpret this bit pattern as 8 characters:\n");
    for (int i = 0; i < NUM_CHARS; ++i) {
        char s[80];
        sprintf(s, "The %s character is:", n_strings[i]);
        printf("\t%-26s'%c'\n", s, val.c[i]);
    }

    return 0;
}
