#include <stdio.h>

int i = 0;
//int i = 12;   //这里会报错

int func()
{
    static int j = 0;
    j++;
    return j;
}

int main()
{
    printf("i= %d\n",i);
    if(i==0)
        printf("全局静态变量只能初始化一次\n第二次会被报错\n");

    printf("1. j= %d\n",func());
    printf("2. j= %d\n",func());
    printf("局部静态变量只能初始化一次\n第二次会被忽略\n");

}
