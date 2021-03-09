#include <stdio.h>
#include <string.h>

static int week2num(const char *week)
{
    if (strcmp(week, "MON") == 0)
        return 1;
    if (strcmp(week, "TUE") == 0)
        return 2;
    if (strcmp(week, "WED") == 0)
        return 3;
    if (strcmp(week, "THU") == 0)
        return 4;
    if (strcmp(week, "FRI") == 0)
        return 5;
    if (strcmp(week, "SAT") == 0)
        return 6;
    if (strcmp(week, "SUN") == 0)
        return 7;

    return 0;
}

int main()
{
    //char *weekstr = "MON,TUE,WED,THU,FRI,SAT,SUN,XXX";
    char *weekstr = "MON,TUE,WED";
    char *p = NULL;
    char buf[64] = "";
    char tmp[64] = "";
    char numstr[64] = "";

    for (int i = 0; i < 7; i++) {
        memset(buf, 0, sizeof(buf));

        if (*weekstr != 0) {
            if ((p = strchr(weekstr, ','))) {
                strncpy(buf, weekstr, strlen(weekstr) - strlen(p));
                printf("weekstr%d: %s\n", i, buf);

                sprintf(tmp, "%d,", week2num(buf));
                strcat(numstr, tmp);

                weekstr = p + 1;
            } else {
                printf("weekstr%d: %s\n", i, weekstr);

                sprintf(tmp, "%d", week2num(weekstr));
                strcat(numstr, tmp);

                break;
            }
        } else
            break;
    }

    printf("str: %s\n", numstr);

    return 0;
}
