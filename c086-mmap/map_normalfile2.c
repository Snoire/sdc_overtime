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
    close(fd);  /* 关闭不影响 mmap */
    
    stat(argv[1], &st);
    printf("st.size: %ld\n", st.st_size);

    sleep(10);
    stat(argv[1], &st);
    printf("st.size: %ld\n", st.st_size);

    for (i = 0; i < 10; i++) {
        printf("name: %s age %d;\n", (*(p_map + i)).name, (*(p_map + i)).age);
    }
    munmap(p_map, sizeof(people) * 10);

    return 0;
}
