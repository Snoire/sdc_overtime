// https://www.cnblogs.com/codestack/p/11188889.html
/* 先执行 map_normalfile2，再执行 map_normalfile1 */
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

typedef struct {
    char name[4];
    int age;
} people;

int main(int argc, char **argv)     // map a normal file as shared mem:
{
    int fd, i;
    struct stat st;
    people *p_map;
    char temp;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return -1;
    }
    printf("pagesize: %d\n", getpagesize());

    fd = open(argv[1], O_CREAT | O_RDWR | O_TRUNC, 00777);
    stat(argv[1], &st);
    printf("st.size: %ld\n", st.st_size);

#if 0
    lseek(fd, sizeof(people) * 5 - 1, SEEK_SET);
    write(fd, "", 1);
#endif
    printf("sizeof(people): %lu\n", sizeof(people));
    truncate(argv[1], sizeof(people)*5);

    stat(argv[1], &st);
    printf("st.size: %ld\n", st.st_size);

    p_map = (people *) mmap(NULL, sizeof(people) * 10, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    printf("mmap succeeded\n");
    close(fd);
    temp = 'a';

    for (i = 0; i < 10; i++) {
        temp += 1;
        memcpy((*(p_map + i)).name, &temp, 2);
        (*(p_map + i)).age = 20 + i;
    }

    printf("initialize over\n");
    sleep(15);   /* 注释这一行 */

    /* 写回磁盘文件的内容不能超过文件的大小，所以可能需要用 truncate 调整文件大小 */
    /* 只要没执行到这，map2 可以访问超过文件大小 */
    munmap(p_map, sizeof(people) * 10);
    printf("umap ok\n");
    stat(argv[1], &st);
    printf("st.size: %ld\n", st.st_size);
    /* 如果 map1 提前退出，map2 只能访问文件大小范围内的数据 */

    return 0;
}
