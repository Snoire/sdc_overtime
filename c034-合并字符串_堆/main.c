#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main()
{
    char * a1 = NULL;
    char * a2 = NULL;
    int lengthA1;          //a1串的长度
    int lengthA2;          //a2串的长度

    a1 = (char*)malloc(10 * sizeof(char));
    strcpy(a1, "data.bian");                  //将字符串"data.bian"复制给a1
//    a1 = "data.bian";                       //不可以这样给它赋值，"data.bian" 是存在常量区的，这一步相当于把 a1 指向 "data.bian"
    printf("a1 = %s\n", a1);                  //用 cgdb 查看，就知道，a1 的值改变了
    printf("a1 = %c\n", *a1);
    printf("a1 = %d\n", a1[9]);

    a2 = (char*)malloc(10 * sizeof(char));
    strcpy(a2, "cheng.net");

    lengthA1 = strlen(a1);
    lengthA2 = strlen(a2);

    //尝试将合并的串存储在 a1 中，如果 a1 空间不够，则用realloc动态申请
    if (lengthA1 < lengthA1 + lengthA2)
	{
        a1 = (char*)realloc(a1, (lengthA1 + lengthA2+1) * sizeof(char));
    }

    //合并两个串到 a1 中
    for (int i = lengthA1; i < lengthA1 + lengthA2; i++)
    {
        a1[i] = a2[i - lengthA1];
    }

    //串的末尾要添加 \0，避免出错
    a1[lengthA1 + lengthA2] = '\0';
    printf("%s", a1);
    printf("\n");

    //用完动态数组要立即释放
    free(a1);
    free(a2);

    printf("a1 = %s\n", a1);    //仍然可以访问，可能是因为为了避免频繁进行系统调用，等要释放的内存多了才统一释放
    printf("a1 = %c\n", *a1);
    printf("a1 = %d\n", a1[9]);

    return 0;
}


