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

    /* get prefix */
    struct in6_addr ip6_prefix = ip6_network;
    int a = mask_len / 8;
    int b = mask_len % 8;

    for (int i = 15; i > 15-a; i--) { /* 也把它写成网络字节序，方便下面的操作 */
        ip6_prefix.__in6_u.__u6_addr8[i] = 0;
    }
    for (int i = 0; i < b; i++) {
        ip6_prefix.__in6_u.__u6_addr8[15-a] &= ~(1<<i);
    }

    char prefix[INET6_ADDRSTRLEN] = "";
    inet_ntop(AF_INET6, &ip6_prefix, prefix, INET6_ADDRSTRLEN);

    printf("prefix:\n");
    printf("%s\n", prefix);
    return 0;
}


/*
 * 这一版比之前的更直接，不算 mask，直接计算 prefix
 * example:
 * ./get_prefix '2a01:d0:838e:f700:194b:21da:74b4:6ed4' 64
 */
