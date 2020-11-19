#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <signal.h>

#include "day_of_week.h"
#include "day_in_month.h"
#include "get_current_time.h"

#define COLOR_CYAN    "\x1b[36m"
#define COLOR_RESET   "\x1b[0m"
#define STIM          1800
#define ETIM          2000

typedef struct {
    int date;
    int mark;
    int startime;
    int endtime;
    int duration;
} clockin_record_t;                //给结构体起一个别名

clockin_record_t record[60];
int total_records = 0;           //总记录数

char file_path[70] = "";
//char file_path[7+32+18]= {0};

struct tm *tmp;                 //保存时间信息
int pre_date;


//声明函数
static int welcome();
static int init();
static int do_list();
static int do_add();
static int do_delete();
static int do_modify();
static int do_search();
static int search(int);
static int write_to_file();
static int parse_args(int, char **);
static int show_help();
static int change_record(int, int, int, int);
static int calculate_duration(int);
static int sort();
static int del_record(int);
static int validate_record(clockin_record_t *);
static void sighandler(int);



int main(int argc, char **argv)
{
    int ret = 0;
    int ret_parse_args = 0;
    volatile int flag = 1;      //继续循环的标志

    signal(SIGINT, sighandler);

    init();
    if ((ret_parse_args = parse_args(argc, argv)) == 1) {
        welcome();
        while (flag) {
            ret = 0;            //如果不恢复初始值，随便输入一个字母将保持上次的结果

            printf(COLOR_CYAN "(ot) " COLOR_RESET);
            fflush(stdout);
            ret = getchar();
            if (ret == 10)      //遇到换行符
                ret = 0;
            else if (ret == -1) //遇到 Ctrl+d
                ret = 'q';
            else {
                scanf("%*[^\n]"); //其它情况，输入缓冲区里都至少有一个 '\n'，\n 之前可能有其他字符
                scanf("%*c");     //所以要清空缓冲区
            }

            switch (ret) {
            case 'h':
                printf("a: add     h: help     l: list     q: quit\n"
                       "d: delete  m: modify   s: search\n\n");
                break;
            case 'a':
                do_add(); break;
            case 'd':
                do_delete(); break;
            case 'm':
                do_modify(); break;
            case 'l':
                do_list(); break;
            case 's':
                do_search(); break;
            case 'q':
                flag = 0; break;
            case 0:
                break;
            default:
                printf("invalid option.\n");
            }                   //switch end..
        }                       //while end
        printf("^D\nbye..\n\n");
    }
    if (ret_parse_args == -1)
        show_help();
    return 0;
}



void sighandler(int signum)
{
    printf("\nbye..\n\n");
    exit(1);
}



static int welcome()
{
    struct passwd *pwd;
    uid_t uid;
    uid = getuid();
    pwd = getpwuid(uid);
    printf("Hi, %s, Welcome to overtime!\n", pwd->pw_name);

    printf("It is now at " "\x1b[4m" "%d:%.2d" "\033[0m" " on %s %d, %d, today is %s\n",
            tmp->tm_hour, tmp->tm_min, trans_mon(tmp->tm_mon+1),
            tmp->tm_mday, tmp->tm_year+1900, trans_week(tmp->tm_wday));  // %.2d 确保它是两位数，不足补0
    printf("Still has " "%d" " days besides today!\n",
            day_in_month(tmp->tm_year+1900, tmp->tm_mon+1) - (tmp->tm_mday));

    printf("\nFor help, type \"" "\x1b[33m" "help"
           "\x1b[0m" "\" or \"" "\x1b[33m" "h" "\x1b[0m" "\".\n");

    return 0;
}



static int init()
{
    int year, mon, day, hour1, hour2, min1, min2;
    char data_dir[7+32+6] = {0};

    tmp = get_current_time();     //初始化的时候就要存储时间信息
    pre_date = ((tmp->tm_year+1900)*100 + tmp->tm_mon+1) * 100;

    char *homevar = getenv("HOME");
    strcat(data_dir, homevar);
    strcat(data_dir, "/.data");

    sprintf(file_path, "%s/.data/record_%d.data", homevar,
            (tmp->tm_year+1900)*100 + tmp->tm_mon+1);

    if (access(data_dir, F_OK) != 0)     //文件夹不存在
        mkdir(data_dir, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

    FILE *fp = fopen(file_path, "r");

    if (fp != NULL) {
        fscanf(fp, "%2d", &total_records);
        fscanf(fp, "%*[^\n]\n");        //读第一行，但不用

        for (int i = 0; i < total_records; i++) {
            fscanf(fp, "%*2d%6d/%2d/%2d%4d  %2d:%2d  %2d:%2d%7d\n",
                   &year, &mon, &day, &record[i].mark, &hour1,
                   &min1, &hour2, &min2, &record[i].duration);
            record[i].date = year*10000 + mon*100 + day;
            record[i].startime = hour1*100 + min1;
            record[i].endtime = hour2*100 + min2;
        }
        fclose(fp);             //放在这里就正常了，本来在条件语句后面的，应该是关闭一个已经关闭的文件会发生错误
    } else {                    // if file does not exit, create and init it.
        write_to_file();
    }
    fp = NULL;

    return 0;
}



static int do_list()
{
    int total_time = 0;
    if (total_records == 0) {
        printf("nothing..\n\n");
    } else {
        printf("%11s   %7s%7s%7s\n", "Date", "stime", "etime", "dur");
        for (int i = 0; i < total_records; i++) {
            printf("%2d%6d/%.2d/%.2d  %.2d:%.2d  %.2d:%.2d%7d\n",
                   i+1, record[i].date/10000, record[i].date/100%100,
                   record[i].date%100, record[i].startime/100, record[i].startime%100,
                   record[i].endtime/100, record[i].endtime%100, record[i].duration);  //用 %s 输出 int 会发生段错误
            total_time += record[i].duration;
        }
        printf("\n");
        printf("total time: %d hours and %d minutes\n", total_time/60, total_time%60);
        printf("still needs: %d hours and %d minutes\n\n",
               total_time<2400 ? (2400-total_time)/60 : 0,
               total_time<2400 ? (2400-total_time)%60 : 0);
    }

    return 0;
}



static int readtime(int flag)
{
    int ret = 0, time;
    char str[5] = "";                //最多能放 4 个字符

    ret = scanf("%4[0-9]", str);
    if (ret == 1) {
        if (strlen(str) < 3)           //一或两个数字
            time = flag + atoi(str);
        else                           //三或四个数字
            time = atoi(str);
    } else if (ret == 0)               //遇到 '\n' 或非数字
        time = flag;
    else                               //遇到 Ctrl+D
        return -1;

    scanf("%*[^\n]");
    scanf("%*c");

    return time;
}



static int readindex()
{
    int index, ret;
    char str[3] = {0};

    ret = scanf("%2[0-9]", str);
    if (ret == 1)                                                  //一或两个数字
        index = atoi(str);
    else if (ret == 0)                                             // '\n' 或者没有输入数字
        index = total_records;
    else                                                           // Ctrl+D
        return -1;

    scanf("%*[^\n]");
    scanf("%*c");

    return index;
}



static int do_add()
{
    int ret = 0;
    int date = 0, stime, etime;
    int dayofw = 0;
    char str[3] = "";                //最多能放 2 个字符

    /* default yesterday */
    dayofw = day_of_week( (tmp->tm_year+1900)*10000+(tmp->tm_mon+1)*100+tmp->tm_mday-1 ); //前一天是周几?
    if (tmp->tm_mday == 1)
        date = pre_date + tmp->tm_mday;
    else if (dayofw == 0)       //星期天
        date = pre_date + tmp->tm_mday - 3; //前一个工作日
    else if (dayofw == 6)       //星期六
        date = pre_date + tmp->tm_mday - 2; //前一个工作日
    else
        date = pre_date + tmp->tm_mday - 1; //前一个工作日

    printf("what's the day do you want to record?\n");
    printf("e.g. 1, default %d: ", date % 100);

    ret = scanf("%2[0-9]", str);
    if (ret == 1)
        date = pre_date + atoi(str);
    else if (ret == 0) {                                             // '\n' 或者没有输入数字
        /* pass */
    } else {                                                         // Ctrl+D
        printf("\n");
        return -1;
    }

    scanf("%*[^\n]");
    scanf("%*c");

    printf("\nwhat's the time when you clock in?\n");
    printf("e.g. 2, 02 or 1802, default 18:00: ");
    if ((stime = readtime(STIM)) == -1) {
        printf("\n");
        return -1;
    }

    printf("\nwhat's the time when you clock out?\n");
    printf("e.g. 4, 04 or 2004, default 20:00: ");
    if ((etime = readtime(ETIM)) == -1) {
        printf("\n");
        return -1;
    }

    change_record(0, date, stime, etime);
    printf("\n");

    return 0;
}



static int do_delete()
{
    int delnum;

    do_list();

    printf("please input the num that you want to del:\n");
    printf("default the last one: ");

    if ((delnum = readindex()) == -1) {
        printf("\n");
        return -1;
    }

    del_record(delnum);
    write_to_file();
    printf("\n");

    return 0;
}



static int del_record(int delnum)
{
    int result = 0;
    if (delnum < 1 || delnum > total_records)
        return 0;

    if (delnum == total_records)
        total_records--;
    else {
        result = delnum - 1;    //要删除的记录的下标（从0开始）
        while ( ((result+1) < total_records) && record[result+1].mark==(record[result].mark+1) )  //找到mark值最大的一条记录
            result++;
        for (int i = delnum - 1; i < result; i++)
            record[i+1].mark --;

        for (int i = delnum; i < total_records; i++)
            record[i-1] = record[i];
        total_records--;
    }
    return 0;
}



static int do_modify()
{
    int stime, etime, modnum;
    do_list();

    printf("please input the num that you what to modify:\n");
    printf("default the last one: ");

    if ((modnum = readindex()) == -1) {
        printf("\n");
        return -1;
    }

    if (modnum < 1 || modnum > total_records)
        return 0;

    printf("what's the time when you clock in?\n");
    printf("e.g. 2, 02 or 1802, default 18:00: ");
    if ((stime = readtime(STIM)) == -1) {
        printf("\n");
        return -1;
    }

    printf("what's the time when you clock out?\n");
    printf("e.g. 4, 04 or 2004, default 20:00: ");
    if ((etime = readtime(ETIM)) == -1) {
        printf("\n");
        return -1;
    }

    change_record(modnum, 0, stime, etime);
    printf("\n");

    return 0;
}



static int do_search()
{
    int value = 0, search_date = 0, ret_num;
    printf("which day do you want to search: ");

    for (int i=0; i<2; i++) {
        value = getchar();
        if (i==0 && value == '\n') {                      //用户输入 \n
            if (tmp->tm_mday == 1)
                search_date = pre_date + tmp->tm_mday;
            else
                search_date = pre_date + tmp->tm_mday - 1; //前一天
            break;
        } else if (i==1 && value == '\n') {               //用户输入一个数字加换行
            search_date += pre_date;
            break;
        }

        search_date = search_date*10 + value- 48;
        if (i==1) {                     //用户输入两个数字
            search_date += pre_date;
            scanf("%*[^\n]");
            scanf("%*c");               //清空缓冲区
        }
    }

    ret_num = search(search_date);
    if (ret_num >= 0) {
        do {
            printf("%2d%6d/%.2d/%.2d%4d  %.2d:%.2d  %.2d:%.2d%7d\n",
                   ret_num+1, record[ret_num].date/10000, record[ret_num].date/100%100,
                   record[ret_num].date%100, record[ret_num].mark, record[ret_num].startime/100,
                   record[ret_num].startime%100, record[ret_num].endtime/100,
                   record[ret_num].endtime%100, record[ret_num].duration);  //用 %s 输出 int 会发生段错误
            ret_num++;

        } while ( ((ret_num) < total_records) && record[ret_num].mark==(record[ret_num-1].mark+1) );  //不能让它访问越界
    } else if (ret_num == -1)
        printf("no record found in %d/%.2d/%.2d.\n",search_date/10000,search_date/100%100,search_date%100);

    return 0;
}



static int search(int search_date)
{
    int i = 0;
    for (; i < total_records; i++)     //这里如果在第一个分号之前加个 i，会报 statement with no effect 警告
        if (search_date == record[i].date)
            return i;
    if (i == total_records)
        return -1;

    return -2;
}



static int write_to_file()
{
    sort();
    FILE *fp = fopen(file_path,"w+");
    if (fp != NULL) {
        fprintf(fp, "%2d%9s   %4s%7s%7s%7s\n",
                total_records, "Date", "m", "stime", "etime", "dur");   
        for (int i = 0; i< total_records; i++) {
            fprintf(fp, "%2d%6d/%.2d/%.2d%4d  %.2d:%.2d  %.2d:%.2d%7d\n",
                    i+1,record[i].date/10000, record[i].date/100%100, record[i].date%100,
                    record[i].mark, record[i].startime/100, record[i].startime%100,
                    record[i].endtime/100, record[i].endtime%100, record[i].duration);
        }
        fclose(fp);
    } else
        printf("open file error!\n");

    return 0;
}



static int parse_args(int argc, char **argv)
{
    int opt, number = 0, date = 0, stime = 0, etime = 0;  //number 是第一列的编号
    int option_index = 0;
    struct option long_options[] = {
        { "help", no_argument, NULL, 'H' },
        { "version", no_argument, NULL, 'V' },
        { "list", no_argument, NULL, 'L' }
    };
    if (argc == 1)
        return 1;                 //进入主循环
    while ((opt = getopt_long(argc, argv, "d:s:e:M:D:hlv", long_options, &option_index)) != -1) { //少加了一个括号..
        switch (opt) {
        case 'd':
            date = atoi(optarg);  //这里应该判断一下
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
            del_record(atoi(optarg));
            write_to_file();
            return 0;
        case 'H':
        case 'h':
            show_help();
            break;
        case 'L':
        case 'l':
            do_list();
            break;
        case 'V':
        case 'v':
            printf("overtime: version 1.1.5\n");
            break;
        default:
            return -1;
        }
    }
    if ((date+stime+etime) !=0) { //至少有一个不为0
        if (change_record(number,date,stime,etime) == -1)
            return -2;
    }

    return 0;                     //返回0的话，就是正常解析选项
}



static int change_record(int number, int date, int stime, int etime)
{
    int result, dayofw = 0;

    if (stime == 0)
        stime = 1800;             //如果未指定这个参数，则默认为 1800
    else if (stime < 100)
        stime += 1800;            //如果指定的参数是两位数，说明省略了小时，则加上 1800

    if (etime == 0)
        etime = 2000;
    else if (etime < 100)
        etime += 2000;

    if (number == 0) {            //增加记录
#if 1
        if (date == 0) {
            dayofw = day_of_week( (tmp->tm_year+1900)*10000+(tmp->tm_mon+1)*100+tmp->tm_mday-1 ); //前一天是周几?
            if (tmp->tm_mday == 1)       //今天是 1 号，也就是不能再往前了
                date = pre_date + tmp->tm_mday;
            else if (dayofw == 0)        //星期天
                date = pre_date + tmp->tm_mday - 3;   //前一个工作日
            else if (dayofw == 6)        //星期六
                date = pre_date + tmp->tm_mday - 2;   //前一个工作日
            else
                date = pre_date + tmp->tm_mday - 1;   //前一个工作日
        }
#else
        if (date == 0) {
            if (tmp->tm_mday == 1)
                date = pre_date + tmp->tm_mday;
            else
                date = pre_date + tmp->tm_mday - 1;   //前一天
        }
#endif
        result = search(date);
        total_records ++;

        if (result == -1) {              //未找到记录，在最后添加
            record[total_records-1].date = date;
            record[total_records-1].mark = 1;
            record[total_records-1].startime = stime;
            record[total_records-1].endtime = etime;
            calculate_duration(total_records-1);

            int ret = validate_record(&record[total_records-1]);
            if (ret < 0) {
                printf("date format error! ret = %d\n", ret);
                total_records--;          //把最后一条排除在外，相当于删掉了
            }
        } else {                         //找到记录，紧随其后添加
            while (((result+1) < total_records-1) &&
                   record[result+1].mark==(record[result].mark+1))  //找到mark值最大的一条记录
                result++;

            for (int i=total_records-1; i> result+1; i--) {                //向后腾出空间
                record[i] = record[i-1];
            }
            record[result+1].date = date;
            record[result+1].mark = record[result].mark + 1;
            record[result+1].startime= stime;
            record[result+1].endtime= etime;
            calculate_duration(result+1);

            if (validate_record(&record[result+1]) < 0) {
                printf("date format error!\n");
                del_record(result+2);
            }
        }
    } else if (number > 0 && number <= total_records) {    //修改记录
        number --;

        record[total_records] = record[number];      //record[total_records] 这个是范围之外的，拿来做临时存储的地方，之后也不用删除
        record[total_records].startime = stime;
        record[total_records].endtime = etime;

        if (validate_record(&record[total_records]) >= 0) {
            record[number] = record[total_records];
            calculate_duration(number);
        } else
            printf("date format error!\n");
    }

    write_to_file();

    return 0;
}



static int show_help()
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



static int calculate_duration(int i)
{
    int shour, smin, ehour, emin, dur;

    shour = record[i].startime / 100;
    smin = record[i].startime % 100;
    ehour = record[i].endtime / 100;
    emin = record[i].endtime % 100;
    dur = (ehour-shour)*60 + emin - smin;
    record[i].duration = (dur < 30) ? 0 : dur;

    return 0;
}



static int sort()
{
    clockin_record_t record_tmp;
    for (int i=0; i< total_records-1; i++) {
        for (int j=i+1; j< total_records; j++) {
            if (record[j].date < record[i].date
                || (record[j].date == record[i].date
                    && record[j].mark < record[i].mark)) {
                record_tmp = record[i];
                record[i] = record[j];
                record[j] = record_tmp;
            }
        }
    }

    return 0;
}



static int validate_record(clockin_record_t * record_tmp )
{
    if ( (record_tmp->date%100) > day_in_month( tmp->tm_year+1900, tmp->tm_mon+1 ) || (record_tmp->date%100) < 1 )
        return -1;              //日期超出范围
    else if (record_tmp->startime >= record_tmp->endtime    //开始时间居然比结束时间还晚?!
             || record_tmp->startime%100 > 59 || record_tmp->startime%100 < 0
             || record_tmp->startime/100 > 23 || record_tmp->startime/100 < 0
             || record_tmp->endtime%100 > 59 || record_tmp->endtime%100 < 0
             || record_tmp->endtime/100 > 23 || record_tmp->endtime/100 < 0)
        return -2;
    else {

    }

    return 0;
}




