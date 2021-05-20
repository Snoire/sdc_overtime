/* 先执行 map_normalfile2，再执行 map_normalfile1 */
#include <stdio.h>
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

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return -1;
    }

    fd = open(argv[1], O_CREAT | O_TRUNC | O_RDWR, 00777);
    p_map = (people *) mmap(NULL, sizeof(people) * 5, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    printf("mmap succeeded\n");
    write(fd, "1", 1);  /* 如果文件大小是 0，就会有 bus error */
//    close(fd);  /* 关闭不影响 mmap */
    
    stat(argv[1], &st);
    printf("st.size: %ld\n", st.st_size);

//    sleep(10);
#if 1
    struct flock lock;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0; /* lock the whole file */
    lock.l_type = F_RDLCK;

    fcntl(fd, F_SETLKW, &lock);
#endif

    stat(argv[1], &st);
    printf("st.size: %ld\n", st.st_size);

    for (i = 0; i < 10; i++) {
        printf("name: %s age %d;\n", (*(p_map + i)).name, (*(p_map + i)).age);
    }
    munmap(p_map, sizeof(people) * 10);
#if 1
    lock.l_type = F_UNLCK;  /* unlock */
    fcntl(fd, F_SETLKW, &lock);
#endif

    return 0;
}
