#include <stdio.h>
#define LEN 256             //不包括 \0 的长度
#define STR(x) STR2(x)     //http://m.newsmth.net/article/LinuxDev/61121
#define STR2(x) #x

int main()
{
    int i; 
    int total=0, space=0, number=0;
    int uppercase=0, lowercase=0;
    char str[LEN+1] = "";

    printf("input a str: \n");
    scanf("%"STR(LEN)"[^\n]%*c", str);    //只能写 LEN，不能进行运算，因为是转换成字符串
                                          //还有个办法，用 sprintf 构造格式化字符串，不过这样就要在运行时计算了

    for (i = 0; *(str+i); i++) {
        if (*(str+i) == ' ')
            space++;
        else if (*(str+i)>='0' && *(str+i)<='9')
            number++;
        else if (*(str+i)>='A' && *(str+i)<='Z')
            uppercase++;
        else if (*(str+i)>='a' && *(str+i)<='z')
            lowercase++;
    }
    total = i;

    printf("reverse: ");
    for (i--; i>=0; i--)
        printf("%c", *(str+i));
    printf("\n");

    printf("space: %d\n", space);
    printf("number: %d\n", number);
    printf("uppercase: %d\n", uppercase);
    printf("lowercase: %d\n", lowercase);
    printf("others: %d\n", total-space-number-uppercase-lowercase);

    return 0;
}
