/* client.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define MAXLINE 80
#define SERV_PORT 2567

int main(int argc, char *argv[])
{
	struct sockaddr_in servaddr;
	char buf[MAXLINE];
	int sockfd, n;
	char *str;
    
	if (argc != 3) {
        fprintf(stderr, "usage: ./%s <ip addr> <message>\n", argv[0]);
		exit(1);
	}
	str = argv[2];
    
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) == 0) {
        fprintf(stderr, "invalid ip addr\n");
		exit(1);
    }
	servaddr.sin_port = htons(SERV_PORT);
    
	connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

	write(sockfd, str, strlen(str));

	n = read(sockfd, buf, MAXLINE);
	printf("Response from server: |");
    fflush(stdout);
	write(STDOUT_FILENO, buf, n);
    printf("|\n");
//    while(1){};

	close(sockfd);
	return 0;
}
