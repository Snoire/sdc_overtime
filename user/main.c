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
static int doSearch();
static int writeToFile();
static int parseArg();
static int showHelp();
static int changeEtime();



int main(int argc, char **argv)
{
	volatile int flag = 1;//退出的标志
	int num = 7;
    init();
    if(parseArg(argc,argv) != 0)
    {
        welcome();
        while(flag)
        {	
            num = 7; //如果不恢复初始值，随便输入一个字母将保持上次的结果
            printf("(overtime) ");
            scanf("%d",&num);   //如果不清空输入缓冲区，在这里输入字母，会一直死循环
            while((clearInput = getchar()) != '\n' && clearInput != EOF); 

            if(num<0||num>6)
                printf("ops!\n");
            else
            {
                switch(num)
                {
                    case 0:
                        printf("0.help 1.add 2.del 3.modify 4.list 5.search 6.exit\n");
                        break;
                    case 1:
                        doAdd(); break;
                    case 2:
                        doDelete(); break;
                    case 3:
                        doModify(); break;
                    case 4:
                        doList(); break;
                    case 5:
                        doSearch(); break;
                    case 6:
                        flag = 0;
                        break;
                    default:
                        printf("ops!\n");
                        break;
                } 
            }
        } 
        printf("\nThe end..\n\n");
    }
    return 0;
}

static int welcome()
{
    tmp = getCurrentTime();

    printf("Welcome to overtime!\n");
    printf("It is now at %d:%d on %s %d, %d, today is %s\n", tmp->tm_hour, tmp->tm_min, transMon(tmp->tm_mon+1), tmp->tm_mday, tmp->tm_year+1900, transWeek(tmp->tm_wday) );
    printf("Still has %d days besides today!\n", daysInaMonth( tmp->tm_year+1900, tmp->tm_mon+1 ) - (tmp->tm_mday) );

    printf("\nFor help, type \"0\".\n");

//    printf("Please input the time you got off work yesterday: \n");
    return 0;
}

static int init()
{
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
		fp = fopen(filePath,"w");
        totalRecords = daysInaMonth(tmp->tm_year+1900,tmp->tm_mon+1);
        for(int i = 0; i < totalRecords; i++)
        {
            clkRecord[i].date = (tmp->tm_year+1900)*10000 + (tmp->tm_mon+1)*100 + i+1;
            if(dayOfWeek(tmp->tm_year+1900,tmp->tm_mon+1,i+1) > 5 || dayOfWeek(tmp->tm_year+1900,tmp->tm_mon+1,i+1) < 1)
            {
                clkRecord[i].mark = 0;
                clkRecord[i].startime = 0;
            }
            else
            {
                clkRecord[i].mark = 1;
                clkRecord[i].startime = 1800;
            }
            clkRecord[i].endtime = 0;
            clkRecord[i].duration = 0;
        }
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
        printf("totalTime: %d minutes\n",totalTime);
	}

    return 0;
}

static int doAdd()
{
    int shour, smin, ehour, emin;

    printf("what's the date do you want to record?\n");
    scanf("%d", &clkRecord[totalRecords].date); //忘了 & 取址就会段错误
    while((clearInput = getchar()) != '\n' && clearInput != EOF);

    clkRecord[totalRecords].mark = 1;
    
    printf("what's the time when you clock in?\n");
    scanf("%d", &clkRecord[totalRecords].startime );
    while((clearInput = getchar()) != '\n' && clearInput != EOF);
    
    printf("what's the time when you clock out?\n");
    scanf("%d", &clkRecord[totalRecords].endtime );
    while((clearInput = getchar()) != '\n' && clearInput != EOF);

    shour = clkRecord[totalRecords].startime/100; 
    smin = clkRecord[totalRecords].startime%100; 
    ehour = clkRecord[totalRecords].endtime/100; 
    emin = clkRecord[totalRecords].endtime%100; 
    clkRecord[totalRecords].duration = (ehour-shour)*60+emin-smin;

    totalRecords++;
    writeToFile();

    return 0;
}

static int doDelete()
{
	doList();
	
	int delnum;
	printf("please input the num that you want to del:\n");
	scanf("%d",&delnum);
    while((clearInput = getchar()) != '\n' && clearInput != EOF); //在下次读取前清空缓冲区

	if(delnum<1||delnum>totalRecords)
		return 0;
	 
    if(delnum==totalRecords)
        totalRecords--;
    else
    {
        for(int i = delnum; i <totalRecords;i++)
        {
            clkRecord[i-1]=clkRecord[i];
        }
        totalRecords--;
    }
    writeToFile();

    return 0;
}

static int doModify()
{
    doList();

    int shour, smin, ehour, emin;
    int modnum;
    printf("please input the num that you what to modify:\n");
	scanf("%d",&modnum);
    while((clearInput = getchar()) != '\n' && clearInput != EOF); //在下次读取前清空缓冲区

	if(modnum<1||modnum>totalRecords)
		return 0;
    
    printf("what's the time when you clock in?\n");
    scanf("%d", &clkRecord[modnum-1].startime );
    while((clearInput = getchar()) != '\n' && clearInput != EOF);
    
    printf("what's the time when you clock out?\n");
    scanf("%d", &clkRecord[modnum-1].endtime );
    while((clearInput = getchar()) != '\n' && clearInput != EOF);

    shour = clkRecord[modnum-1].startime/100; 
    smin = clkRecord[modnum-1].startime%100; 
    ehour = clkRecord[modnum-1].endtime/100; 
    emin = clkRecord[modnum-1].endtime%100; 
    clkRecord[modnum-1].duration = (ehour-shour)*60+emin-smin;
    
    writeToFile(); 

    return 0;
}

static int doSearch()
{
    int searchDate, i;
    printf("please input the date that you want to search:\n");
    scanf("%d",&searchDate);
    while((clearInput = getchar()) != '\n' && clearInput != EOF); //在下次读取前清空缓冲区
    for(i=0; i< totalRecords; i++)
        if(searchDate==clkRecord[i].date)
        {
			printf("%2d%10d%4d%7d%7d%7d\n",i+1,clkRecord[i].date,clkRecord[i].mark,clkRecord[i].startime,clkRecord[i].endtime,clkRecord[i].duration);  //用 %s 输出 int 会发生段错误
            break;
        }
    if(i==totalRecords)
        printf("no record here.\n");

    return 0;
}

static int writeToFile()
{
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
    int opt;
    int option_index = 0;
    struct option long_options[]={
        {"help",no_argument, NULL, 'H'},
        {"list",no_argument, NULL, 'L'}
    };
    if(argc==1)
        return -1; //只有在正确解析选项才返回0
    while( (opt=getopt_long(argc, argv, "e:hl",long_options,&option_index)) != -1 ) //少加了一个括号..
    {
        switch(opt)
        {
            case 'e':
                changeEtime();
                break;
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
            default:
                return -1;
        }
    }
    return 0;
}

static int changeEtime()
{
}

static int showHelp()
{
    printf("usage: overtime [-h] [-e <etime>]\n\n");
    printf("Options:\n\
  -h          show help\n\
  -e <etime>  change etime\n\n");

    return 0;
}


