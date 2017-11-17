#include <stdio.h>

int main(int argc, char **argv)
{
    short val;
    char *p_val;
    p_val = (char *)&val;

#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
    printf("System uses big-endian memory architecture.\n");
    p_val[0] = 0x12;
    p_val[1] = 0x34;
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    printf("System uses little-endian memory architecture.\n");
    p_val[1] = 0x12;
    p_val[0] = 0x34;
#else
#error "Endianess cannot be determined at compile time."
#endif
    printf("%x\n", val);

    return 0;
}
