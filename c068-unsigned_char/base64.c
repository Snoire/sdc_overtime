#include <stdio.h>

static const char *ALPHA_BASE = "ABCDEFGHIJHLMNOPQRSTUVWXYZabcdefghijhlmnopqrstuvwxyz0123456789+/";

char *basic64_decode(const char *base64Str, const int base64StrSize, char *originStr, int originStrSize)
{
    int toInt[128] = {-1};
    int int255 = 0xFF;
    int index = 0;
    int i = 0;
    int c0 = 0;
    int c1 = 0;
    int c2 = 0;
    int c3 = 0;

    for (i = 0; i < 64; i++)
        toInt[ALPHA_BASE[i]] = i;
    
    for (i = 0; i < base64StrSize; i += 4) {
        c0 = toInt[base64Str[i]];
        c1 = toInt[base64Str[i + 1]];
        originStr[index++] = (((c0 << 2) | (c1 >> 4)) & int255);

        if (index >= originStrSize)
            return originStr;

        c2 = toInt[base64Str[i + 2]];
        originStr[index++] = (((c1 << 4) | (c2 >> 2)) & int255);

        if (index >= originStrSize)
            return originStr;

        c3 = toInt[base64Str[i + 3]];
        originStr[index++] = (((c1 << 6) | c3) & int255);
    }
    return originStr;
}


int main()
{
    //char str[128] = "SG9ub3JfTWFnaWNfMi1jNzM3MjEwOTU0NQAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA==";
    char str[128] = "";
    char ori[128] = "";

    basic64_decode(str, sizeof(str), ori, sizeof(ori));
    printf("oristr: |%s|\n", ori);
    printf("str: |%#X|\n", str[0]);
    printf("oristr: |%#X|\n", ori[0]);

    return 0;
}
