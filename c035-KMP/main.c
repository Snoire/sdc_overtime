#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kmp.h"


char * getstr(void);

int main()
{
    char *str1=NULL, *str2=NULL;    //这样写不能直接用 scanf 读取，字符串不定长

    printf("输入两个字符串：\n");
    str1 = getstr();
    str2 = getstr();

//    printf("ret = %d\n", kmp(str1, str2));
    int ret = kmp(str1, str2);
    for(int i=0; *(str1+i)!=0; i++)
    {
        printf("", str1[i]);
    }

    free(str1);
    free(str2);

    return 0;
}

