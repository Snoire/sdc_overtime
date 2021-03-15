#include <stdio.h>
#include <unistd.h>

int main()
{
    FILE *fp = NULL;

    if ((fp = fopen("unlink.txt", "r"))) {
        sleep(20);
        unlink("unlink.txt");
        printf("unlink\n");
        sleep(20);

        fclose(fp);
        printf("fclose\n");
        sleep(20);
    }

    return 0;
}
