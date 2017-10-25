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

/* 32/17 as double, used in division algorithm */
#define K2          0x3ffe1e1e1e1e1e1e

/* 3/2 as a double, used in square root algorithm */
#define K3          0x3ff8000000000000

#define DIV_ITERS   4   /* Number of Newton iterations needed for divide */
#define SQRT_ITERS  3   /* Number of Newton iterations needed for square root */

typedef struct {
    uint64_t mant : MANT_BITS, exp : EXP_BITS, sign : SIGN_BITS;
} my_double;

typedef struct {
    uint64_t upper;
    uint64_t lower;
} uint128_t;

static const my_double my_nan  = { .sign = 0,.exp = EXP_MAX,.mant = 1 };
static const my_double my_zero = { .sign = 0,.exp = 0,      .mant = 0 };

double my_double_to_double(my_double d) {
    return *((double*)(&d));
}

my_double double_to_my_double(double d) {
    return *((my_double*)(&d));
}

my_double ui_to_d(uint64_t ui) {
    return *((my_double*)(&ui));
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
        result = my_zero;
    }
    else if (!op2.exp && !op2.mant) {
        result = op1;
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
            result = my_nan;
        }
    }
    else if (!op2.exp && !op2.mant) {
        result = my_zero;
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
            result.exp  = EXP_MAX;
            result.mant = 0;
        }
        else if (s_exp < 0) {
            result = my_zero;
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
    my_double result;
    result.sign = op1.sign ^ op2.sign;
    if (!op2.exp && !op2.mant) {
        result = my_nan;
    }
    else if (op1.exp == EXP_MAX) {
        if (op1.mant || (op2.exp == EXP_MAX)) {
            result = my_nan;
        }
        else {
            result.exp  = EXP_MAX;
            result.mant = 0;
        }
    }
    else if (op2.exp == EXP_MAX) {
        if (op2.mant) {
            result = my_nan;
        }
        else {
            result = my_zero;
        }
    }
    else if (!op1.exp && !op1.mant) {
        result = my_zero;
    }
    else {
        op1.sign = 0;
        op2.sign = 0;
        op1.exp = op1.exp - op2.exp - 1 + EXP_BIAS;
        op2.exp = EXP_BIAS - 1;

        my_double k1  = ui_to_d(K1);
        my_double k2  = ui_to_d(K2);
        my_double two = ui_to_d(0x4000000000000000);

        my_double recip = my_sub(k1, my_mul(k2, op2));
        for (int i = 0; i < DIV_ITERS; ++i) {
            my_double temp  = my_mul(op2, recip);
            my_double temp2 = my_sub(two, temp);
            recip = my_mul(recip, temp2);
        }

        result = my_mul(op1, recip);
    }
    
    return result;
}

/* 
 * Beautiful fast square root algorithm courtesy of Quake III source at
 * https://github.com/id-Software/Quake-III-Arena/blob/master/code/game/q_math.c#L552 
 */
my_double my_sqrt(my_double op) {
    my_double result;
    if (op.exp == EXP_MAX) {
        result = op;
    }
    else if (op.sign) {
        result = my_nan;
    }
    else {
        my_double x2 = op;
        x2.exp--;
        my_double temp = op;
        uint64_t i = *((uint64_t*)(&temp));
        i = 0x5FE6EB50C7B537A9 - (i >> 1);
        temp = ui_to_d(i);
        my_double k3 = ui_to_d(K3);
        for (int i = 0; i < SQRT_ITERS; ++i) {
            result = my_mul(x2,     temp  );
            result = my_mul(result, temp  );
            result = my_sub(k3,     result);
            result = my_mul(temp,   result);
            temp = result;
        }
        result = my_mul(op, result);
    }
    
    return result;
}

int main(int argc, char* argv[]) {
    double op1_d = strtod(argv[1], NULL);
    my_double op1 = double_to_my_double(op1_d);
    double op2_d = strtod(argv[2], NULL);
    my_double op2 = double_to_my_double(op2_d);
    my_double result;

    result = my_add(op1, op2);
    printf("\t%f + %f = %f\n", op1_d, op2_d, my_double_to_double(result));

    result = my_sub(op1, op2);
    printf("\t%f - %f = %f\n", op1_d, op2_d, my_double_to_double(result));

    result = my_mul(op1, op2);
    printf("\t%f * %f = %f\n", op1_d, op2_d, my_double_to_double(result));

    result = my_div(op1, op2);
    printf("\t%f / %f = %f\n", op1_d, op2_d, my_double_to_double(result));

    result = my_sqrt(op1);
    printf("\tsqrt(%f) = %f\n", op1_d, my_double_to_double(result));
}
