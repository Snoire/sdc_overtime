#include <stdio.h>
#include <string.h>

#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define FILENAME "latest.log"
#define LINELEN  150
#define STR(x)   STR2(x)
#define STR2(x)  #x

int main()         //先到文件末尾，再把文件指针向前移最多150，再逐行读取
{
    FILE *fp;
    long bytes_count;
    char str[LINELEN+1] = "";
    char player[20] = "";                                //人名最多 15 个字符

    fp = fopen(FILENAME, "r");
    if (fp == NULL)
        fprintf(stderr, "open %s error!\n", FILENAME);
    fseek(fp, 0L, SEEK_END);
    bytes_count = ftell(fp);
    printf("ftell: %ld\n", bytes_count);
    fseek(fp, -MIN(bytes_count, LINELEN), SEEK_CUR);

    bytes_count = ftell(fp);
    printf("ftell: %ld\n", bytes_count);

    int ret = 0;
//    for (int i=0; i<4; i++) {
//        ret = fscanf(fp, "%"STR(LINELEN)"[^\n]%*c", str);  //读到最后一行 ret 是 1，再读就读不到了，ret 为 -1，
                                                             //读取失败，str 会保持最后一次成功的样子
//        printf("ret: %d, Line %d: %s\n", ret, i, str);
//    }
    while (ret != EOF) {
        ret = fscanf(fp, "%"STR(LINELEN)"[^\n]%*c", str);
    }
    printf("%s\n", str);

    char *p, *p2;
    p = strstr(str, "Player connected: ");  //18 个字符
    printf("p: %s\n", p);

//    p = strstr(str, "xyz");
//    if (!p)
//    printf("NULL\n");

    printf("p+18: %s\n", p+18);
    p2 = strstr(p+18, ",");
    printf("p2: %s\n", p2);

    printf("strlen(p)-strlen(p2)-18: %d\n", strlen(p)-strlen(p2)-18);
    strncpy(player, p+18, strlen(p)-strlen(p2)-18);
    printf("player: %s\n", player);


    fclose(fp);
    return 0;
}
