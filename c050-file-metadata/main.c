#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

#define WIDTH 36

int printf_binary(unsigned int st_mode)
{
    int i = 0;
    char stmode[WIDTH] = "";
    while (st_mode) {              /* print binary number */
        if ((i+1)%5 == 0) {
            stmode[i] = ' ';
            ++i;
        }

        if (st_mode & 1)
            stmode[i] = '1';
        else
            stmode[i] = '0';

        ++i;

        st_mode >>= 1;
	}
    for (; i; i--)
        printf("%c", stmode[i-1]);   /* 正序，高位在前 */
    printf("\n");

    return 0;
}

int main()
{
    int fd;
    struct stat filestat;
    
    fd = open("testfile", O_CREAT|O_RDWR, S_IRWXU|S_IRGRP|S_IXGRP|S_IROTH|S_IXOTH);
    if (stat("testfile", &filestat))
        fprintf(stderr, "stat error\n");

    printf("IDs of device on which file resides: %18ld\n", filestat.st_dev);
    printf("i-node number: %40ld\n", filestat.st_ino);

    printf("file type and permissions: %28lX\n", filestat.st_mode);
    printf("unsigned octal format: %32o\n", filestat.st_mode);
    printf_binary(filestat.st_mode);
    switch (filestat.st_mode & S_IFMT) {
	case S_IFBLK:
        printf("block device\n");            break;
	case S_IFCHR:
        printf("character device\n");        break;
	case S_IFDIR:
        printf("directory\n");               break;
	case S_IFIFO:
        printf("FIFO/pipe\n");               break;
	case S_IFLNK:
        printf("symlink\n");                 break;
	case S_IFREG:
        printf("regular file\n");            break;
	case S_IFSOCK:
        printf("socket\n");                  break;
    default:
        printf("unknown?\n");                break;
	}
    printf("\n");


    printf("number of hard links to file: %25ld\n", filestat.st_nlink);
    printf("user ID of file owner: %32ld\n", filestat.st_uid);
    printf("group ID of file owner: %31ld\n\n", filestat.st_gid);

    printf("time of last file access: %29ld\n", filestat.st_atime);  //注意，最后是 st_atime，它等于 st_atim.tv_sec
    printf("time of last file access(ns): %25ld\n", filestat.st_atim.tv_nsec);
    struct tm *tmp;
    tmp = localtime(&filestat.st_atim.tv_sec);                       //转换成易读形式
    printf("%d%.2d%d, %.2d:%.2d:%.2d, 星期 %d\n",
            tmp->tm_year+1900, tmp->tm_mon+1, tmp->tm_mday, tmp->tm_hour,
            tmp->tm_min, tmp->tm_sec, tmp->tm_wday?tmp->tm_wday:7);

    printf("time of last file modification: %23ld\n", filestat.st_mtime);
    printf("time of last status change: %27ld\n", filestat.st_ctime);
    
    printf("total file size: %38ld\n", filestat.st_size);
    printf("Number of 512B blocks allocated: %22ld\n", filestat.st_blocks);
    printf("Block size for filesystem I/O: %24ld\n", filestat.st_blksize);

    return 0;
}

