#include <stdio.h>
#include <math.h>

void byte_swap(char* bytes, int len) {
    int num_swaps = ceil((len - 1) / 2.0);
    for (int i = 0; i < num_swaps; ++i) {
        int back = i;
        int front = len - 1 - i;
        char temp;
        temp = bytes[back];
        bytes[back] = bytes[front];
        bytes[front] = temp;
    }
}

int main(int argc, char **argv)
{
    short val;
    char *p_val;
    p_val = (char *)&val;
    p_val[0] = 0x12;
    p_val[1] = 0x34;

#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
    printf("System uses big-endian memory architecture.\n");
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    printf("System uses little-endian memory architecture.\n");
    byte_swap(p_val, 2);
#else
#error "Endianess cannot be determined at compile time."
#endif
    printf("%x\n", val);

    return 0;
}
