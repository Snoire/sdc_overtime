#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE * fp;
    char buf[32] = "logId<17>";
    char count[16] = "";
    if((fp=fopen("log.txt","r"))==NULL)
    {
      printf("cant open the file");
      exit(0);
    }
    sscanf(buf, "%*6s%s>", count);  // 这里要用 %s 来存储，不要看它是数字就用 %d 。。
    printf("count: %s\n", count);

    sscanf(buf, "logId<%s>", count); // 虽然看上去 %s 用 <> 限定住了，但是 %s 遇到空白符才停止，所以后一个 > 无法限制它
    printf("count: %s\n", count);

    sscanf(buf, "logId<%[^>]", count); // 这种才可以
    printf("count: %s\n", count);

    fscanf(fp, "logId<%15[^>]", count);  // 或者换成 %*6s
    printf("count: %s\n", count);

    return 0;
}

