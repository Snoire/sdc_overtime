# include <stdio.h>

int func2()
{
    int i = 0;
    for (i; i<0; i++)
    {
        printf("不存在！\n");
    }
    printf("i=%d\n由此可证，上面的循环未被执行\n",i);

    return 0;
}

