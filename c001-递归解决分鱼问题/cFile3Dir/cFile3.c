# include <stdio.h>
int func3()
{
    enum week{mon, tues=mon,wed} day;
    day= mon;
    printf("mon=%d\n",day);
    day= tues;
    printf("tues=%d\n",day);
    day= wed;
    printf("wed=%d\n",day);
    printf("wed=%d\n",wed);

    return 0;
}
