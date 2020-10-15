#include <stdio.h>

char clearInput;

int dayOfWeek(int date) //output: 0-6, 0 for sun..  input: date format: 20191108
{
    int w, y, c, m, d;
    c = date/1000000;
    y = date/10000%100;
    m = date/100%100;
    d = date%100;
    
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
    
    return w;
}

char * transWeek(int w)
{
    char * pstr;
    switch(w){
        case 1:  pstr = "Monday";   break;
        case 2:  pstr = "Tuesday";  break;
        case 3:  pstr = "Wednesday";break;
        case 4:  pstr = "Thursday"; break;
        case 5:  pstr = "Friday";   break;
        case 6:  pstr = "Saturday"; break;
        case 7:
        case 0:  pstr = "Sunday";   break;
    }

    return pstr;
}

