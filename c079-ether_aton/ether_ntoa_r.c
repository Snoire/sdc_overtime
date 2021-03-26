#include <stdio.h>
#include <netinet/ether.h>

int main()
{
    char buf[18] = "";
#if 0
    char *macstr = "14:2e:5e:89:09:be";
#else
    char *macstr = "14:2E:5E:89:09:BE";
#endif
    unsigned char macbin[6] = { 0 };

    ether_aton_r(macstr, (struct ether_addr *) macbin);
    ether_ntoa_r((struct ether_addr *) macbin, buf);     /* 会被转换成小写啊 */
    printf("mac: %s\n", buf);                            /* 并且 09 变成 9 了 */
    printf("mac: %s\n", ether_ntoa_r((struct ether_addr *) macbin, buf));

    return 0;
}
