#include <stdio.h>
#include <time.h>
#include <sys/time.h>


struct tm* get_current_time()
{
    struct timeval tv;
//    struct timezone tz;
    struct tm* tmp;

    gettimeofday(&tv, NULL);  //This tz argument is now obsolete and should always be specified as NULL.
//    printf("time is %d\n",tv.tv_sec); //TLPI 第10章，获取秒数

    tmp = localtime(&(tv.tv_sec));

//    printf("year: %d, mon: %d, day: %d, h: %d, m: %d, s: %d, wday: %d\n",
//          tmp->tm_year+1900, tmp->tm_mon+1, tmp->tm_mday, tmp->tm_hour,
//          tmp->tm_min, tmp->tm_sec, tmp->tm_wday?tmp->tm_wday:7);

    return tmp;
}

char * trans_mon( int m )
{
    char * pstr;
    switch(m){
        case 1:  pstr = "January";  break;
        case 2:  pstr = "February"; break;
        case 3:  pstr = "March";    break;
        case 4:  pstr = "April";    break;
        case 5:  pstr = "May";      break;
        case 6:  pstr = "June";     break;
        case 7:  pstr = "July";     break;
        case 8:  pstr = "August";   break;
        case 9:  pstr = "September";break;
        case 10: pstr = "October";  break;
        case 11: pstr = "November"; break;
        case 12: pstr = "December"; break;
    }
    return pstr; 
}

