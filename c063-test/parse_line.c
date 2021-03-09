#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int len = 0;
    FILE *fp;
    char *buf = NULL;
    char tmp[1024] = "";
    
    /* get the string */
    if ((fp = popen("cat parse_line.txt", "r")) == NULL) {
        perror("popen");
        return EXIT_FAILURE;
    }

    buf = malloc(3);
    if (!buf)
        return EXIT_FAILURE;

    *buf = '\0';
    while (fgets(tmp, sizeof(tmp), fp)) {
        len = strlen(buf) + strlen(tmp) + 1;
        if (!(buf = realloc(buf, sizeof(char) * len))) {
            pclose(fp);
            return EXIT_FAILURE;
        }
        strcat(buf, tmp);
    }

    printf("%s", buf);

    /* do sothing */
    int mcs1 = -1, mcs2 = -1;
    int nss1 = -1, nss2 = -1;
    int bw = 0, sgi = 0;
    char *substr = NULL;

    //sscanf(strstr(buf, "mcs"), "mcs %d Nss %d", &mcs1, &nss1);
#if 0
    if ((substr = strstr(buf, "mcs"))) {
        sscanf(substr, "mcs %d Nss %d", &mcs1, &nss1);
        for (; *substr != '\n' && *substr; substr++) {  // 当前行是否包含 sgi？
            if (strncmp(substr, "sgi", strlen("sgi")) == 0) {
                sgi = 1;
                break;
            }
        }
        if ((substr = strstr(substr, "mcs"))) {  // 找子串第二次出现的位置
            sscanf(substr, "mcs %d Nss %d", &mcs2, &nss2);
        //    for (int i = 0; substr[i] != '\n' && substr[i]; i++) {
            for (; *substr != '\n' && *substr; substr++) {
                if (strncmp(substr, "sgi", strlen("sgi")) == 0) {
                    sgi = 1;
                    break;
                }
            }
        }
    }
#else
    int mcs[2] = {-1, -1}, nss[2] = {-1, -1};
    
    for (int i = 0; i < 2; i++) {
        if (substr == NULL)
            substr = buf;

        if ((substr = strstr(substr, "mcs"))) { // 第二次执行到这里时，由于查找 sgi，所以会使 substr 的指向向后移
            sscanf(substr, "mcs %d Nss %d", mcs + i, nss + i);
            for (; *substr != '\n' && *substr; substr++) {  // 当前行是否包含 sgi？
                if (strncmp(substr, "sgi", strlen("sgi")) == 0) {
                    sgi = 1;
                    break;
                }
            }
        }
    }
#endif
    if ((substr = strstr(buf, "bandwidth"))) {
        sscanf(substr, "bandwidth = %d MHZ", &bw);
    }
    printf("%d %d\n", mcs[0], nss[0]);
    printf("%d %d\n", mcs[1], nss[1]);
    printf("%d MHz, sgi %d\n", bw, sgi);



    pclose(fp);
    return 0;
}
