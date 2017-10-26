#include <sys/time.h>
#include <sys/resource.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include "my_double.h"
#include "mt19937-64.h"

#define FP_ITERATIONS       10000
#define MY_FP_ITERATIONS    100

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

    getrusage(RUSAGE_SELF, &usage);
    start = usage.ru_utime;
    for (int i = 0; i < FP_ITERATIONS; ++i) {
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
    printf("Time to run %d times: %lu.%06u seconds.\n", 20 * FP_ITERATIONS, end.tv_sec - start.tv_sec, end.tv_usec - start.tv_usec);
    return 0;
}
