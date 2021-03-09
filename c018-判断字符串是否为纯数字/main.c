#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main()
{
    char str[10] = "";
    char num[10] = "";
//    scanf("%s",str);   //不要对 str 取地址，虽然加了也没事。。
//    if(strspn(str, "0123456789")==strlen(str)) {
//        if(atoi(str)>0)   //判断是否是自然数，好像这句重复了，不需要，，不管它，我都提交了
//            printf("str=%s, it's a num\n",str);
//        else
//            printf("str=%s, it's not a num\n",str);
//    }
//    else
//        printf("str=%s, it's not a num\n",str);

/*
    scanf("%9[0-9]", str);              //只读取纯数字，不要傻乎乎地写 scanf("%9[0123456789]", str);
    printf("str=%s\n",str);
*/
    scanf("%9s", str);                         //先存下来
    sscanf(str, "%9[0-9]", num);
    if (strlen(str) == strlen(num))            //再比较
        printf("str=%s, it's a num\n",str);
    else
        printf("str=%s, it's not a num\n",str);

    return 0;
}

