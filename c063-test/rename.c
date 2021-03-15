#include <stdio.h>
#include <unistd.h>

int main()
{
    char buf[128] = "";
    FILE *fp = NULL;

    if ((fp = fopen("rename.old", "r"))) {
        sleep(20);

        rename("rename.old", "rename.new");
        printf("rename\n");
        sleep(20);

        fgets(buf, sizeof(buf), fp);
        printf("buf: %s\n", buf);

        fclose(fp);
        printf("fclose\n");
        sleep(10);
    }

    return 0;
}
