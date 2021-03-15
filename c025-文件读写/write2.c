#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int fd = 0;

    fd = open("write2.txt", O_CREAT | O_TRUNC | O_WRONLY, 0644);
#if 1
    /* 一次写入有 16 个 char 型数字的数组，也可以定义 16 个 char 型变量，然后 write 16 次 。。*/
    char a[16] = {0x0a, 0, 0, 0, 2, 0, 0, 0, 0x41, 0, 0, 0, 4, 0, 0, 0};
    write(fd, &a, sizeof(a));
#else
    /* 也可以这样写，它们是完全一样的 */
    int b[4] = {10, 2, 65, 4};
    write(fd, &b, sizeof(b));
#endif
    close(fd);

    return 0;
}
//也可以这样写：
