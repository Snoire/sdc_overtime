#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
	char str[] = "root:x::0:root:/root:/bin/bash:";
	char *token, *saveptr = NULL, *p;
    printf("%s, strlen: %ld\n", str, strlen(str));

    for (int i = 1, p = str; ; i++, p = NULL) {  /* 这里会有问题 */
        token = strtok_r(p, ":", &saveptr);      /* 这种写法相当于定义了 int p 的局部变量。。 */
        if (token == NULL)                       /* 但是很奇怪，我是直接从 strtok_r 的 man 手册上抄的 */
            break;                               /* 为啥作者能编译，我却编不过 */
        printf("%d: %s\n", i, token);
    }

	return 0;
}
