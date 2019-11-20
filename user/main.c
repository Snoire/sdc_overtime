#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "dayOfWeek.h"
#include "daysInaMonth.h"
#include "getCurrentTime.h"

#define COLOR_CYAN    "\x1b[36m"
#define COLOR_RESET   "\x1b[0m"

typedef struct clockinrecord{
    int date;
    int mark;
    int startime;
    int endtime;
    int duration;
} ClockinRecord; //给结构体起一个别名

ClockinRecord clkRecord[60];
int totalRecords=0; //总记录数

char filePath[70] = "";
//char filePath[7+32+18]= {0};

struct tm* tmp;  //保存时间信息
int pre_date;


//声明函数
static int welcome();
static int init();
static int doList();
static int doAdd();
static int doDelete();
static int doModify();
static int doSearch();
static int search(int);
static int writeToFile();
static int parseArg(int, char **);
static int showHelp();
static int changeRecord(int,int,int,int);
static int calDuration(int);
static int sort();
static int Del(int);
static int validRd(ClockinRecord *);



int main(int argc, char **argv)
{
    int num;
    int retParseArg=0;
    volatile int flag = 1;//退出的标志
    char str[2]; //只能放1个字符

    init();
    if((retParseArg=parseArg(argc,argv)) == 1)
    {
        welcome();
        while(flag)
        {    
            num = 0; //如果不恢复初始值，随便输入一个字母将保持上次的结果

            printf( COLOR_CYAN "(overtime) " COLOR_RESET );
            fgets(str, 2 , stdin); //读取1个字符
            if(*str==10)
                num = 0;
            else
            {
                num = *str;
                scanf("%*[^\n]"); scanf("%*c"); //清空缓冲区
            }

            switch(num)
            {
                case 'h':
                    printf("h: help    l: list     q: quit\n");
                    printf("a: add     d: delete   m: modify   s: search\n\n");
                    break;
                case 'a':
                    doAdd(); break;
                case 'd':
                    doDelete(); break;
                case 'm':
                    doModify(); break;
                case 'l':
                    doList(); break;
                case 's':
                    doSearch(); break;
                case 'q':
                    flag = 0; break;
                case 0:
                    break;
                default:
                    printf("invalid option.\n"); break;
            } //switch end..
        }  //while end
        printf("\nbye..\n\n");
    }
    if(retParseArg==-1)
        showHelp();
    return 0;
}



static int welcome()
{
    printf("Welcome to overtime!\n");
    printf("It is now at " "\x1b[4m" "%d:%.2d" "\033[0m" " on %s %d, %d, today is %s\n", tmp->tm_hour, tmp->tm_min, transMon(tmp->tm_mon+1), tmp->tm_mday, tmp->tm_year+1900, transWeek(tmp->tm_wday) );  // %.2d 确保它是两位数，不足补0
    printf("Still has " "%d" " days besides today!\n", daysInaMonth( tmp->tm_year+1900, tmp->tm_mon+1 ) - (tmp->tm_mday) );

    printf("\nFor help, type \"" "\x1b[33m"  "h" "\x1b[0m"  "\".\n");

    return 0;
}



static int init()
{
    int year, mon, day, hour1, hour2, min1, min2;
    char dataDir[7+32+6]= {0};

    tmp = getCurrentTime();  //初始化的时候就要存储时间信息
    pre_date = ((tmp->tm_year+1900)*100 + tmp->tm_mon+1) *100;

    char *homevar = getenv("HOME"); 
    strcat (dataDir, homevar);
    strcat (dataDir, "/.data");
    
    sprintf(filePath, "%s/.data/record_%d.data", homevar, (tmp->tm_year+1900)*100 + tmp->tm_mon+1);

    if ( access(dataDir, F_OK) != 0)  //文件夹不存在
        mkdir(dataDir, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

    FILE *fp = fopen(filePath,"r");
    
    if(fp!=NULL)
    {
        fscanf(fp, "%2d", &totalRecords);
        fscanf(fp,"%*[^\n]\n"); //读第一行，但不用
        
        for(int i = 0 ; i < totalRecords;i++)
        {
            fscanf(fp,"%*2d%6d/%2d/%2d%4d  %2d:%2d  %2d:%2d%7d\n",&year,&mon,&day,&clkRecord[i].mark,&hour1,&min1,&hour2,&min2,&clkRecord[i].duration );
            clkRecord[i].date = year*10000+mon*100+day;
            clkRecord[i].startime = hour1*100+min1;
            clkRecord[i].endtime = hour2*100+min2;
        }
        fclose(fp); //放在这里就正常了，本来在条件语句后面的，应该是关闭一个已经关闭的文件会发生错误
    }
    else // if file does not exit, create and init it.
    {
        writeToFile();
    }
    fp=NULL;

    return 0;
}



static int doList()
{
    int totalTime = 0;
    if(totalRecords==0)
    {
        printf("nothing..\n");
    }
    else
    {
        printf("%11s   %7s%7s%7s\n","Date","stime","etime","dur");
        for(int i = 0 ; i<totalRecords ;i++)
        {
            printf("%2d%6d/%.2d/%.2d  %.2d:%.2d  %.2d:%.2d%7d\n",i+1,clkRecord[i].date/10000,clkRecord[i].date/100%100,clkRecord[i].date%100,clkRecord[i].startime/100,clkRecord[i].startime%100,clkRecord[i].endtime/100,clkRecord[i].endtime%100,clkRecord[i].duration);  //用 %s 输出 int 会发生段错误
            totalTime += clkRecord[i].duration;
        }
        printf("\n");
        printf("total time: %d hours and %d minutes\n", totalTime/60, totalTime%60);
        printf("still needs: %d hours and %d minutes\n\n", (2400-totalTime)/60, (2400-totalTime)%60);
    }

    return 0;
}



static int doAdd()
{
    int date=0, stime, etime;
    int value=0, dayofw = 0;
    char str[3]; //最多能放2个字符
    printf("what's the day do you want to record?\n");
    printf("e.g. 1, default yesterday: ");

    for(int i=0; i<2; i++)
    {
        value = getchar();
        if(i==0 && value == '\n')        //用户输入 \n
        {
            dayofw = dayOfWeek( (tmp->tm_year+1900)*10000+(tmp->tm_mon+1)*100+tmp->tm_mday-1 ); //前一天是周几?
            if(tmp->tm_mday==1)
                date = pre_date + tmp->tm_mday;
            else if( dayofw == 0)        //星期天
                date = pre_date + tmp->tm_mday-3; //前一个工作日
            else if( dayofw == 6)        //星期六
                date = pre_date + tmp->tm_mday-2; //前一个工作日
            else
                date = pre_date + tmp->tm_mday-1; //前一个工作日

            break;
        }
        else if(i==1 && value == '\n')   //用户输入一个数字加换行
        {
            date += pre_date;
            break;
        }
        date = date*10 + value-48;
        if(i==1)                         //用户输入两个数字
        {
            date += pre_date;
            scanf("%*[^\n]"); scanf("%*c"); //清空缓冲区
        }
    }

    printf("\nwhat's the time when you clock in?\n");
    printf("e.g. 2, 02 or 1802, default 18:00: ");
    fgets(str, 5, stdin); //读取4个字符
    if(*str==10)  //第一个字符是换行，也就是说直接按了换行键
        stime = 1800;
    else if( *(str+1)=='\n' || *(str+2)=='\n' )  //第二个或第三个字符是换行，也就是说只读取了一或两个字符
        stime = 18*100 + atoi(str);
    else if( *(str+3)!='\n' && *(str+3)!=0 )  //只有在第四个字符既不是\n，也不是\0的时候，也就是说缓冲区里有多余的字符时，才能去清空缓冲区
    {
        stime = atoi(str);
        scanf("%*[^\n]"); scanf("%*c"); //在下次读取前清空缓冲区，如果缓冲区里有东西，这里就会卡住
    }
    else  //输入三个字符
        stime = atoi(str);
    
    printf("\nwhat's the time when you clock out?\n");
    printf("e.g. 4, 04 or 2004, default 20:00: ");
    fgets(str, 5, stdin); //读取4个字符
    if(*str==10)
        etime = 2000;
    else if( *(str+1)=='\n' || *(str+2)=='\n' )
        etime = 20*100 + atoi(str);
    else if( *(str+3)!='\n' && *(str+3)!=0 )
    {
        etime = atoi(str);
        scanf("%*[^\n]"); scanf("%*c"); //清空缓冲区
    }
    else  //输入三个字符
        etime = atoi(str);

    changeRecord( 0, date, stime, etime);
    printf("\n");

    return 0;
}



static int doDelete()
{
    int delnum;
    char str[2];
    doList();
    
    printf("please input the num that you want to del:\n");
    printf("default the last one: ");
    fgets(str, 2, stdin); //读取1个字符
    if(*str==10)
        delnum = totalRecords;
    else
    {
        delnum = atoi(str);
        scanf("%*[^\n]"); scanf("%*c"); //清空缓冲区
    }

    Del(delnum);
    writeToFile();
    printf("\n");

    return 0;
}



static int Del(int delnum)
{
    int result=0;
    if(delnum<1 || delnum > totalRecords)
        return 0;
     
    if(delnum==totalRecords)
        totalRecords--;
    else
    {
        result = delnum -1;  //要删除的记录的下标（从0开始）
        while( ((result+1) < totalRecords) && clkRecord[result+1].mark==(clkRecord[result].mark+1) )  //找到mark值最大的一条记录
            result++;
        for(int i = delnum -1; i < result; i++)
            clkRecord[i+1].mark --;

        for(int i = delnum; i <totalRecords;i++)
            clkRecord[i-1]=clkRecord[i];
        totalRecords--;
    }
    return 0;
}



static int doModify()
{
    char str[5];
    int stime, etime, modnum;
    doList();

    printf("please input the num that you what to modify:\n");
    printf("default the last one: ");
    fgets(str, 2, stdin); //读取1个字符
    if(*str==10)
        modnum = totalRecords;
    else
    {
        modnum = atoi(str);
        scanf("%*[^\n]"); scanf("%*c"); //清空缓冲区
    }

    if(modnum<1||modnum>totalRecords)
        return 0;
    
    printf("what's the time when you clock in?\n");
    printf("e.g. 2, 02 or 1802, default 18:00: ");
    fgets(str, 5, stdin); //读取4个字符
    if(*str==10)  //直接按换行键
        stime = 1800;
    else if( *(str+1)=='\n' || *(str+2)=='\n' )  //只读取了一或两个字符
        stime = 18*100 + atoi(str);
    else if( *(str+3)!='\n' && *(str+3)!=0 )  //缓冲区里有多余的字符
    {
        stime = atoi(str);
        scanf("%*[^\n]"); scanf("%*c");
    }
    else  //输入三个字符
        stime = atoi(str);
    
    printf("what's the time when you clock out?\n");
    printf("e.g. 4, 04 or 2004, default 20:00: ");
    fgets(str, 5, stdin); //读取4个字符
    if(*str==10)
        etime = 2000;
    else if( *(str+1)=='\n' || *(str+2)=='\n' )
        etime = 20*100 + atoi(str);
    else if( *(str+3)!='\n' && *(str+3)!=0 )
    {
        etime = atoi(str);
        scanf("%*[^\n]"); scanf("%*c"); //清空缓冲区
    }
    else  //输入三个字符
        etime = atoi(str);
    
    changeRecord( modnum, 0, stime, etime);
    printf("\n");

    return 0;
}



static int doSearch()
{
    int value=0, searchDate=0, retNum;
    printf("which day do you want to search: ");

    for(int i=0; i<2; i++)
    {
        value = getchar();
        if(i==0 && value == '\n')        //用户输入 \n
        {
            if(tmp->tm_mday==1)
                searchDate = pre_date + tmp->tm_mday;
            else
                searchDate = pre_date + tmp->tm_mday-1; //前一天
            break;
        }
        else if(i==1 && value == '\n')   //用户输入一个数字加换行
        {
            searchDate += pre_date;
            break;
        }

        searchDate = searchDate*10 + value-48;
        if(i==1)                         //用户输入两个数字
        {
            searchDate += pre_date;
            scanf("%*[^\n]"); scanf("%*c"); //清空缓冲区
        }
    }

    retNum=search(searchDate);
    if(retNum>=0)
    {
        do
        {
            printf("%2d%6d/%.2d/%.2d%4d  %.2d:%.2d  %.2d:%.2d%7d\n",retNum+1,clkRecord[retNum].date/10000,clkRecord[retNum].date/100%100,clkRecord[retNum].date%100,clkRecord[retNum].mark,clkRecord[retNum].startime/100,clkRecord[retNum].startime%100,clkRecord[retNum].endtime/100,clkRecord[retNum].endtime%100,clkRecord[retNum].duration);  //用 %s 输出 int 会发生段错误
            retNum++;
            
        }while( ((retNum) < totalRecords) && clkRecord[retNum].mark==(clkRecord[retNum-1].mark+1) );  //不能让它访问越界

    }
    else if(retNum==-1)
        printf("no record found in %d/%.2d/%.2d.\n",searchDate/10000,searchDate/100%100,searchDate%100);

    return 0;
}



static int search(int searchDate)
{
    int i=0;
    for(i; i< totalRecords; i++)
        if(searchDate==clkRecord[i].date)
            return i;
    if(i==totalRecords)
        return -1;

    return -2;
}



static int writeToFile()
{
    sort();
    FILE *fp = fopen(filePath,"w+");
    if(fp!=NULL)
    {
        fprintf(fp,"%2d%9s   %4s%7s%7s%7s\n", totalRecords, "Date", "m", "stime","etime","dur");   
        for(int i = 0; i< totalRecords; i++)
        {
            fprintf(fp,"%2d%6d/%.2d/%.2d%4d  %.2d:%.2d  %.2d:%.2d%7d\n",i+1,clkRecord[i].date/10000,clkRecord[i].date/100%100,clkRecord[i].date%100,clkRecord[i].mark,clkRecord[i].startime/100,clkRecord[i].startime%100,clkRecord[i].endtime/100,clkRecord[i].endtime%100,clkRecord[i].duration );
        }
        fclose(fp);
    }
    else
        printf("open file error!\n");

    return 0;
}



static int parseArg(int argc, char **argv)
{
    int opt, number=0, date=0, stime=0, etime=0;  //number 是第一列的编号
    int option_index = 0;
    struct option long_options[]={
        {"help",no_argument, NULL, 'H'},
        {"version",no_argument, NULL, 'V'},
        {"list",no_argument, NULL, 'L'}
    };
    if(argc==1)
        return 1; //进入主循环
    while( (opt=getopt_long(argc, argv, "d:s:e:M:D:hlv",long_options,&option_index)) != -1 ) //少加了一个括号..
    {
        switch(opt)
        {
            case 'd':
                date = atoi(optarg); //这里应该判断一下
                date += pre_date;
                break;
            case 's':
                stime = atoi(optarg);
                break;
            case 'e':
                etime = atoi(optarg);
                break;
            case 'M':
                number = atoi(optarg);
                break;
            case 'D':
                Del(atoi(optarg));
                writeToFile();
                return 0;
            case 'H':
            case 'h':
                showHelp();
                break;
            case 'L':
            case 'l':
                doList();
                break;
            case 'V':
            case 'v':
                printf("overtime: version 1.1.0\n");
                break;
            default:
                return -1;
        }
    }
    if( (date+stime+etime) !=0) //至少有一个不为0
    {
        if( changeRecord(number,date,stime,etime) == -1 )
            return -2;
    }

    return 0;  //返回0的话，就是正常解析选项
}



static int changeRecord(int number, int date, int stime, int etime)
{
    int result, dayofw=0;

    if(stime==0)
        stime = 1800;      //如果未指定这个参数，则默认为 1800
    else if(stime < 100)
        stime += 1800;     //如果指定的参数是两位数，说明省略了小时，则加上 1800

    if(etime==0)
        etime = 2000;
    else if(etime < 100)
        etime += 2000;

    if(number==0)  //增加记录
    {
#if 1
        if(date==0)
        {
            dayofw = dayOfWeek( (tmp->tm_year+1900)*10000+(tmp->tm_mon+1)*100+tmp->tm_mday-1 ); //前一天是周几?
            if(tmp->tm_mday==1)          //今天是 1 号，也就是不能再往前了
                date = pre_date + tmp->tm_mday;
            else if( dayofw == 0)        //星期天
                date = pre_date + tmp->tm_mday-3;   //前一个工作日
            else if( dayofw == 6)        //星期六
                date = pre_date + tmp->tm_mday-2;   //前一个工作日
            else
                date = pre_date + tmp->tm_mday-1;   //前一个工作日
        }
#else
        if(date==0)
        {
            if(tmp->tm_mday==1)
                date = pre_date + tmp->tm_mday;
            else
                date = pre_date + tmp->tm_mday-1; //前一天
        }
#endif
        result = search(date);
        totalRecords ++;

        if(result==-1)  //未找到记录，在最后添加
        {
            clkRecord[totalRecords-1].date = date;
            clkRecord[totalRecords-1].mark = 1;
            clkRecord[totalRecords-1].startime = stime;
            clkRecord[totalRecords-1].endtime = etime;
            calDuration(totalRecords-1);

            int ret = validRd(&clkRecord[totalRecords-1]);
            if(  ret < 0 )
            {
                printf("date format error! ret = %d\n", ret);
                totalRecords--;  //把最后一条排除在外，相当于删掉了
            }
        }
        else  //找到记录，紧随其后添加
        {
            while( ((result+1) < totalRecords-1) && clkRecord[result+1].mark==(clkRecord[result].mark+1) )  //找到mark值最大的一条记录
                result++;

            for(int i=totalRecords-1; i> result+1; i--) //向后腾出空间
            {
                clkRecord[i] = clkRecord[i-1];
            }
            clkRecord[result+1].date = date;
            clkRecord[result+1].mark = clkRecord[result].mark + 1;
            clkRecord[result+1].startime= stime;
            clkRecord[result+1].endtime= etime;
            calDuration(result+1);

            if( validRd(&clkRecord[result+1]) < 0 )
            {
                printf("date format error!\n");
                Del(result+2);
            }
        }
    }
    else if(number > 0 && number <= totalRecords)  //修改记录
    {
        number --;

        clkRecord[totalRecords] = clkRecord[number];  //clkRecord[totalRecords] 这个是范围之外的，拿来做临时存储的地方，之后也不用删除
        clkRecord[totalRecords].startime = stime;
        clkRecord[totalRecords].endtime = etime;

        if( validRd(&clkRecord[totalRecords]) >= 0 )
        {
            clkRecord[number] = clkRecord[totalRecords];
            calDuration(number);
        }
        else
            printf("date format error!\n");
    }
    
    writeToFile();
    
    return 0;
}



static int showHelp()
{
    printf("Usage: overtime [-hlv] [-d day] [-s stime] [-e etime] [-M number] [-D number]\n\n");
    printf("Options:\n"
            "\t-h, --help           show help\n"
            "\t-l, --list           show list\n"
            "\t-v, --version        show version\n"
            "\t-d day               choose the day you want to modify\n"
            "\t-s stime             change the start time\n"
            "\t-e etime             change the end time\n"
            "\t-M number            modify record\n"
            "\t-D number            delete record\n"
            "\n");

    return 0;
}



static int calDuration(int i)
{
    int shour, smin, ehour, emin, dur;

    shour = clkRecord[i].startime/100; 
    smin = clkRecord[i].startime%100; 
    ehour = clkRecord[i].endtime/100; 
    emin = clkRecord[i].endtime%100; 
    dur = (ehour-shour)*60+emin-smin;
    clkRecord[i].duration = ( dur < 30 ) ? 0 : dur;
}



static int sort()
{
    ClockinRecord recordTmp;
    for(int i=0; i< totalRecords-1; i++)
    {
        for(int j=i+1; j< totalRecords; j++)
        {
            if(clkRecord[j].date < clkRecord[i].date || (clkRecord[j].date == clkRecord[i].date && clkRecord[j].mark < clkRecord[i].mark) )
            {
                recordTmp = clkRecord[i];
                clkRecord[i] = clkRecord[j];
                clkRecord[j] = recordTmp;
            }
        }
    }

    return 0;
}



static int validRd( ClockinRecord * recordTmp )
{
    if( (recordTmp->date%100) > daysInaMonth( tmp->tm_year+1900, tmp->tm_mon+1 ) || (recordTmp->date%100) < 1 )
        return -1;   //日期超出范围
    else if( recordTmp->startime >= recordTmp->endtime ||    //开始时间居然比结束时间还晚?!
            recordTmp->startime%100 > 59 || recordTmp->startime%100 < 0  ||
            recordTmp->startime/100 > 23 || recordTmp->startime/100 < 0  ||
            recordTmp->endtime%100 > 59 || recordTmp->endtime%100 < 0  ||
            recordTmp->endtime/100 > 23 || recordTmp->endtime/100 < 0  )
        return -2;
    else
    {

    }

    return 0;
}




