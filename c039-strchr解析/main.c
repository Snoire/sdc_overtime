#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
    char var[1024], value[1024];
    char *equal = NULL;

    printf("argv[1]: %s\n", argv[1]);
    printf("strlen(argv[1]) = %d\n", strlen(argv[1]));

    memset(var, 0, sizeof(var));
    memset(value, 0, sizeof(value));
    equal = strchr(argv[1], '=');
    memcpy(var, argv[1], equal-argv[1]);     //复制从第一个字符到 '=' 之前的字符到 var，注意没有 \0，但是因为之前全都初始化为0，所以没出错
    memcpy(value, equal+1, strlen(argv[1])-(equal-argv[1]));  //复制从 '=' 之后的字符到最后的 \0 到 value


    printf("var: %s\n", var);
    printf("strlen(var) = %d\n", strlen(var));

    printf("value: %s\n", value);
    printf("strlen(value) = %d\n", strlen(value));

    return 0;
}

