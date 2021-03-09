# include <stdio.h>
int main()
{
    char a[2][4] = {"abc","xyz"};
    int *p = NULL;
    char str1[]="";
    char str2[]=" ";
    int b = -1;
    
    if (a[2]) {
        printf("真\n");
        printf("a[1]=%s\n",a[1]);  //a[1] 的值自然是 xyz 啦
        printf("a[2]=%s\n",a[2]);  //a[2] 的值每次都不一样，这应该是数组访问越界吧
    } else {
        printf("假\n\n");
    }

    if (p) {
        printf("NULL指针为真\n");
    } else {
        printf("NULL指针为假\n");
    }

    if (str1) {
        printf("空字符串为真\n");
    } else {
        printf("空字符串为假\n");
    }

    if (*str1) {
        printf("*空字符串为真\n");
    } else {
        printf("*空字符串为假\n");
    }

    if (str2) {
        printf("空格字符串为真\n");
    } else {
        printf("空格字符串为假\n");
    }

    if (b) {
        printf("负数为真\n");
    } else {
        printf("负数为假\n");
    }

    return 0;
}

