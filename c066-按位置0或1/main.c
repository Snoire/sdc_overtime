#include <stdio.h>

int main()
{
    unsigned int bindbit = 0;
    int num = -65798;

    bindbit |= 1<<3;   // 在第4位置1
    bindbit |= 1<<6;   // 在第7位置1

    bindbit &= ~(1<<6);   // 在第7位置0

    bindbit = ~0;
//    bindbit |= 1<<25;

    printf("bindbit: |%d|\n", bindbit);
    printf("bindbit: |%ld|\n", bindbit);
    printf("bindbit: |%#010X|\n", bindbit);  // 0X前缀，10位十六进制，不足补0

    printf("num: |%d|\n", num);
    printf("num: |%ld|\n", num);
    printf("num: |%#010X|\n", num);



    return 0;
}

