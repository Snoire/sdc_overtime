#include <stdio.h>
#include <stdlib.h>

int main()
{
    char buf[32] = "";
    FILE *fp = fopen("/proc/meminfo", "r");
    fscanf(fp, "%*[^\n]\n");
    fscanf(fp, "MemFree: %s kB", buf);

    printf("free memory: %d kB\n", atoi(buf));
    fclose(fp);

    return 0;
}
