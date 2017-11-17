#include <stdio.h>
#include <math.h>
#include <stdint.h>

void bi_endian(char* bytes, int len) {
    /* Referenced https://stackoverflow.com/questions/1001307/detecting-endianness-programmatically-in-a-c-program */
    union {
        uint16_t u;
        char c[2];
    } test_val = {0x0102};

    if (test_val.c[0] != 1) {
        printf("System uses little-endian memory architecture.\n");
        int num_swaps = ceil((len - 1) / 2.0);
        for (int i = 0; i < num_swaps; ++i) {
            int back = i;
            int front = len - 1 - i;
            char temp;
            temp = bytes[back];
            bytes[back] = bytes[front];
            bytes[front] = temp;
        }
    } else {
        printf("System uses big-endian memory architecture.\n");
    }
}

int main(int argc, char **argv)
{
    short val;
    char *p_val;
    p_val = (char *)&val;
    p_val[0] = 0x12;
    p_val[1] = 0x34;
    bi_endian(p_val, 2);
    printf("%x\n", val);

    return 0;
}
