#include <math.h>
#include <float.h>
#include <stdio.h>
#include <stdlib.h>

#define D_TO_UI(d)          (*((unsigned long*)(&d)))
#define UI_TO_D(ui)         (*((double*)(&ui)))

#define NUM_BITS            64ul
#define SIGN_BITS           1ul
#define EXP_BITS            11ul
#define FRAC_BITS           52ul

#define EXP_MAX             0b11111111111ul
#define EXP_MASK            0x7FF0000000000000ul
#define EXP_SHIFT           (NUM_BITS - SIGN_BITS - EXP_BITS)
#define EXP_BIAS            1023ul
#define GET_EXP_BITS(ui)    ((ui & EXP_MASK) >> EXP_SHIFT)
#define EXP_ZERO            (EXP_BIAS << EXP_SHIFT)
#define SET_EXP(ui)         ((ui & ~EXP_MASK) | EXP_ZERO)

#define FRAC_MASK           0xFFFFFFFFFFFFF
#define FRAC_SHIFT          0
#define GET_FRAC_BITS(ui)   ((ui & FRAC_MASK) >> FRAC_SHIFT)

#define DENORMAL_VAL        pow(10, (DBL_MIN_10_EXP - 1))
#define HUGE_DOUBLE         pow(2, (DBL_MAX_EXP -1))
#define PI                  3.1415926535

double my_frexp(double x, int* exp) {
    unsigned long   bits        = D_TO_UI(x);
    unsigned long   exp_bits    = GET_EXP_BITS(bits);
    unsigned long   frac_bits   = GET_FRAC_BITS(bits);
    unsigned long   temp        = SET_EXP(bits);
    int             exponent    = (int)exp_bits - EXP_BIAS + 1;
    double fraction;
    

    if (isinf(x) || isnan(x)) {  /* Infinity or NaN */
        exponent = 0;
        fraction = x;
    }
    else if (exp_bits == 0) {
        if (frac_bits == 0) {   /* Zero */
            exponent = 0;
            fraction = x;
        }
        else {  /* Denormal */
            fraction = UI_TO_D(temp);
            (fraction < 0) ? fraction++ : fraction--; /* Remove leading 1 */
            while (fabs(fraction) < 0.5) {
                fraction *= 2;
                --exponent;
            }
        }
    }
    else {  /* Normal */
        fraction = UI_TO_D(temp) / 2;
    }

    *exp = exponent;
    return fraction;
}

int main(int argc, char* argv[])
{
    double test_values[] = {
        DENORMAL_VAL,
        -DENORMAL_VAL,
        0.0,
        -0.0,
        INFINITY,
        -INFINITY,
        NAN,
        PI,
        -PI,
        HUGE_DOUBLE,
        -HUGE_DOUBLE
    };

    int num_values = sizeof(test_values) / sizeof(test_values[0]);
    for (int i = 0; i < num_values; ++i) {
        int exp1, exp2;
        double input  = test_values[i];
        double frac1  = frexp(input, &exp1);
        double frac2  = my_frexp(input, &exp2);

        printf("   frexp(%g, &e) = %g: %g * %d^%d = %g\n",
            input, frac1, frac1, FLT_RADIX, exp1, input);
        printf("my_frexp(%g, &e) = %g: %g * %d^%d = %g\n\n",
            input, frac2, frac2, FLT_RADIX, exp2, input);
    }

    return 0;
}
