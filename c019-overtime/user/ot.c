#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <pwd.h>
#include <signal.h>

#include "day_of_week.h"
#include "day_in_month.h"
#include "get_current_time.h"

#define COLOR_CYAN    "\x1b[36m"
#define COLOR_RESET   "\x1b[0m"
#define STIM          1800
#define ETIM          2000

#define SERV_PORT       2569

int total_records = 0;          //总记录数

struct tm *tmp;                 //保存时间信息
int pre_date;

//enum mode_e {
typedef enum {
    OT_MODE_SHOW = -3,
    OT_MODE_GETVAL,
    OT_MODE_DEL,
    OT_MODE_INS,
    OT_MODE_UPDATE
} ot_mode_t;


//声明函数
static int welcome();
static int init();
static int do_add();
static int do_delete();
static int do_modify();
static int do_search();
static int parse_args(int, char **);
static int show_help();
static void sighandler(int);
int ot_process(int mode, int date, int data);

char buf[2440] = "";
/*
 * Create a client endpoint and connect to a server.
 * Returns fd if all OK, <0 on error.
 */
int cli_conn(char *server_ip)
{
    int fd, err, rval;
    struct sockaddr_in ser_sockaddr;

    /* create a socket */
    if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        return (-1);

    /* fill socket address structure with server's address */
    memset(&ser_sockaddr, 0, sizeof(ser_sockaddr));
    ser_sockaddr.sin_family = AF_INET;
    inet_pton(AF_INET, server_ip, &ser_sockaddr.sin_addr);
    ser_sockaddr.sin_port = htons(SERV_PORT);

    if (connect(fd, (struct sockaddr *) &ser_sockaddr, sizeof(ser_sockaddr)) < 0) {
        rval = -4;
        goto errout;
    }

    return (fd);

errout:
    err = errno;
    close(fd);
    errno = err;
    return (rval);
}

int fd;
void interactive_loop()
{
    int ret = 0;
    volatile int loop = 1;      //继续循环的标志

    welcome();

    while (loop) {
        ret = 0;            //如果不恢复初始值，随便输入一个字母将保持上次的结果

        printf(COLOR_CYAN "(ot) " COLOR_RESET);
        fflush(stdout);
        ret = getchar();
        if (ret == 10)      //遇到换行符
            ret = 0;
        else if (ret == -1) //遇到 Ctrl+d
            ret = 'q';
        else {
            scanf("%*[^\n]");       //其它情况，输入缓冲区里都至少有一个 '\n'，\n 之前可能有其他字符
            scanf("%*c");           //所以要清空缓冲区
        }

        switch (ret) {
        case 'h':
            printf("a: add     h: help     l: list     q: quit\n"
                   "d: delete  m: modify   s: search\n\n");
            break;
        case 'a':
            do_add();
            break;
        case 'd':
            do_delete();
            break;
        case 'm':
            do_modify();
            break;
        case 'l':
            ot_process(OT_MODE_SHOW, 0, 0);
            read(fd, buf, sizeof(buf));
            printf(buf);
            break;
        case 's':
            do_search();
            break;
        case 'q':
            loop = 0;
            break;
        case 0:
            break;
        default:
            printf("invalid option.\n");
        }                   /* end of switch ret */
    }                       /* end of while loop */
    printf("^D\nbye..\n\n");
}


int main(int argc, char **argv)
{
    int ret = 0;

    signal(SIGINT, sighandler);
    init();
    fd = cli_conn(argv[1]);
    if (fd < 0) {
        fprintf(stderr, "failed to connect to server\n");
        return -1;
    }

    argc--;
    argv++;

    if (argc == 1)                  //进入交互界面
        interactive_loop();
    else
        ret = parse_args(argc, argv);

    if (ret < 0)
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
            day_in_month(tmp->tm_year + 1900, tmp->tm_mon + 1) - (tmp->tm_mday));

    printf("\nFor help, type \"" "\x1b[33m" "help"
            "\x1b[0m" "\" or \"" "\x1b[33m" "h" "\x1b[0m" "\".\n");

    return 0;
}


static int init()
{
    tmp = get_current_time();   //初始化的时候就要存储时间信息
    pre_date = ((tmp->tm_year + 1900) * 100 + tmp->tm_mon + 1) * 100;

    return 0;
}




static int readtime(int flag)
{
    int ret = 0, time;
    char str[5] = "";           //最多能放 4 个字符

    ret = scanf("%4[0-9]", str);

    if (ret == 1) {
        if (strlen(str) < 3)    //一或两个数字
            time = flag + atoi(str);
        else                    //三或四个数字
            time = atoi(str);
    } else if (ret == 0)        //遇到 '\n' 或非数字
        time = flag;
    else                        //遇到 Ctrl+D
        return -1;

    scanf("%*[^\n]");
    scanf("%*c");

    return time;
}



static int readindex()
{
    int index, ret;
    char str[3] = { 0 };

    ot_process(OT_MODE_GETVAL, 0, 0);
    read(fd, &total_records, sizeof(total_records));

    ret = scanf("%2[0-9]", str);
    if (ret == 1)               //一或两个数字
        index = atoi(str);
    else if (ret == 0)          // '\n' 或者没有输入数字
        index = total_records;
    else                        // Ctrl+D
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
    char str[3] = "";           //最多能放 2 个字符

    /* default yesterday */
    dayofw = day_of_week((tmp->tm_year + 1900) * 10000 + (tmp->tm_mon + 1) * 100 + tmp->tm_mday - 1);   //前一天是周几?

    if (tmp->tm_mday == 1)
        date = pre_date + tmp->tm_mday;
    else if (dayofw == 0)       //星期天
        date = pre_date + tmp->tm_mday - 3;     //前一个工作日
    else if (dayofw == 6)       //星期六
        date = pre_date + tmp->tm_mday - 2;     //前一个工作日
    else
        date = pre_date + tmp->tm_mday - 1;     //前一个工作日

    printf("what's the day do you want to record?\n");
    printf("e.g. 1, default %d: ", date % 100);

    ret = scanf("%2[0-9]", str);
    if (ret == 1)
        date = pre_date + atoi(str);
    else if (ret == 0) {        // '\n' 或者没有输入数字
        /* pass */
    } else {                    // Ctrl+D
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

    ot_process(OT_MODE_INS, date, (stime << 16) + etime);
    printf("\n");

    return 0;
}



static int do_delete()
{
    int delnum;

    printf("please input the num that you want to del:\n");
    printf("default the last one: ");

    if ((delnum = readindex()) == -1) {
        printf("\n");
        return -1;
    }

    ot_process(OT_MODE_DEL, 0, delnum);
    printf("\n");

    return 0;
}



static int do_modify()
{
    int stime, etime, modnum;
//    ot_process(OT_MODE_SHOW, 0, 0);

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

    ot_process(modnum, 0, (stime << 16) + etime);
    printf("\n");

    return 0;
}



static int do_search()
{
    int value = 0, search_date = 0;
    printf("which day do you want to search: ");

    for (int i = 0; i < 2; i++) {
        value = getchar();

        if (i == 0 && value == '\n') {  //用户输入 \n
            if (tmp->tm_mday == 1)
                search_date = pre_date + tmp->tm_mday;
            else
                search_date = pre_date + tmp->tm_mday - 1;      //前一天
            break;
        } else if (i == 1 && value == '\n') {   //用户输入一个数字加换行
            search_date += pre_date;
            break;
        }

        search_date = search_date * 10 + value - 48;

        if (i == 1) {           //用户输入两个数字
            search_date += pre_date;
            scanf("%*[^\n]");
            scanf("%*c");       //清空缓冲区
        }
    }

    ot_process(OT_MODE_SHOW, search_date, 0);
    read(fd, buf, sizeof(buf));
    printf(buf);

    return 0;
}





/**
 *  Usage:
 *  overtime batch << EOF
 *  1 1855
 *  2 1300, 2000
 *  3 2005
 *  EOF
 */

static void ot_batch()
{
    int number = 0, ret;
    int date, stime, etime;

    while (!feof(stdin)) {
        if ((ret = scanf("%d %d, %d\n", &date, &stime, &etime)) == 2) {
            etime = stime;
            stime = 1800;
            scanf("\n");           //吃掉换行符

            /* 为什么这么写如果没加 break 最后会多一次循环？
             * 虽然也把最后的换行符取出来了，但好像没有设置 EOF
             * 总感觉 feof 函数不靠谱呀 */
            /* scanf("%*c"); */
        }

        if (ret == 2 || ret == 3) {
            ot_process(number, pre_date + date, (stime << 16) + etime);
        } else {
            break;
        }
    }
}



static int parse_args(int argc, char **argv)
{
    int opt, number = 0, date = 0, stime = 0, etime = 0;        //number 是第一列的编号
    int option_index = 0;
    struct option long_options[] = {
        { "help", no_argument, NULL, 'H' },
        { "version", no_argument, NULL, 'V' },
        { "list", no_argument, NULL, 'L' }
    };

    if (argc == 1)                  //进入交互界面
        return 1;

    while ((opt = getopt_long(argc, argv, "d:s:e:M:D:hlv", long_options, &option_index)) != -1) {
        switch (opt) {
        case 'd':
            date = atoi(optarg);    //这里应该判断一下
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
            ot_process(OT_MODE_DEL, 0, atoi(optarg));
            return 0;
        case 'H':
        case 'h':
            show_help();
            return 0;
        case 'L':
        case 'l':
            ot_process(OT_MODE_SHOW, 0, 0);
            read(fd, buf, sizeof(buf));
            printf(buf);
            break;
        case 'V':
        case 'v':
            printf("overtime: version 2.1.0\n");
            break;
        default:
            return -1;
        }
    }

    if ((date + stime + etime) != 0) {  //至少有一个不为0
        if (ot_process(number, date, (stime << 16) + etime) == -1)
            return -2;
    }

    if (optind > 1)
        argv[optind - 1] = argv[0];
    argv += optind - 1;
    argc -= optind - 1;

    if (argc > 1) {
        if (!strcasecmp(argv[1], "batch"))
            ot_batch();
        else
            show_help();
    }

    return 0;                   //返回0的话，就是正常解析选项
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


int ot_process(int mode, int date, int data)
{
    int buf[3];
    buf[0] = mode;
    buf[1] = date;
    buf[2] = data;
    write(fd, buf, sizeof(buf));

    return 0;
}
