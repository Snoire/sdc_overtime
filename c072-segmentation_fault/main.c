#include <stdio.h>
#include <sys/types.h>
#include <pwd.h>
#include <unistd.h>

int main()
{
    char *pnull = NULL;
    char buf[64] = "";

    printf("NULL: %s\n", pnull);  /* 用 printf 输出不会出错 */

    sprintf(buf, "NULL: |%s|\n", pnull);  /* 这个也不会 */
    printf("buf: [%s]\n", buf);
   
#if 0
    if (pnull[0] != '-')          /* 对 NULL 寻址会段错误 */
        printf("NULL: %s\n", pnull);
#endif

    return 0;
}

