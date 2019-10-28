#include <stdio.h>

char clearInput;

int dayOfWeek( int tmp, int m, int d)
{
//    int w, y, c, m, d;
//    int tmp;
//    printf("please input the date:         [format: 2019/10/24]\n");
//    scanf("%d/%d/%d",&tmp,&m,&d);
//    while((clearInput = getchar()) != '\n' && clearInput != EOF); //在下次读取前清空缓冲区
    
    int w, y, c;

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
    
    return w;
}

char * transWeek( int w )
{
    char * pstr;
    switch(w){
        case 0:  pstr = "Sunday";   break;
        case 1:  pstr = "Monday";   break;
        case 2:  pstr = "Tuesday";  break;
        case 3:  pstr = "Wednesday";break;
        case 4:  pstr = "Thursday"; break;
        case 5:  pstr = "Friday";   break;
        case 6:  pstr = "Saturday"; break;
        case 7:  pstr = "Sunday";   break;
    }

    return pstr;
}

