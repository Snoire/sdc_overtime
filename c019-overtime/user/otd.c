#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <signal.h>
#include <errno.h>
#include <time.h>
#include <pwd.h>

#include "day_of_week.h"
#include "day_in_month.h"
#include "get_current_time.h"

#define COLOR_CYAN    "\x1b[36m"
#define COLOR_RESET   "\x1b[0m"
#define STIM          1800
#define ETIM          2000

#define QLEN 10

#define DATA_FILE_PATH   "/tmp/ot_%s_data_%d.txt"
#define SERV_PORT       2569
#define MAX_LEN_OF_ONE_LINE 40

char file_path[256] = "";

typedef struct {
    int date;
    int mark;
    int startime;
    int endtime;
    int duration;
} clockin_record_t;             //给结构体起一个别名

clockin_record_t record[60];
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
static int init();
static int do_list();
static int do_search(int);
static int search(int);
static int write_to_file();
static int change_record(int, int, short, short);
static int calculate_duration(int);
static int sort();
static int del_record(int);
static int validate_record(clockin_record_t *);
static void sighandler(int);
int ot_process(int mode, int date, int data);

/*
 * Create a server endpoint of a connection.
 * Returns fd if all OK, <0 on error.
 */
int serv_listen()
{
    int fd, err, rval;
//    struct sockaddr_un un;
    struct sockaddr_in ser_sockaddr;

    /* create a stream socket */
    if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        return (-1);

    /* fill in socket address structure */
    memset(&ser_sockaddr, 0, sizeof(ser_sockaddr)); //bzero ok
    ser_sockaddr.sin_family = AF_INET;
    ser_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    ser_sockaddr.sin_port = htons(SERV_PORT);

    /* bind the ser_sockaddr to the descriptor */
    if (bind(fd, (struct sockaddr *) &ser_sockaddr, sizeof(ser_sockaddr)) < 0) {
        rval = -2;
        goto errout;
    }

    if (listen(fd, QLEN) < 0) { /* tell kernel we're a server */
        rval = -3;
        goto errout;
    }

    return (fd);

errout:
    err = errno;                /*tmp store in case of close error */
    close(fd);
    errno = err;
    return (rval);
}

int serv_accept(int listenfd)
{
    int clifd, len;
    struct sockaddr_in cli_sockaddr;

    len = sizeof(cli_sockaddr);           /*watch out here */
    if ((clifd = accept(listenfd, (struct sockaddr *) &cli_sockaddr, (socklen_t *) &len)) < 0)
        return (-1);            /* often errno=EINTR, if signal caught */

    return (clifd);
}


int cfd;
int main(int argc, char **argv)
{
    int lfd, n;
    int buf[3] = {0};

    signal(SIGINT, sighandler);
    init();
    lfd = serv_listen();
    if (lfd < 0) {
        perror("error");
        exit(EXIT_FAILURE);
    }
    while (1) {
        cfd = serv_accept(lfd);

        while (1) {
r_again:
            n = read(cfd, &buf, sizeof(buf));

            if (n == -1) {
                if (errno == EINTR)
                    goto r_again;
            } else if (n == 0) {
                printf("the other side has been closed.\n\n");
                break;
            }

            printf("%d, %d, %d\n", buf[0], buf[1], buf[2]);
            ot_process(buf[0], buf[1], buf[2]);
        }
    }

    return 0;
}



void sighandler(int signum)
{
    printf("\nbye..\n\n");
    exit(1);
}



static int init()
{
    int year, mon, day, hour1, hour2, min1, min2;

    tmp = get_current_time();   //初始化的时候就要存储时间信息
    pre_date = ((tmp->tm_year + 1900) * 100 + tmp->tm_mon + 1) * 100;

#if 0
    char data_dir[7 + 32 + 6] = { 0 };
    strcat(data_dir, homevar);
    strcat(data_dir, "/.data");
    if (access(data_dir, F_OK) != 0)    //文件夹不存在
        mkdir(data_dir, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
#endif

    char *homevar = getenv("USER");

    sprintf(file_path, DATA_FILE_PATH, homevar,
            (tmp->tm_year+1900)*100 + tmp->tm_mon+1);

    FILE *fp = fopen(file_path, "r");

    if (fp != NULL) {
        fscanf(fp, "%2d", &total_records);
        fscanf(fp, "%*[^\n]\n");        //读第一行，但不用

        for (int i = 0; i < total_records; i++) {
            fscanf(fp, "%*2d%6d/%2d/%2d%4d  %2d:%2d  %2d:%2d%7d\n",
                   &year, &mon, &day, &record[i].mark, &hour1,
                   &min1, &hour2, &min2, &record[i].duration);
            record[i].date = year * 10000 + mon * 100 + day;
            record[i].startime = hour1 * 100 + min1;
            record[i].endtime = hour2 * 100 + min2;
        }

        fclose(fp);             //放在这里就正常了，本来在条件语句后面的，应该是关闭一个已经关闭的文件会发生错误
    } else {                    // if file does not exit, create and init it.
        write_to_file();
    }

    return 0;
}



static int do_list()
{
    int total_time = 0;
    char *buf = NULL;
    char line[MAX_LEN_OF_ONE_LINE * 3] = "";

    if (total_records == 0) {
        buf = malloc(MAX_LEN_OF_ONE_LINE);
        if (!buf)
            return -1;
        memset(buf, 0, MAX_LEN_OF_ONE_LINE);
        snprintf(buf, MAX_LEN_OF_ONE_LINE, "nothing..\n\n");
    } else {
        buf = malloc(MAX_LEN_OF_ONE_LINE * (total_records + 3));
        if (!buf)
            return -1;
        memset(buf, 0, MAX_LEN_OF_ONE_LINE * (total_records + 3));

        snprintf(buf, MAX_LEN_OF_ONE_LINE, "%11s   %7s%7s%7s\n", "Date", "stime", "etime", "dur");

        for (int i = 0; i < total_records; i++) {
            snprintf(line, sizeof(line), "%2d%6d/%.2d/%.2d  %.2d:%.2d  %.2d:%.2d%7d\n",
                    i + 1, record[i].date / 10000, record[i].date / 100 % 100,
                    record[i].date % 100, record[i].startime / 100, record[i].startime % 100,
                    record[i].endtime / 100, record[i].endtime % 100, record[i].duration);  //用 %s 输出 int 会发生段错误

            strncat(buf, line, MAX_LEN_OF_ONE_LINE * (total_records + 3) - 1);
            total_time += record[i].duration;
        }
        snprintf(line, sizeof(line), "\ntotal time: %d hours and %d minutes\n"
                "still needs: %d hours and %d minutes\n\n",
                total_time / 60, total_time % 60,
                total_time < 2400 ? (2400 - total_time) / 60 : 0,
                total_time < 2400 ? (2400 - total_time) % 60 : 0);
        strncat(buf, line, MAX_LEN_OF_ONE_LINE * (total_records + 3) - 1);
    }
    write(cfd, buf, MAX_LEN_OF_ONE_LINE * (total_records + 3));
    free(buf);

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
        while (((result + 1) < total_records) && record[result + 1].mark == (record[result].mark + 1))  //找到mark值最大的一条记录
            result++;
        for (int i = delnum - 1; i < result; i++)
            record[i + 1].mark--;

        for (int i = delnum; i < total_records; i++)
            record[i - 1] = record[i];
        total_records--;
    }
    printf("delnum: %d\n", delnum); /* debug */

    return 0;
}




static int search(int search_date)
{
    int i = 0;

    for (; i < total_records; i++)      //这里如果在第一个分号之前加个 i，会报 statement with no effect 警告
        if (search_date == record[i].date)
            return i;

    if (i == total_records)
        return -1;

    return -2;
}

static int do_search(int search_date)
{
    int index = 0;
    char *buf = NULL;
    char line[MAX_LEN_OF_ONE_LINE * 3] = "";

    index = search(search_date);
    if (index >= 0) {
        buf = malloc(MAX_LEN_OF_ONE_LINE * total_records);
        if (!buf)
            return -1;
        memset(buf, 0, MAX_LEN_OF_ONE_LINE * total_records);
        do {
            snprintf(line, sizeof(line), "%2d%6d/%.2d/%.2d%4d  %.2d:%.2d  %.2d:%.2d%7d\n",
                    index + 1, record[index].date / 10000, record[index].date / 100 % 100,
                    record[index].date % 100, record[index].mark, record[index].startime / 100,
                    record[index].startime % 100, record[index].endtime / 100,
                    record[index].endtime % 100, record[index].duration);  //用 %s 输出 int 会发生段错误

            strncat(buf, line, MAX_LEN_OF_ONE_LINE * total_records - 1);
            index++;
        } while (((index) < total_records) && record[index].mark == (record[index - 1].mark + 1));        //不能让它访问越界
        write(cfd, buf, MAX_LEN_OF_ONE_LINE * total_records);
        free(buf);
    } else if (index == -1) {
        snprintf(line, sizeof(line), "no record found in %d/%.2d/%.2d.\n", search_date / 10000, search_date / 100 % 100, search_date % 100);
        write(cfd, line, sizeof(line));
    }

    return 0;
}



static int write_to_file()
{
    sort();
    FILE *fp = fopen(file_path, "w+");

    if (fp != NULL) {
        fprintf(fp, "%2d%9s   %4s%7s%7s%7s\n", total_records, "Date", "m", "stime", "etime", "dur");

        for (int i = 0; i < total_records; i++) {
            fprintf(fp, "%2d%6d/%.2d/%.2d%4d  %.2d:%.2d  %.2d:%.2d%7d\n",
                    i + 1, record[i].date / 10000, record[i].date / 100 % 100, record[i].date % 100,
                    record[i].mark, record[i].startime / 100, record[i].startime % 100,
                    record[i].endtime / 100, record[i].endtime % 100, record[i].duration);
        }
        fclose(fp);
    } else
        printf("open file error!\n");

    return 0;
}





static int change_record(int number, int date, short stime, short etime)
{
    int result, dayofw = 0;

    if (stime == 0)
        stime = 1800;           //如果未指定这个参数，则默认为 1800
    else if (stime < 100)
        stime += 1800;          //如果指定的参数是两位数，说明省略了小时，则加上 1800

    if (etime == 0)
        etime = 2000;
    else if (etime < 100)
        etime += 2000;

    if (number == 0) {          //增加记录
#if 1
        if (date == 0) {
            dayofw = day_of_week((tmp->tm_year + 1900) * 10000 + (tmp->tm_mon + 1) * 100 + tmp->tm_mday - 1);   //前一天是周几?

            if (tmp->tm_mday == 1)      //今天是 1 号，也就是不能再往前了
                date = pre_date + tmp->tm_mday;
            else if (dayofw == 0)       //星期天
                date = pre_date + tmp->tm_mday - 3;     //前一个工作日
            else if (dayofw == 6)       //星期六
                date = pre_date + tmp->tm_mday - 2;     //前一个工作日
            else
                date = pre_date + tmp->tm_mday - 1;     //前一个工作日
        }
#else
        if (date == 0) {
            if (tmp->tm_mday == 1)
                date = pre_date + tmp->tm_mday;
            else
                date = pre_date + tmp->tm_mday - 1;     //前一天
        }
#endif
        result = search(date);
        total_records++;

        if (result == -1) {     //未找到记录，在最后添加
            record[total_records - 1].date = date;
            record[total_records - 1].mark = 1;
            record[total_records - 1].startime = stime;
            record[total_records - 1].endtime = etime;

            calculate_duration(total_records - 1);

            int ret = validate_record(&record[total_records - 1]);

            if (ret < 0) {
                printf("date format error! ret = %d\n", ret);
                total_records--;        //把最后一条排除在外，相当于删掉了
            }
        } else {                //找到记录，紧随其后添加
            while (((result + 1) < total_records - 1) && record[result + 1].mark == (record[result].mark + 1))  //找到mark值最大的一条记录
                result++;

            for (int i = total_records - 1; i > result + 1; i--) {      //向后腾出空间
                record[i] = record[i - 1];
            }

            record[result + 1].date = date;
            record[result + 1].mark = record[result].mark + 1;
            record[result + 1].startime = stime;
            record[result + 1].endtime = etime;

            calculate_duration(result + 1);

            if (validate_record(&record[result + 1]) < 0) {
                printf("date format error!\n");
                del_record(result + 2);
            }
        }
    } else if (number > 0 && number <= total_records) { //修改记录
        number--;

        record[total_records] = record[number]; //record[total_records] 这个是范围之外的，拿来做临时存储的地方，之后也不用删除
        record[total_records].date = date;
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




static int calculate_duration(int i)
{
    int shour, smin, ehour, emin, dur;

    shour = record[i].startime / 100;
    smin = record[i].startime % 100;
    ehour = record[i].endtime / 100;
    emin = record[i].endtime % 100;
    dur = (ehour - shour) * 60 + emin - smin;
    record[i].duration = (dur < 30) ? 0 : dur;

    return 0;
}



static int sort()
{
    clockin_record_t record_tmp;
    for (int i = 0; i < total_records - 1; i++) {
        for (int j = i + 1; j < total_records; j++) {
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



static int validate_record(clockin_record_t * record_tmp)
{
    if ((record_tmp->date % 100) > day_in_month(tmp->tm_year + 1900, tmp->tm_mon + 1) || (record_tmp->date % 100) < 1)
        return -1;              //日期超出范围
    else if (record_tmp->startime >= record_tmp->endtime        //开始时间居然比结束时间还晚?!
            || record_tmp->startime % 100 > 59 || record_tmp->startime % 100 < 0
            || record_tmp->startime / 100 > 23 || record_tmp->startime / 100 < 0
            || record_tmp->endtime % 100 > 59 || record_tmp->endtime % 100 < 0
            || record_tmp->endtime / 100 > 23 || record_tmp->endtime / 100 < 0)
        return -2;
    else {
        /* TODO */
    }

    return 0;
}

int ot_process(int mode, int date, int data)
{
    int index = 0;

    switch (mode) {
    case OT_MODE_SHOW:
        if (date == 0) {    /* show all records */
            do_list();
        } else {            /* show specified date */
            do_search(date);
        }
        return 0;
    case OT_MODE_GETVAL:
        if (date == 0) {    /* get total_records */
            write(cfd, &total_records, sizeof(total_records));
        } else {            /* get the index of specified date */
            index = search(date);
            write(cfd, &index, sizeof(index));
        }
        return 0;
    case OT_MODE_DEL:
        return del_record(data);
    default:
        return change_record(mode, date, data>>16, (short) data);
    }
}
