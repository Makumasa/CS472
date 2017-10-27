#include <sys/time.h>
#include <sys/resource.h>
#include <time.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include "my_double.h"
#include "mt19937-64.h"

#define FP_ITERATIONS       1000000
#define MY_FP_ITERATIONS    10000

extern my_double my_add(my_double op1, my_double op2);
extern my_double my_sub(my_double op1, my_double op2);
extern my_double my_div(my_double op1, my_double op2);
extern my_double my_mul(my_double op1, my_double op2);
extern my_double my_sqrt(my_double op);

extern double add_d(double op1, double op2);
extern double sub_d(double op1, double op2);
extern double mul_d(double op1, double op2);
extern double div_d(double op1, double op2);
extern double sqrt_d(double op);

int main(int argc, char* argv[]) {
    
    init_genrand64(time(NULL));
    uint64_t op1_ui = genrand64_int64();
    uint64_t op2_ui = genrand64_int64();
    double op1 = *((double*)(&op1_ui));
    double op2 = *((double*)(&op2_ui));
    my_double my_op1 = *((my_double*)(&op1_ui));
    my_double my_op2 = *((my_double*)(&op2_ui));
    struct rusage usage;
    struct timeval start, end;

    /**************************************************************************/
    /*                           FP OPERATIONS                                */
    /**************************************************************************/

    getrusage(RUSAGE_SELF, &usage);
    start = usage.ru_utime;
    for (volatile int i = 0; i < FP_ITERATIONS; ++i) {
        add_d(op1, op2);
        add_d(op1, op2);
        add_d(op1, op2);
        add_d(op1, op2);
        add_d(op1, op2);
        add_d(op1, op2);
        add_d(op1, op2);
        add_d(op1, op2);
        add_d(op1, op2);
        add_d(op1, op2);
        add_d(op1, op2);
        add_d(op1, op2);
        add_d(op1, op2);
        add_d(op1, op2);
        add_d(op1, op2);
        add_d(op1, op2);
        add_d(op1, op2);
        add_d(op1, op2);
        add_d(op1, op2);
        add_d(op1, op2);
        add_d(op1, op2);
        add_d(op1, op2);
        add_d(op1, op2);
        add_d(op1, op2);
        add_d(op1, op2);
        add_d(op1, op2);
        add_d(op1, op2);
        add_d(op1, op2);
        add_d(op1, op2);
        add_d(op1, op2);
        add_d(op1, op2);
        add_d(op1, op2);
        add_d(op1, op2);
        add_d(op1, op2);
        add_d(op1, op2);
        add_d(op1, op2);
        add_d(op1, op2);
        add_d(op1, op2);
        add_d(op1, op2);
        add_d(op1, op2);
    }
    getrusage(RUSAGE_SELF, &usage);
    end = usage.ru_utime;
    uint64_t temp = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
    getrusage(RUSAGE_SELF, &usage);
    start = usage.ru_utime;
    for (volatile int i = 0; i < FP_ITERATIONS; ++i) {
        add_d(op1, op2);
        add_d(op1, op2);
        add_d(op1, op2);
        add_d(op1, op2);
        add_d(op1, op2);
        add_d(op1, op2);
        add_d(op1, op2);
        add_d(op1, op2);
        add_d(op1, op2);
        add_d(op1, op2);
        add_d(op1, op2);
        add_d(op1, op2);
        add_d(op1, op2);
        add_d(op1, op2);
        add_d(op1, op2);
        add_d(op1, op2);
        add_d(op1, op2);
        add_d(op1, op2);
        add_d(op1, op2);
        add_d(op1, op2);
    }
    getrusage(RUSAGE_SELF, &usage);
    end = usage.ru_utime;
    double addusec = (temp - ((end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec))) / (FP_ITERATIONS / 50.0);

    getrusage(RUSAGE_SELF, &usage);
    start = usage.ru_utime;
    for (volatile int i = 0; i < FP_ITERATIONS; ++i) {
        sub_d(op1, op2);
        sub_d(op1, op2);
        sub_d(op1, op2);
        sub_d(op1, op2);
        sub_d(op1, op2);
        sub_d(op1, op2);
        sub_d(op1, op2);
        sub_d(op1, op2);
        sub_d(op1, op2);
        sub_d(op1, op2);
        sub_d(op1, op2);
        sub_d(op1, op2);
        sub_d(op1, op2);
        sub_d(op1, op2);
        sub_d(op1, op2);
        sub_d(op1, op2);
        sub_d(op1, op2);
        sub_d(op1, op2);
        sub_d(op1, op2);
        sub_d(op1, op2);
        sub_d(op1, op2);
        sub_d(op1, op2);
        sub_d(op1, op2);
        sub_d(op1, op2);
        sub_d(op1, op2);
        sub_d(op1, op2);
        sub_d(op1, op2);
        sub_d(op1, op2);
        sub_d(op1, op2);
        sub_d(op1, op2);
        sub_d(op1, op2);
        sub_d(op1, op2);
        sub_d(op1, op2);
        sub_d(op1, op2);
        sub_d(op1, op2);
        sub_d(op1, op2);
        sub_d(op1, op2);
        sub_d(op1, op2);
        sub_d(op1, op2);
        sub_d(op1, op2);
    }
    getrusage(RUSAGE_SELF, &usage);
    end = usage.ru_utime;
    temp = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
    getrusage(RUSAGE_SELF, &usage);
    start = usage.ru_utime;
    for (volatile int i = 0; i < FP_ITERATIONS; ++i) {
        sub_d(op1, op2);
        sub_d(op1, op2);
        sub_d(op1, op2);
        sub_d(op1, op2);
        sub_d(op1, op2);
        sub_d(op1, op2);
        sub_d(op1, op2);
        sub_d(op1, op2);
        sub_d(op1, op2);
        sub_d(op1, op2);
        sub_d(op1, op2);
        sub_d(op1, op2);
        sub_d(op1, op2);
        sub_d(op1, op2);
        sub_d(op1, op2);
        sub_d(op1, op2);
        sub_d(op1, op2);
        sub_d(op1, op2);
        sub_d(op1, op2);
        sub_d(op1, op2);
    }
    getrusage(RUSAGE_SELF, &usage);
    end = usage.ru_utime;
    double subusec = (temp - ((end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec))) / (FP_ITERATIONS / 50.0);

    getrusage(RUSAGE_SELF, &usage);
    start = usage.ru_utime;
    for (volatile int i = 0; i < FP_ITERATIONS; ++i) {
        mul_d(op1, op2);
        mul_d(op1, op2);
        mul_d(op1, op2);
        mul_d(op1, op2);
        mul_d(op1, op2);
        mul_d(op1, op2);
        mul_d(op1, op2);
        mul_d(op1, op2);
        mul_d(op1, op2);
        mul_d(op1, op2);
        mul_d(op1, op2);
        mul_d(op1, op2);
        mul_d(op1, op2);
        mul_d(op1, op2);
        mul_d(op1, op2);
        mul_d(op1, op2);
        mul_d(op1, op2);
        mul_d(op1, op2);
        mul_d(op1, op2);
        mul_d(op1, op2);
        mul_d(op1, op2);
        mul_d(op1, op2);
        mul_d(op1, op2);
        mul_d(op1, op2);
        mul_d(op1, op2);
        mul_d(op1, op2);
        mul_d(op1, op2);
        mul_d(op1, op2);
        mul_d(op1, op2);
        mul_d(op1, op2);
        mul_d(op1, op2);
        mul_d(op1, op2);
        mul_d(op1, op2);
        mul_d(op1, op2);
        mul_d(op1, op2);
        mul_d(op1, op2);
        mul_d(op1, op2);
        mul_d(op1, op2);
        mul_d(op1, op2);
        mul_d(op1, op2);
    }
    getrusage(RUSAGE_SELF, &usage);
    end = usage.ru_utime;
    temp = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
    getrusage(RUSAGE_SELF, &usage);
    start = usage.ru_utime;
    for (volatile int i = 0; i < FP_ITERATIONS; ++i) {
        mul_d(op1, op2);
        mul_d(op1, op2);
        mul_d(op1, op2);
        mul_d(op1, op2);
        mul_d(op1, op2);
        mul_d(op1, op2);
        mul_d(op1, op2);
        mul_d(op1, op2);
        mul_d(op1, op2);
        mul_d(op1, op2);
        mul_d(op1, op2);
        mul_d(op1, op2);
        mul_d(op1, op2);
        mul_d(op1, op2);
        mul_d(op1, op2);
        mul_d(op1, op2);
        mul_d(op1, op2);
        mul_d(op1, op2);
        mul_d(op1, op2);
        mul_d(op1, op2);
    }
    getrusage(RUSAGE_SELF, &usage);
    end = usage.ru_utime;
    double mulusec = (temp - ((end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec))) / (FP_ITERATIONS / 50.0);

    getrusage(RUSAGE_SELF, &usage);
    start = usage.ru_utime;
    for (volatile int i = 0; i < FP_ITERATIONS; ++i) {
        div_d(op1, op2);
        div_d(op1, op2);
        div_d(op1, op2);
        div_d(op1, op2);
        div_d(op1, op2);
        div_d(op1, op2);
        div_d(op1, op2);
        div_d(op1, op2);
        div_d(op1, op2);
        div_d(op1, op2);
        div_d(op1, op2);
        div_d(op1, op2);
        div_d(op1, op2);
        div_d(op1, op2);
        div_d(op1, op2);
        div_d(op1, op2);
        div_d(op1, op2);
        div_d(op1, op2);
        div_d(op1, op2);
        div_d(op1, op2);
        div_d(op1, op2);
        div_d(op1, op2);
        div_d(op1, op2);
        div_d(op1, op2);
        div_d(op1, op2);
        div_d(op1, op2);
        div_d(op1, op2);
        div_d(op1, op2);
        div_d(op1, op2);
        div_d(op1, op2);
        div_d(op1, op2);
        div_d(op1, op2);
        div_d(op1, op2);
        div_d(op1, op2);
        div_d(op1, op2);
        div_d(op1, op2);
        div_d(op1, op2);
        div_d(op1, op2);
        div_d(op1, op2);
        div_d(op1, op2);
    }
    getrusage(RUSAGE_SELF, &usage);
    end = usage.ru_utime;
    temp = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
    getrusage(RUSAGE_SELF, &usage);
    start = usage.ru_utime;
    for (volatile int i = 0; i < FP_ITERATIONS; ++i) {
        div_d(op1, op2);
        div_d(op1, op2);
        div_d(op1, op2);
        div_d(op1, op2);
        div_d(op1, op2);
        div_d(op1, op2);
        div_d(op1, op2);
        div_d(op1, op2);
        div_d(op1, op2);
        div_d(op1, op2);
        div_d(op1, op2);
        div_d(op1, op2);
        div_d(op1, op2);
        div_d(op1, op2);
        div_d(op1, op2);
        div_d(op1, op2);
        div_d(op1, op2);
        div_d(op1, op2);
        div_d(op1, op2);
        div_d(op1, op2);
    }
    getrusage(RUSAGE_SELF, &usage);
    end = usage.ru_utime;
    double divusec = (temp - ((end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec))) / (FP_ITERATIONS / 50.0);

    getrusage(RUSAGE_SELF, &usage);
    start = usage.ru_utime;
    for (volatile int i = 0; i < FP_ITERATIONS; ++i) {
        sqrt_d(op1);
        sqrt_d(op1);
        sqrt_d(op1);
        sqrt_d(op1);
        sqrt_d(op1);
        sqrt_d(op1);
        sqrt_d(op1);
        sqrt_d(op1);
        sqrt_d(op1);
        sqrt_d(op1);
        sqrt_d(op1);
        sqrt_d(op1);
        sqrt_d(op1);
        sqrt_d(op1);
        sqrt_d(op1);
        sqrt_d(op1);
        sqrt_d(op1);
        sqrt_d(op1);
        sqrt_d(op1);
        sqrt_d(op1);
        sqrt_d(op1);
        sqrt_d(op1);
        sqrt_d(op1);
        sqrt_d(op1);
        sqrt_d(op1);
        sqrt_d(op1);
        sqrt_d(op1);
        sqrt_d(op1);
        sqrt_d(op1);
        sqrt_d(op1);
        sqrt_d(op1);
        sqrt_d(op1);
        sqrt_d(op1);
        sqrt_d(op1);
        sqrt_d(op1);
        sqrt_d(op1);
        sqrt_d(op1);
        sqrt_d(op1);
        sqrt_d(op1);
        sqrt_d(op1);
    }
    getrusage(RUSAGE_SELF, &usage);
    end = usage.ru_utime;
    temp = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);;
    getrusage(RUSAGE_SELF, &usage);
    start = usage.ru_utime;
    for (volatile int i = 0; i < FP_ITERATIONS; ++i) {
        sqrt_d(op1);
        sqrt_d(op1);
        sqrt_d(op1);
        sqrt_d(op1);
        sqrt_d(op1);
        sqrt_d(op1);
        sqrt_d(op1);
        sqrt_d(op1);
        sqrt_d(op1);
        sqrt_d(op1);
        sqrt_d(op1);
        sqrt_d(op1);
        sqrt_d(op1);
        sqrt_d(op1);
        sqrt_d(op1);
        sqrt_d(op1);
        sqrt_d(op1);
        sqrt_d(op1);
        sqrt_d(op1);
        sqrt_d(op1);
        sqrt_d(op1);
        sqrt_d(op1);
        sqrt_d(op1);
        sqrt_d(op1);
        sqrt_d(op1);
        sqrt_d(op1);
        sqrt_d(op1);
        sqrt_d(op1);
        sqrt_d(op1);
        sqrt_d(op1);
    }
    getrusage(RUSAGE_SELF, &usage);
    end = usage.ru_utime;
    double sqrtusec = (temp - ((end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec))) / (FP_ITERATIONS / 50.0);

    /**************************************************************************/
    /*                         MY FP OPERATIONS                               */
    /**************************************************************************/

    getrusage(RUSAGE_SELF, &usage);
    start = usage.ru_utime;
    for (volatile int i = 0; i < MY_FP_ITERATIONS; ++i) {
        my_add(my_op1, my_op2);
        my_add(my_op1, my_op2);
        my_add(my_op1, my_op2);
        my_add(my_op1, my_op2);
        my_add(my_op1, my_op2);
        my_add(my_op1, my_op2);
        my_add(my_op1, my_op2);
        my_add(my_op1, my_op2);
        my_add(my_op1, my_op2);
        my_add(my_op1, my_op2);
        my_add(my_op1, my_op2);
        my_add(my_op1, my_op2);
        my_add(my_op1, my_op2);
        my_add(my_op1, my_op2);
        my_add(my_op1, my_op2);
        my_add(my_op1, my_op2);
        my_add(my_op1, my_op2);
        my_add(my_op1, my_op2);
        my_add(my_op1, my_op2);
        my_add(my_op1, my_op2);
        my_add(my_op1, my_op2);
        my_add(my_op1, my_op2);
        my_add(my_op1, my_op2);
        my_add(my_op1, my_op2);
        my_add(my_op1, my_op2);
        my_add(my_op1, my_op2);
        my_add(my_op1, my_op2);
        my_add(my_op1, my_op2);
        my_add(my_op1, my_op2);
        my_add(my_op1, my_op2);
        my_add(my_op1, my_op2);
        my_add(my_op1, my_op2);
        my_add(my_op1, my_op2);
        my_add(my_op1, my_op2);
        my_add(my_op1, my_op2);
        my_add(my_op1, my_op2);
        my_add(my_op1, my_op2);
        my_add(my_op1, my_op2);
        my_add(my_op1, my_op2);
        my_add(my_op1, my_op2);
    }
    getrusage(RUSAGE_SELF, &usage);
    end = usage.ru_utime;
    temp = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
    getrusage(RUSAGE_SELF, &usage);
    start = usage.ru_utime;
    for (volatile int i = 0; i < MY_FP_ITERATIONS; ++i) {
        my_add(my_op1, my_op2);
        my_add(my_op1, my_op2);
        my_add(my_op1, my_op2);
        my_add(my_op1, my_op2);
        my_add(my_op1, my_op2);
        my_add(my_op1, my_op2);
        my_add(my_op1, my_op2);
        my_add(my_op1, my_op2);
        my_add(my_op1, my_op2);
        my_add(my_op1, my_op2);
        my_add(my_op1, my_op2);
        my_add(my_op1, my_op2);
        my_add(my_op1, my_op2);
        my_add(my_op1, my_op2);
        my_add(my_op1, my_op2);
        my_add(my_op1, my_op2);
        my_add(my_op1, my_op2);
        my_add(my_op1, my_op2);
        my_add(my_op1, my_op2);
        my_add(my_op1, my_op2);
    }
    getrusage(RUSAGE_SELF, &usage);
    end = usage.ru_utime;
    double my_addusec = (temp - ((end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec))) / (MY_FP_ITERATIONS / 50.0);

    getrusage(RUSAGE_SELF, &usage);
    start = usage.ru_utime;
    for (volatile int i = 0; i < MY_FP_ITERATIONS; ++i) {
        my_sub(my_op1, my_op2);
        my_sub(my_op1, my_op2);
        my_sub(my_op1, my_op2);
        my_sub(my_op1, my_op2);
        my_sub(my_op1, my_op2);
        my_sub(my_op1, my_op2);
        my_sub(my_op1, my_op2);
        my_sub(my_op1, my_op2);
        my_sub(my_op1, my_op2);
        my_sub(my_op1, my_op2);
        my_sub(my_op1, my_op2);
        my_sub(my_op1, my_op2);
        my_sub(my_op1, my_op2);
        my_sub(my_op1, my_op2);
        my_sub(my_op1, my_op2);
        my_sub(my_op1, my_op2);
        my_sub(my_op1, my_op2);
        my_sub(my_op1, my_op2);
        my_sub(my_op1, my_op2);
        my_sub(my_op1, my_op2);
        my_sub(my_op1, my_op2);
        my_sub(my_op1, my_op2);
        my_sub(my_op1, my_op2);
        my_sub(my_op1, my_op2);
        my_sub(my_op1, my_op2);
        my_sub(my_op1, my_op2);
        my_sub(my_op1, my_op2);
        my_sub(my_op1, my_op2);
        my_sub(my_op1, my_op2);
        my_sub(my_op1, my_op2);
        my_sub(my_op1, my_op2);
        my_sub(my_op1, my_op2);
        my_sub(my_op1, my_op2);
        my_sub(my_op1, my_op2);
        my_sub(my_op1, my_op2);
        my_sub(my_op1, my_op2);
        my_sub(my_op1, my_op2);
        my_sub(my_op1, my_op2);
        my_sub(my_op1, my_op2);
        my_sub(my_op1, my_op2);
    }
    getrusage(RUSAGE_SELF, &usage);
    end = usage.ru_utime;
    temp = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
    getrusage(RUSAGE_SELF, &usage);
    start = usage.ru_utime;
    for (volatile int i = 0; i < MY_FP_ITERATIONS; ++i) {
        my_sub(my_op1, my_op2);
        my_sub(my_op1, my_op2);
        my_sub(my_op1, my_op2);
        my_sub(my_op1, my_op2);
        my_sub(my_op1, my_op2);
        my_sub(my_op1, my_op2);
        my_sub(my_op1, my_op2);
        my_sub(my_op1, my_op2);
        my_sub(my_op1, my_op2);
        my_sub(my_op1, my_op2);
        my_sub(my_op1, my_op2);
        my_sub(my_op1, my_op2);
        my_sub(my_op1, my_op2);
        my_sub(my_op1, my_op2);
        my_sub(my_op1, my_op2);
        my_sub(my_op1, my_op2);
        my_sub(my_op1, my_op2);
        my_sub(my_op1, my_op2);
        my_sub(my_op1, my_op2);
        my_sub(my_op1, my_op2);
    }
    getrusage(RUSAGE_SELF, &usage);
    end = usage.ru_utime;
    double my_subusec = (temp - ((end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec))) / (MY_FP_ITERATIONS / 50.0);

    getrusage(RUSAGE_SELF, &usage);
    start = usage.ru_utime;
    for (volatile int i = 0; i < MY_FP_ITERATIONS; ++i) {
        my_mul(my_op1, my_op2);
        my_mul(my_op1, my_op2);
        my_mul(my_op1, my_op2);
        my_mul(my_op1, my_op2);
        my_mul(my_op1, my_op2);
        my_mul(my_op1, my_op2);
        my_mul(my_op1, my_op2);
        my_mul(my_op1, my_op2);
        my_mul(my_op1, my_op2);
        my_mul(my_op1, my_op2);
        my_mul(my_op1, my_op2);
        my_mul(my_op1, my_op2);
        my_mul(my_op1, my_op2);
        my_mul(my_op1, my_op2);
        my_mul(my_op1, my_op2);
        my_mul(my_op1, my_op2);
        my_mul(my_op1, my_op2);
        my_mul(my_op1, my_op2);
        my_mul(my_op1, my_op2);
        my_mul(my_op1, my_op2);
        my_mul(my_op1, my_op2);
        my_mul(my_op1, my_op2);
        my_mul(my_op1, my_op2);
        my_mul(my_op1, my_op2);
        my_mul(my_op1, my_op2);
        my_mul(my_op1, my_op2);
        my_mul(my_op1, my_op2);
        my_mul(my_op1, my_op2);
        my_mul(my_op1, my_op2);
        my_mul(my_op1, my_op2);
        my_mul(my_op1, my_op2);
        my_mul(my_op1, my_op2);
        my_mul(my_op1, my_op2);
        my_mul(my_op1, my_op2);
        my_mul(my_op1, my_op2);
        my_mul(my_op1, my_op2);
        my_mul(my_op1, my_op2);
        my_mul(my_op1, my_op2);
        my_mul(my_op1, my_op2);
        my_mul(my_op1, my_op2);
    }
    getrusage(RUSAGE_SELF, &usage);
    end = usage.ru_utime;
    temp = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
    getrusage(RUSAGE_SELF, &usage);
    start = usage.ru_utime;
    for (volatile int i = 0; i < MY_FP_ITERATIONS; ++i) {
        my_mul(my_op1, my_op2);
        my_mul(my_op1, my_op2);
        my_mul(my_op1, my_op2);
        my_mul(my_op1, my_op2);
        my_mul(my_op1, my_op2);
        my_mul(my_op1, my_op2);
        my_mul(my_op1, my_op2);
        my_mul(my_op1, my_op2);
        my_mul(my_op1, my_op2);
        my_mul(my_op1, my_op2);
        my_mul(my_op1, my_op2);
        my_mul(my_op1, my_op2);
        my_mul(my_op1, my_op2);
        my_mul(my_op1, my_op2);
        my_mul(my_op1, my_op2);
        my_mul(my_op1, my_op2);
        my_mul(my_op1, my_op2);
        my_mul(my_op1, my_op2);
        my_mul(my_op1, my_op2);
        my_mul(my_op1, my_op2);
    }
    getrusage(RUSAGE_SELF, &usage);
    end = usage.ru_utime;
    double my_mulusec = (temp - ((end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec))) / (MY_FP_ITERATIONS / 50.0);

    getrusage(RUSAGE_SELF, &usage);
    start = usage.ru_utime;
    for (volatile int i = 0; i < MY_FP_ITERATIONS; ++i) {
        my_div(my_op1, my_op2);
        my_div(my_op1, my_op2);
        my_div(my_op1, my_op2);
        my_div(my_op1, my_op2);
        my_div(my_op1, my_op2);
        my_div(my_op1, my_op2);
        my_div(my_op1, my_op2);
        my_div(my_op1, my_op2);
        my_div(my_op1, my_op2);
        my_div(my_op1, my_op2);
        my_div(my_op1, my_op2);
        my_div(my_op1, my_op2);
        my_div(my_op1, my_op2);
        my_div(my_op1, my_op2);
        my_div(my_op1, my_op2);
        my_div(my_op1, my_op2);
        my_div(my_op1, my_op2);
        my_div(my_op1, my_op2);
        my_div(my_op1, my_op2);
        my_div(my_op1, my_op2);
        my_div(my_op1, my_op2);
        my_div(my_op1, my_op2);
        my_div(my_op1, my_op2);
        my_div(my_op1, my_op2);
        my_div(my_op1, my_op2);
        my_div(my_op1, my_op2);
        my_div(my_op1, my_op2);
        my_div(my_op1, my_op2);
        my_div(my_op1, my_op2);
        my_div(my_op1, my_op2);
        my_div(my_op1, my_op2);
        my_div(my_op1, my_op2);
        my_div(my_op1, my_op2);
        my_div(my_op1, my_op2);
        my_div(my_op1, my_op2);
        my_div(my_op1, my_op2);
        my_div(my_op1, my_op2);
        my_div(my_op1, my_op2);
        my_div(my_op1, my_op2);
        my_div(my_op1, my_op2);
    }
    getrusage(RUSAGE_SELF, &usage);
    end = usage.ru_utime;
    temp = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
    getrusage(RUSAGE_SELF, &usage);
    start = usage.ru_utime;
    for (volatile int i = 0; i < MY_FP_ITERATIONS; ++i) {
        my_div(my_op1, my_op2);
        my_div(my_op1, my_op2);
        my_div(my_op1, my_op2);
        my_div(my_op1, my_op2);
        my_div(my_op1, my_op2);
        my_div(my_op1, my_op2);
        my_div(my_op1, my_op2);
        my_div(my_op1, my_op2);
        my_div(my_op1, my_op2);
        my_div(my_op1, my_op2);
        my_div(my_op1, my_op2);
        my_div(my_op1, my_op2);
        my_div(my_op1, my_op2);
        my_div(my_op1, my_op2);
        my_div(my_op1, my_op2);
        my_div(my_op1, my_op2);
        my_div(my_op1, my_op2);
        my_div(my_op1, my_op2);
        my_div(my_op1, my_op2);
        my_div(my_op1, my_op2);
    }
    getrusage(RUSAGE_SELF, &usage);
    end = usage.ru_utime;
    double my_divusec = (temp - ((end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec))) / (MY_FP_ITERATIONS / 50.0);

    getrusage(RUSAGE_SELF, &usage);
    start = usage.ru_utime;
    for (volatile int i = 0; i < MY_FP_ITERATIONS; ++i) {
        my_sqrt(my_op1);
        my_sqrt(my_op1);
        my_sqrt(my_op1);
        my_sqrt(my_op1);
        my_sqrt(my_op1);
        my_sqrt(my_op1);
        my_sqrt(my_op1);
        my_sqrt(my_op1);
        my_sqrt(my_op1);
        my_sqrt(my_op1);
        my_sqrt(my_op1);
        my_sqrt(my_op1);
        my_sqrt(my_op1);
        my_sqrt(my_op1);
        my_sqrt(my_op1);
        my_sqrt(my_op1);
        my_sqrt(my_op1);
        my_sqrt(my_op1);
        my_sqrt(my_op1);
        my_sqrt(my_op1);
        my_sqrt(my_op1);
        my_sqrt(my_op1);
        my_sqrt(my_op1);
        my_sqrt(my_op1);
        my_sqrt(my_op1);
        my_sqrt(my_op1);
        my_sqrt(my_op1);
        my_sqrt(my_op1);
        my_sqrt(my_op1);
        my_sqrt(my_op1);
        my_sqrt(my_op1);
        my_sqrt(my_op1);
        my_sqrt(my_op1);
        my_sqrt(my_op1);
        my_sqrt(my_op1);
        my_sqrt(my_op1);
        my_sqrt(my_op1);
        my_sqrt(my_op1);
        my_sqrt(my_op1);
        my_sqrt(my_op1);
    }
    getrusage(RUSAGE_SELF, &usage);
    end = usage.ru_utime;
    temp = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
    getrusage(RUSAGE_SELF, &usage);
    start = usage.ru_utime;
    for (volatile int i = 0; i < MY_FP_ITERATIONS; ++i) {
        my_sqrt(my_op1);
        my_sqrt(my_op1);
        my_sqrt(my_op1);
        my_sqrt(my_op1);
        my_sqrt(my_op1);
        my_sqrt(my_op1);
        my_sqrt(my_op1);
        my_sqrt(my_op1);
        my_sqrt(my_op1);
        my_sqrt(my_op1);
        my_sqrt(my_op1);
        my_sqrt(my_op1);
        my_sqrt(my_op1);
        my_sqrt(my_op1);
        my_sqrt(my_op1);
        my_sqrt(my_op1);
        my_sqrt(my_op1);
        my_sqrt(my_op1);
        my_sqrt(my_op1);
        my_sqrt(my_op1);
    }
    getrusage(RUSAGE_SELF, &usage);
    end = usage.ru_utime;
    double my_sqrtusec = (temp - ((end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec))) / (MY_FP_ITERATIONS / 50.0);

    printf("Time to perform hardware add:         %f nanoseconds.\n", addusec);
    printf("Time to perform software add:         %f nanoseconds.\n\n", my_addusec);

    printf("Time to perform hardware subtract:    %f nanoseconds.\n", subusec);
    printf("Time to perform software subtract:    %f nanoseconds.\n\n", my_subusec);

    printf("Time to perform hardware multiply:    %f nanoseconds.\n", mulusec);
    printf("Time to perform software multiply:    %f nanoseconds.\n\n", my_mulusec);

    printf("Time to perform hardware divide:      %f nanoseconds.\n", divusec);
    printf("Time to perform software divide:      %f nanoseconds.\n\n", my_divusec);

    printf("Time to perform hardware square root: %f nanoseconds.\n", sqrtusec);
    printf("Time to perform software square root: %f nanoseconds.\n\n", my_sqrtusec);

    return 0;
}
