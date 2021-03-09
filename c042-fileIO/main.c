#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define MAX_READ 20

int main()
{
    int fd;
    unsigned int readnum = 0;
//	fd = open("filetest1", O_RDONLY | O_CREAT, S_IRWXU|S_IRGRP|S_IXGRP|S_IROTH|S_IXOTH);  //指定 O_CREAT 的时候要指定权限，不然可能会很奇怪
//    if (fd == -1)
//        perror("open filetest1");
	fd = open("filetest1", O_RDONLY);  //指定 O_CREAT 的时候要指定权限，不然可能会很奇怪
    if (fd == -1)
        perror("open filetest1");
    char str[12] = "";

    lseek(fd, 2, SEEK_SET);
    readnum = read (fd, str, 10);
    printf("str is %s\n"          //这里暗含了一个 \n ？
           "readnum is %d\n"    //并不是，，而是从文件中读出了换行符。。
           "str[2] = %d\n-----------\n",
           str, readnum, str[2]);

    lseek(fd, -10, SEEK_CUR);  //再把文件指针往前偏移10格
    readnum = read (fd, str, 10);
    printf("str is %s\n"
           "readnum is %d\n"
           "str[2] = %d\n-----------\n",
           str, readnum, str[2]);

    int curr = 0;
    curr = lseek(fd, 0, SEEK_CUR);
    printf("current offset is %d\n----------\n", curr);  //知道为什么是12吗？嘿嘿

    lseek(fd, -4, SEEK_END);  //再把文件指针移到最后，再往前偏移4格
    readnum = read (fd, str, 10);
    printf("str is %s,  \n"     //因为没有\0，所以字符串不只显示4个，先用memset清一下会比较好
           "readnum is %d\n"
           "str[2] = %d\n",
           str, readnum, str[2]);

    printf("the current fd is %d\n", fd);
	fd = open("filetest1", O_RDONLY | O_CREAT);  //Each open() of a file creates a new open file description; thus, there may be multiple open file descriptions corresponding to a file inode.
    printf("the reopened fd is %d\n", fd);


#if 0
//stdin
    char buffer1[MAX_READ];
    char buffer2[MAX_READ];
    
    if (read(STDIN_FILENO, buffer1, MAX_READ) == -1)
        perror("open");
    if (read(STDOUT_FILENO, buffer2, MAX_READ) == -1)
        perror("open");
    printf("input is %s\n", buffer1);
//stdout  //这个没有输出啊，不明白
    printf("output is %s\n", buffer2);
#endif
#if 0
//close
    close(fd);
//write
	fd = open("filetest1", O_WRONLY | O_APPEND);
//    write(fd, str, strlen(str));
    char str2[] = "\n";
    write(fd, str2, strlen(str2));
#endif


    return 0;
}

