#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <time.h>

#include "dayOfWeek.h"
#include "daysInaMonth.h"
#include "getCurrentTime.h"

typedef struct clockInRecord{
    int date;
    int mark;
    int startime;
    int endtime;
    int duration;
} CLOCKINRECORD; //给结构体起一个别名

CLOCKINRECORD clkRecord[60];
int totalRecords=0; //总记录数
char *filePath="data/record.data";
struct tm* tmp;  //保存时间信息

char clearInput;

//声明函数
static int welcome();
static int init();
static int doList();
static int doAdd();
static int doDelete();
static int doModify();
static int doSearch(int);
static int writeToFile();
static int parseArg(int, char **);
static int showHelp();
static int changeRecord(int,int,int,int);
static int calDuration(int);
static int sort();
static int Del(int);



int main(int argc, char **argv)
{
    int num;
    int searchDate;
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

            printf("(overtime) ");
            fgets(str, 2 , stdin); //读取1个字符
            if(*str==10)
                num = 0;
            else
            {
                num = *str;
                while((clearInput = getchar()) != '\n' && clearInput != EOF); //在下次读取前清空缓冲区
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
                    printf("please input the date that you want to search:\n");
                    scanf("%d",&searchDate);
                    while((clearInput = getchar()) != '\n' && clearInput != EOF); //在下次读取前清空缓冲区

                    searchDate=doSearch(searchDate); //懒得再定义一个变量。。
                    if(searchDate>=0)
                    {
                        printf("%2d%10d%4d%7d%7d%7d\n",searchDate+1,clkRecord[searchDate].date,clkRecord[searchDate].mark,clkRecord[searchDate].startime,clkRecord[searchDate].endtime,clkRecord[searchDate].duration);  //用 %s 输出 int 会发生段错误
                        while( ((searchDate+1) < totalRecords) && clkRecord[searchDate+1].mark==(clkRecord[searchDate].mark+1) )  //不能让它访问越界
                        {
                            searchDate++;
                            printf("%2d%10d%4d%7d%7d%7d\n",searchDate+1,clkRecord[searchDate].date,clkRecord[searchDate].mark,clkRecord[searchDate].startime,clkRecord[searchDate].endtime,clkRecord[searchDate].duration);  //用 %s 输出 int 会发生段错误
                        }
                    }
                    else if(searchDate==-1)
                        printf("no record found here.\n");

                    break;
                case 'q':
                    flag = 0;
                    break;
                case 0:
                    break;
                default:
                    printf("ops!\n");
                    break;
            } //switch end..
        }  //while end
        printf("\nThe end..\n\n");
    }
    if(retParseArg==-1)
        showHelp();
    return 0;
}

static int welcome()
{
    printf("Welcome to overtime!\n");
    printf("It is now at %d:%d on %s %d, %d, today is %s\n", tmp->tm_hour, tmp->tm_min, transMon(tmp->tm_mon+1), tmp->tm_mday, tmp->tm_year+1900, transWeek(tmp->tm_wday) );
    printf("Still has %d days besides today!\n", daysInaMonth( tmp->tm_year+1900, tmp->tm_mon+1 ) - (tmp->tm_mday) );

    printf("\nFor help, type \"h\".\n");

//    printf("Please input the time you got off work yesterday: \n");
    return 0;
}

static int init()
{
    tmp = getCurrentTime();  //初始化的时候就要存储时间信息

    FILE *fp = fopen(filePath,"r");
    
    if(fp!=NULL)
    {
        fscanf(fp, "%2d", &totalRecords);
        fscanf(fp,"%*[^\n]\n"); //读第一行，但不用
        
        for(int i = 0 ; i < totalRecords;i++)
        {
            fscanf(fp,"%*2d%10d%4d%7d%7d%7d\n",&clkRecord[i].date,&clkRecord[i].mark,&clkRecord[i].startime,&clkRecord[i].endtime,&clkRecord[i].duration );
        }
    }
    else // if file does not exit, create and init it.
    {
        fp = fopen(filePath,"w");  //这里为什么要加这一句，下面调用的函数里有这一句啊
        writeToFile();
    }
    fclose(fp);
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
        printf("%2d%10s%4s%7s%7s%7s\n",totalRecords,"date","m","stime","etime","dur");
        for(int i = 0 ; i<totalRecords ;i++)
        {
            printf("%2d%10d%4d%7d%7d%7d\n",i+1,clkRecord[i].date,clkRecord[i].mark,clkRecord[i].startime,clkRecord[i].endtime,clkRecord[i].duration);  //用 %s 输出 int 会发生段错误
            totalTime += clkRecord[i].duration;
        }
        printf("totalTime: %d minutes\n\n",totalTime);
    }

    return 0;
}

static int doAdd()
{
    int date, stime, etime;
    char str[9]; //最多能放8个字符
    printf("what's the date do you want to record?\n");
    printf("e.g. 20191024, default yesterday: ");
    fgets(str, 9, stdin); //读取8个字符
    if(*str==10)
        date = (tmp->tm_year+1900)*10000 + (tmp->tm_mon+1)*100 + tmp->tm_mday-1; //前一天
    else
    {
        date = atoi(str);
        while((clearInput = getchar()) != '\n' && clearInput != EOF); //在下次读取前清空缓冲区
    }

    printf("what's the time when you clock in?\n");
    printf("default 1800: ");
    fgets(str, 5, stdin); //读取4个字符
    if(*str==10)
        stime = 1800;
    else
    {
        stime = atoi(str);
        while((clearInput = getchar()) != '\n' && clearInput != EOF); //在下次读取前清空缓冲区
    }
    
    printf("what's the time when you clock out?\n");
    printf("default 2000: ");
    fgets(str, 5, stdin); //读取4个字符
    if(*str==10)
        etime = 2000;
    else
    {
        etime = atoi(str);
        while((clearInput = getchar()) != '\n' && clearInput != EOF); //在下次读取前清空缓冲区
    }

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
        while((clearInput = getchar()) != '\n' && clearInput != EOF); //在下次读取前清空缓冲区
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
        result = doSearch(clkRecord[delnum-1].date);
        while( ((result+1) < totalRecords) && clkRecord[result+1].mark==(clkRecord[result].mark+1) )  //找到mark值最大的一条记录
            result++;
        for(int i = delnum; i < result; i++)
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
        while((clearInput = getchar()) != '\n' && clearInput != EOF); //在下次读取前清空缓冲区
    }

    if(modnum<1||modnum>totalRecords)
        return 0;
    
    printf("what's the time when you clock in?\n");
    printf("default 1800: ");
    fgets(str, 5, stdin); //读取1个字符
    if(*str==10)
        stime = 1800;
    else
    {
        stime = atoi(str);
        while((clearInput = getchar()) != '\n' && clearInput != EOF); //在下次读取前清空缓冲区
    }
    
    printf("what's the time when you clock out?\n");
    printf("default 2000: ");
    fgets(str, 5, stdin); //读取4个字符
    if(*str==10)
        etime = 2000;
    else
    {
        etime = atoi(str);
        while((clearInput = getchar()) != '\n' && clearInput != EOF); //在下次读取前清空缓冲区
    }
    
    changeRecord( modnum, 0, stime, etime);
    printf("\n");

    return 0;
}

static int doSearch(int searchDate)
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
    FILE *fp = fopen(filePath,"w");
    if(fp!=NULL)
    {
        fprintf(fp,"%2d%10s%4s%7s%7s%7s\n", totalRecords, "date", "m", "stime","etime","dur");   
        for(int i = 0; i< totalRecords; i++)
        {
            fprintf(fp,"%2d%10d%4d%7d%7d%7d\n",i+1,clkRecord[i].date,clkRecord[i].mark,clkRecord[i].startime,clkRecord[i].endtime,clkRecord[i].duration );
        }
    }
    fclose(fp);

    return 0;
}

static int parseArg(int argc, char **argv)
{
    int opt, Mflag=0, date=0, stime=0, etime=0;  //Mflag 是第一列的编号
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
                break;
            case 's':
                stime = atoi(optarg);
                break;
            case 'e':
                etime = atoi(optarg);
                break;
            case 'M':
                Mflag = atoi(optarg);
                break;
            case 'D':
                Del(atoi(optarg));
                writeToFile();
                return 0;
            case 'H':
                showHelp();
                break;
            case 'h':
                showHelp();
                break;
            case 'L':
                doList();
                break;
            case 'l':
                doList();
                break;
            case 'V':
                printf("overtime: version 0.2\n");
                break;
            case 'v':
                printf("overtime: version 0.2\n");
                break;
            default:
                return -1;
        }
    }
    if( (date+stime+etime) !=0) //至少有一个不为0
    {
        if( changeRecord(Mflag,date,stime,etime) == -1 )
            return -2;
    }

    return 0;  //返回0的话，就是正常解析选项
}

static int changeRecord(int Mflag, int date, int stime, int etime)
{
    int result;
    if(Mflag==0)  //增加记录
    {
        if(date==0)
        {
            if(tmp->tm_mday==1)
                return -1; //没有前一天
            else
                date = (tmp->tm_year+1900)*10000 + (tmp->tm_mon+1)*100 + tmp->tm_mday-1; //前一天
        }

        result = doSearch(date);
        if(result==-1)  //未找到记录，在最后添加
        {
            clkRecord[totalRecords].date = date;
            clkRecord[totalRecords].mark = 1;
            if(stime==0)
                clkRecord[totalRecords].startime = 1800;
            else
                clkRecord[totalRecords].startime = stime;
            if(etime==0)
                clkRecord[totalRecords].endtime = 2000;
            else
                clkRecord[totalRecords].endtime = etime;
            calDuration(totalRecords);
        }
        else  //找到记录，紧随其后添加
        {
            while( ((result+1) < totalRecords) && clkRecord[result+1].mark==(clkRecord[result].mark+1) )  //找到mark值最大的一条记录
                result++;
            for(int i=totalRecords-1; i> result+1; i--) //向后腾出空间
            {
                clkRecord[i] = clkRecord[i-1];
            }
            clkRecord[result+1].date = date;
            clkRecord[result+1].mark = clkRecord[result].mark + 1;
            if(stime==0)
                clkRecord[result+1].startime= 1800;
            else
                clkRecord[result+1].startime= stime;
            if(etime==0)
                clkRecord[result+1].endtime= 2000;
            else
                clkRecord[result+1].endtime= etime;
            calDuration(result+1);
        }
        totalRecords ++;
    }
    else if(Mflag > 0 && Mflag <= totalRecords)  //修改记录
    {
        Mflag --;
        if(stime==0)
            clkRecord[Mflag].startime= 1800;
        else
            clkRecord[Mflag].startime= stime;
        if(etime==0)
            clkRecord[Mflag].endtime= 2000;
        else
            clkRecord[Mflag].endtime= etime;
        calDuration(Mflag);
    }
    
    writeToFile();
    
    return 0;
}

static int showHelp()
{
    printf("usage: overtime [-hlv] [-d date] [-s stime] [-e etime] [-M number] [-D number]\n\n");
    printf("Options:\n\
  -h, --help           show help\n\
  -l, --list           show list\n\
  -v, --version        show version\n\
  -d date              specify the date to modify\n\
  -s stime             change stime\n\
  -e etime             change etime\n\
  -M number            modify record\n\
  -D number            Delete record\n\n");

    return 0;
}

static int calDuration(int i)
{
    int shour, smin, ehour, emin;

    shour = clkRecord[i].startime/100; 
    smin = clkRecord[i].startime%100; 
    ehour = clkRecord[i].endtime/100; 
    emin = clkRecord[i].endtime%100; 
    clkRecord[i].duration = (ehour-shour)*60+emin-smin;
}

static int sort()
{
    CLOCKINRECORD recordTmp;
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


