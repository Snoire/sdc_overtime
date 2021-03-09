#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

int main(int argc, char **argv)
{
    int prefix_len = atoi(argv[2]), mask_len = 128 - prefix_len;
    struct in6_addr ip6_network;

    inet_pton(AF_INET6, argv[1], &ip6_network);

    printf("ipv6:\n");
    for (int i = 0; i < 16; i++) { /* 网络字节序，所以从 0 开始输出刚好可以从高位打印 */
        printf("%.2X ", ip6_network.__in6_u.__u6_addr8[i]);
    }
    printf("\n");

    /* mask */
    struct in6_addr ip6_mask;
    memset(&ip6_mask, 0xFF, sizeof(ip6_mask));
    int a = mask_len / 8;
    int b = mask_len % 8;

    for (int i = 15; i > 15-a; i--) { /* 也把它写成网络字节序，方便下面的操作 */
        ip6_mask.__in6_u.__u6_addr8[i] = 0;
    }
    for (int i = 0; i < b; i++) {
        ip6_mask.__in6_u.__u6_addr8[15-a] &= ~(1<<i);
    }

    printf("mask:\n");
    for (int i = 0; i < 16; i++) {
        printf("%.2X ", ip6_mask.__in6_u.__u6_addr8[i]);
    }
    printf("\n");

    /* get prefix */
    struct in6_addr ip6_prefix;
    for (int i = 0; i < 16; i++) {
        ip6_prefix.__in6_u.__u6_addr8[i] = ip6_network.__in6_u.__u6_addr8[i] & ip6_mask.__in6_u.__u6_addr8[i];
    }

    printf("prefix:\n");
#if 0
    for (int i = 0; i < 16; i++) {
        printf("%.2X ", ip6_prefix.__in6_u.__u6_addr8[i]);
    }
    printf("\n");
#endif

    char prefix[INET6_ADDRSTRLEN] = "";
    inet_ntop(AF_INET6, &ip6_prefix, prefix, INET6_ADDRSTRLEN);

    printf("%s\n", prefix);
    return 0;
}


/*
 * example:
 * ./get_ipv6_prefix '2a01:d0:838e:f700:194b:21da:74b4:6ed4' 64
 */
