#include <stdio.h>

/*赋值字母给 %d 会怎么样？*/
int main()
{   
    int num = 0;
    scanf("%d",&num);
    printf("%d\n",num);
    printf("%s\n",num);
    printf("%c\n",num);
    return 0;
}

