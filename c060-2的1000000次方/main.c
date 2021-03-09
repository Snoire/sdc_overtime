#include <stdio.h>
#if 0
#include <string.h>
#include <unistd.h>

#define PATH "/home/purian/playc/c060"
#define File PATH"/tfile"

int main()
{
    FILE *fp = NULL;
    if (access(File, F_OK) != 0) {
        printf("the file does not exist!\n");
    }
    if ((fp = fopen(File, "r")) == NULL)
        printf("fopen error\n");

    char teststr[128] = "";

    strcpy(teststr, "12345"
            "678910"
            "abcd");
    printf("str: %s", teststr);

    char str2[16] = {"Off°C"};
    printf("str2: |%s|\n", str2);
    printf("str2[3]: |%d|\n", str2[3]);
/* °C */ /* :digraphs */ /* Ctrl+k, DG */

    return 0;
}
#else
#include <math.h>

/* calculate 2 to the power 1000 */
int main(int argc, const char *argv[])
{
    printf("%.0f\n", pow(2, 1000)); /* 惊了，double 类型居然能存下 2^1000，不过再大一点就不行了 */
    return 0;
}
#endif
