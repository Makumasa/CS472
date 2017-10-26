#include <stdio.h>
#include <stdlib.h>
#include "my_double.h"
#include "mt19937-64.h"

extern my_double my_add(my_double op1, my_double op2);
extern my_double my_sub(my_double op1, my_double op2);
extern my_double my_div(my_double op1, my_double op2);
extern my_double my_mul(my_double op1, my_double op2);
extern my_double my_sqrt(my_double op);

double my_double_to_double(my_double d) {
    return *((double*)(&d));
}

my_double double_to_my_double(double d) {
    return *((my_double*)(&d));
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
