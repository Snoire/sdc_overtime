#include<stdio.h>
#include<unistd.h>

int main()
{
    printf("prompts written to stdout that don’t include a terminating newline character");
    scanf("%*c");   //隐含了调用了一次 fflush(stdout); tlpi page 239
    sleep(5);  //程序暂停5秒钟
    printf("第一行和这一行一起输出了\n");

    return 0;
}
