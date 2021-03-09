#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    unsigned long int a = 10;
    unsigned long long int b;
    a = atoi("600");

    b = a;
    a = 0;
    
    FILE *fp = fopen("./test2.txt", "w+");
    fprintf(fp, "%llu\n", b);
    fflush(fp);

    //fsync(fileno(fp));
    //sync();
    rewind(fp);  // mdzz, 不加这个，你读了个寂寞。。

    fscanf(fp, "%lu\n", &a);
    printf("%lu\n", a);

    fclose(fp);
    return 0;
}
