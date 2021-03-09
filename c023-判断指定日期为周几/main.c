#include <stdio.h>

char clearInput;

int main()
{
    int w, y, c, m, d;
    int tmp;
    printf("please input the date:         [format: 2019/10/24]\n");
    scanf("%d/%d/%d",&tmp,&m,&d);
    while((clearInput = getchar()) != '\n' && clearInput != EOF); //在下次读取前清空缓冲区
    
    c = tmp/100;     //取出前两位
    y = tmp%100;     //取出后两位
    if( m>0 && m<3)  //我一开始写的是 0<m<3，，为什么不报错呀
    {
        m = m+12;
        y = y-1;
    }

    w = y + (y/4) + (c/4) - 2*c + ((26*(m+1)/10)) + d-1;
    if(w<0)
        w= 7-(-w)%7;
    else
        w= w%7;
    printf("%d\n",w);
    
    return 0;
}

