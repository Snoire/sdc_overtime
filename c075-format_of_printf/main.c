#include <stdio.h>

int main()
{
    int mac[6] = { 0 };

    mac[0] = 0x01;
    mac[1] = 0x4F01;

    printf("mac[0]: %2X\n", mac[0]);
    printf("mac[0]: %02X\n", mac[0]);
    printf("mac[0]: %.2X\n", mac[0]);   // 这两个等价，man 手册里提到了这种写法

    printf("mac[1]: %2X\n", mac[1]);
    printf("mac[1]: %02X\n", mac[1]);
    printf("mac[1]: %.2X\n", mac[1]);   // 会超过两个字符

    printf("mac[1]: %4X\n", mac[1]);
    printf("mac[1]: %04X\n", mac[1]);
    printf("mac[1]: %.4X\n", mac[1]);

    return 0;
}
