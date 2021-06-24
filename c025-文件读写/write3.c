#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>

int main()
{
    int fd = 0;

    fd = open("write3.txt", O_CREAT | O_TRUNC | O_WRONLY, 0644);
    char str[] = "a string\n";
    printf("sizeof str: %zu\n", sizeof(str));
    write(fd, str, sizeof(str) - 1);
    write(fd, str, strlen(str));
    close(fd);

    return 0;
}
