#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>              //结构体addrinfo, in_addr
#include <netinet/in.h>
#include <arpa/inet.h>

int getIp(char *hostname, char *ip)
{
    struct addrinfo hints, *res = NULL;
    struct in_addr addr;
    int err;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_family = AF_INET;

    if ((err = getaddrinfo(hostname, NULL, &hints, &res)) != 0) {
        printf("error %d : %s\n", err, gai_strerror(err));
        return -1;
    }

    if (res != NULL) {
        addr.s_addr = ((struct sockaddr_in *) (res->ai_addr))->sin_addr.s_addr;
        fprintf(stderr, "ip addresss: %s\n", inet_ntoa(addr));
        sprintf(ip, "%s", inet_ntoa(addr));
        freeaddrinfo(res);
    }

    return 0;
}

int main(int argc, char **argv)
{
    char ip[128] = "";
    if (argc == 2)
        getIp(argv[1], ip);

    return 0;
}
