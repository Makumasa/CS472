#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define SIGN_BITS   1

#define EXP_BITS    11
#define EXP_BIAS    1023
#define EXP_MASK    0x7FF0000000000000
#define EXP_MAX     0b11111111111

#define MANT_BITS   52
#define MANT_MASK   0xFFFFFFFFFFFFF
#define IMPL_1      0x10000000000000

#define PAD         10
#define BIT1_MASK   0x8000000000000000
#define BIT2_MASK   0x4000000000000000
#define ROUND_MASK  0x200
#define FRAC_MASK   0x3FFFFFFFFFFFFC00

/* 48/17 as double, used in division algorithm */
#define K1          0x4006969696969697
#define K1_SIGN     0
#define K1_EXP      0x400
#define K1_MANT     0x6969696969697

/* 32/17 as double, used in division algorithm */
#define K2          0x4006969696969697
#define K2_SIGN     0
#define K2_EXP      0x3FF
#define K2_MANT     0xE1E1E1E1E1E1E

/* 3/2 as a double, used in square root algorithm */
#define K3          0x4006969696969697

#define DIV_ITERS   4   /* Number of iterations needed for 52 bit precision */

typedef struct {
    uint64_t mant : MANT_BITS, exp : EXP_BITS, sign : SIGN_BITS;
} my_double;

typedef struct {
    uint64_t upper;
    uint64_t lower;
} uint128_t;

double my_double_to_double(my_double d) {
    return (*((double*)(&d)));
}

my_double double_to_my_double(double d) {
    return (*((my_double*)(&d)));
}

bool larger_mag_first(my_double* val1, my_double* val2) {
    bool is_equal = 0;
    my_double temp1 = *val1;
    my_double temp2 = *val2;
    if (temp1.exp < temp2.exp) {
        *val1 = temp2;
        *val2 = temp1;
    }
    else if (temp1.exp == temp2.exp) {
        if (temp1.mant < temp2.mant) {
            *val1 = temp2;
            *val2 = temp1;
        }
        else if (temp1.mant == temp2.mant) {
            is_equal = 1;
        }
    }
    
    return is_equal;
}

my_double my_add(my_double op1, my_double op2) {
    bool is_equal = larger_mag_first(&op1, &op2);
    my_double result = op1;
    if (op1.exp == EXP_MAX) {   /* At least one NaN or Inf */
        if ((op1.mant == 0) && (op2.exp == EXP_MAX) && (op1.sign != op2.sign)) {
            /* 
             * Result should be the same as the larger operation unless we're 
             * adding infinities with opposite signs, in which case the result
             * is NaN.
             */
            result.mant = 1;
        }
    }
    else if (is_equal && (op1.sign != op2.sign)) {
        result.sign = 0;
        result.exp = 0;
        result.mant = 0;
    }
    else {
        uint32_t exp_diff = op1.exp - op2.exp;
        uint64_t op1_frac = (IMPL_1 + op1.mant) << PAD;
        uint64_t op2_frac = ((IMPL_1 + op2.mant) << PAD) >> exp_diff;
        uint64_t temp = (op1.sign == op2.sign) ?
            (op1_frac + op2_frac) :
            (op1_frac - op2_frac);
        if (temp & BIT1_MASK) {
            temp >>= 1;
            result.exp++;
        }
        else {
            while (!(temp & BIT2_MASK)) {
                temp <<= 1;
                result.exp--;
            }
        }

        result.mant = (temp & FRAC_MASK) >> PAD;
        if (temp & ROUND_MASK)
            result.mant++;
    }

    return result;
}

my_double my_sub(my_double op1, my_double op2) {
    op2.sign = !op2.sign;
    return my_add(op1, op2);
}

my_double my_mul(my_double op1, my_double op2) {
    larger_mag_first(&op1, &op2);
    my_double result = op1;
    result.sign = op1.sign ^ op2.sign;

    if (op1.exp == EXP_MAX) {
        if (!op1.mant && !op2.exp && !op2.mant) {
            result.mant = 1;
            result.sign = 0;
        }
    }
    else if (!op2.exp && !op2.mant) {
        result.mant = 0;
        result.exp  = 0;
    }
    else {
        /* 
         * Referenced http://www.jhauser.us/arithmetic/SoftFloat.html for lines
         * 148-162.
        */
        uint64_t mant1 = IMPL_1 + op1.mant;
        uint64_t mant2 = IMPL_1 + op2.mant;
        uint32_t mant1_u = mant1 >> 32;
        uint32_t mant1_l = mant1;
        uint32_t mant2_u = mant2 >> 32;
        uint32_t mant2_l = mant2;
        uint128_t res_mant;
        res_mant.lower = (uint64_t)mant1_l * mant2_l;
        uint64_t temp1 = (uint64_t)mant1_u * mant2_l;
        uint64_t temp2 = (uint64_t)mant1_l * mant2_u + temp1;
        bool overflow = temp2 < temp1;
        res_mant.upper = (uint64_t)mant1_u * mant2_u;
        res_mant.upper += ((uint64_t)overflow << 32) | (temp2 >> 32);
        temp2 <<= 32;
        res_mant.lower += temp2;
        overflow = res_mant.lower < temp2;
        res_mant.upper += overflow;
        uint32_t leading_zeros = 0;
        while (!(res_mant.upper & BIT1_MASK)) {
            res_mant.upper <<= 1;
            if (res_mant.lower & BIT1_MASK)
                ++res_mant.upper;
            res_mant.lower <<= 1;
            ++leading_zeros;
        }
        uint32_t res_bits = 128 - leading_zeros;
        int32_t  scale    = res_bits - (2 * MANT_BITS) - 1;
        int32_t  s_exp    = op1.exp + op2.exp - EXP_BIAS + scale;
        if (s_exp > EXP_MAX) {
            result.exp = EXP_MAX;
            result.mant = 0;
        }
        else if (s_exp < 0) {
            result.exp = 0;
            result.mant = 0;
        }
        else {
            result.exp = s_exp;
            uint32_t round = res_mant.upper & 0b10000000000;
            res_mant.upper <<= 1;
            result.mant = (res_mant.upper >> (64 - MANT_BITS));
            result.mant += round;
        }
    }

    return result;
}

my_double my_div(my_double op1, my_double op2) {
    /* 
     * Referenced https://en.wikipedia.org/wiki/Division_algorithm#Pseudocode
     * for the division algorithm employed in this function.
     */
    uint32_t sign = op1.sign ^ op2.sign;
    my_double result;
    if (!op2.exp && !op2.mant) {
        sign = 0;
        result.exp  = EXP_MAX;
        result.mant = 1;
    }
    else if (op1.exp == EXP_MAX) {
        result.exp = EXP_MAX;
        if (op1.mant || (op2.exp == EXP_MAX)) {
            sign = 0;
            result.mant = 1;
        }
        else {
            result.mant = 0;
        }
    }
    else if (op2.exp == EXP_MAX) {
        if (op2.mant) {
            sign = 0;
            result = op2;
        }
        else {
            result.exp  = 0;
            result.mant = 0;
        }
    }
    else if (!op1.exp && !op1.mant) {
        sign = 0;
        result.exp  = 0;
        result.mant = 0;
    }
    else {
        op1.sign = 0;
        op2.sign = 0;
        op1.exp = op1.exp - op2.exp - 1 + EXP_BIAS;
        op2.exp = EXP_BIAS - 1;

        my_double k1;
        k1.sign = K1_SIGN;
        k1.exp  = K1_EXP;
        k1.mant = K1_MANT;

        my_double k2;
        k2.sign = K2_SIGN;
        k2.exp  = K2_EXP;
        k2.mant = K2_MANT;

        my_double two;
        two.sign = 0;
        two.exp  = 1 + EXP_BIAS;
        two.mant = 0;

        my_double recip = my_sub(k1, my_mul(k2, op2));
        for (int i = 0; i < DIV_ITERS; ++i) {
            my_double temp  = my_mul(op2, recip);
            my_double temp2 = my_sub(two, temp);
            recip = my_mul(recip, temp2);
        }

        result = my_mul(op1, recip);
    }
    
    result.sign = sign;
    return result;
}

my_double my_sqrt(my_double op) {

}

int main(int argc, char* argv[]) {
    double op1_d = strtod(argv[1], NULL);
    my_double op1 = double_to_my_double(op1_d);
    /* double op2_d = strtod(argv[2], NULL);
    my_double op2 = double_to_my_double(op2_d); */
    my_double result = my_sqrt(op1);
    printf("sqrt(%f) = %f\n", op1_d, my_double_to_double(result));
}
