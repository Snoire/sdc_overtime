#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int fd = 0;

    fd = open("non-exist.txt", O_RDONLY);   /* 如果不指定 O_CREAT 并且文件不存在，就会出错 */
    if (fd > -1) {
        printf("fd: %d\n", fd);
        close(fd);
    } else
        fprintf(stderr, "fd: %d: %m\n", fd);

    return 0;
}
//也可以这样写：
