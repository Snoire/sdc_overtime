#include <stdio.h>
#include <string.h>

char *get_mac()
{
    char tmp[32] = "00C002FF2206";
    static char mac[32] = "";

    sprintf(mac, "%c%c:%c%c:%c%c:%c%c:%c%c:%c%c",
            tmp[0], tmp[1], tmp[2], tmp[3], tmp[4], tmp[5],
            tmp[6], tmp[7], tmp[8], tmp[9], tmp[10], tmp[11]);

//    printf("mac = %s\n", mac);

    return mac;
}

int main()
{
    printf("mac = %s\n", get_mac()); // 虽然静态局部变量的名字不可使用，但是传个地址出来还是可以的

    return 0;
}
