#pragma once

#include <stdint.h>

#define SIGN_BITS   1
#define EXP_BITS    11
#define MANT_BITS   52

typedef struct {
    uint64_t mant : MANT_BITS, exp : EXP_BITS, sign : SIGN_BITS;
} my_double;
