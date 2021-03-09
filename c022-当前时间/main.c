#define _XOPEN_SOURCE   //这个还必须放在最上面。。
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

int main()
{
    /* 获取 calendar time（一串数字） */
    struct timeval tv;
//    struct timezone tz;
//    gettimeofday(&tv,&tz);
    gettimeofday(&tv, NULL);  //听说要这样用？
    printf("time is %ld s\n",tv.tv_sec); //TLPI 第10章，获取秒数
    printf("utime is %ld us\n",tv.tv_usec); //TLPI 第10章，获取微秒数

    /* time 函数类似，但是精度只能到秒 */   // 与之类似，settimeofday() 和 stime() 用来设定时间，但是需要特权（ CAP_SYS_TIME）
    time_t time1, time2;

//    time2 = time(&time1);
//    printf("time1 = %ld\n", time1);
//    printf("time2 = %ld\n", time2); //两者相同，所以实际使用时只需要：

    time2 = time(NULL);
    printf("time2 = %ld\n", time2);

    /* 转换成可读的形式之 broken-down times: struct tm */
    struct tm *tmp1, *tmp2;

    /* Greenwich Mean Time */
    tmp1 = gmtime(&time2);
    printf("year: %d, mon: %d, day: %d, h: %d, m: %d, s: %d, wday: %d\n",
            tmp1->tm_year+1900, tmp1->tm_mon+1, tmp1->tm_mday, tmp1->tm_hour,
            tmp1->tm_min, tmp1->tm_sec, tmp1->tm_wday?tmp1->tm_wday:7);
    /* 当地时间 */
    tmp2 = localtime(&(tv.tv_sec));
    printf("year: %d, mon: %d, day: %d, h: %d, m: %d, s: %d, wday: %d\n",   //基本上也就是小时（tm_hour）变了一下
            tmp2->tm_year+1900, tmp2->tm_mon+1, tmp2->tm_mday, tmp2->tm_hour,
            tmp2->tm_min, tmp2->tm_sec, tmp2->tm_wday?tmp2->tm_wday:7);     //注意，虽然设了两个 tm *指针，但是这个时候，tmp1 所指向的结构体已经被 localtime 修改了，不信你再打印一次 tmp1 的数据试试
/*
    printf("year: %d, mon: %d, day: %d, h: %d, m: %d, s: %d, wday: %d\n",
            tmp1->tm_year+1900, tmp1->tm_mon+1, tmp1->tm_mday, tmp1->tm_hour,
            tmp1->tm_min, tmp1->tm_sec, tmp1->tm_wday?tmp1->tm_wday:7);
*/
    /* 所以要保存一下 */
    struct tm gmt, ltime;
    tmp1 = gmtime(&time2);
    gmt = *tmp1;
    tmp1 = localtime(&time2);   //只需要使用一个指针（tmp1）就好了
    ltime = *tmp1;

    /* 转换成 fixed-format string */
    printf("\nthe fixed-format string is: %s\n", ctime(&time2));  //这个字符串最后包含 \n\0，所以会换两行

    /* 把 localtime 转换成 calendar time */
    time1 = mktime(tmp2);
    printf("calendar time is: %ld\n", time1);

    /* 把 struct tm 转换成 fixed-format string */
    printf("\nthe fixed-format string of gmt is: %s\n", asctime(&gmt));  //这个字符串最后包含 \n\0，所以会换两行
    printf("the fixed-format string of localtime is: %s\n", asctime(&ltime));  //这个字符串最后包含 \n\0，所以会换两行

    /* 把 struct tm 转换成 格式化字符串 */
    char buffer[120] = "";
    strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", &ltime);
    printf("the format str is: %s\n", buffer);
    /* 再转回来 */
    memset(&ltime, 0, sizeof(struct tm));
    strptime(buffer, "%Y-%m-%d %H:%M:%S", &ltime);
    tmp1 = &ltime;
    printf("year: %d, mon: %d, day: %d, h: %d, m: %d, s: %d, wday: %d\n",
            tmp1->tm_year+1900, tmp1->tm_mon+1, tmp1->tm_mday, tmp1->tm_hour,
            tmp1->tm_min, tmp1->tm_sec, tmp1->tm_wday?tmp1->tm_wday:7);

    return 0;
}

