#include <stdio.h>
#include <string.h>


static char *transWeek(int w)
{
    char * pstr;
    switch(w){
        case 1:  pstr = "MON";   break;
        case 2:  pstr = "TUE";  break;
        case 3:  pstr = "WED";break;
        case 4:  pstr = "THU"; break;
        case 5:  pstr = "FRI";   break;
        case 6:  pstr = "SAT"; break;
        case 7:  pstr = "SUN";   break;
        default: pstr = NULL;
    }

    return pstr;
}

int main()
{
#if 0
    char numstr[] = "1,2,3,4,5,6";
    //char numstr[] = "1,2,3,4,5,6,7,8,9";
    //char numstr[] = "1,2";
    int num[7] = {0};
    char *str[7];
    char weekstr[128] = "";

    sscanf(numstr, "%d,%d,%d,%d,%d,%d,%d",
            &num[0], &num[1], &num[2], &num[3], &num[4], &num[5], &num[6]);

    if (num[0] !=0)
        printf("%d", num[0]);

    for (int i = 1; i < 7; i++) {
        if (num[i] !=0)
            printf(",%d", num[i]);
    }

    printf("\n");

    char buf[32] = "";
    if (num[0] !=0)
        sprintf(weekstr, "%s", transWeek(num[0]));

    for (int i = 1; i < 7; i++) {
        if (num[i] != 0) {
            sprintf(buf, ",%s", transWeek(num[i]));
            strcat(weekstr, buf);
        }
    }
    printf("%s\n", weekstr);
#else
    char tmpmac[32] = "D6:3B:04:bf:59:14";
    char destmac[16] = "";
    int i = 0, j = 0;

    for (; i<17; i++) {
        if (tmpmac[i] == ':')
            continue;
//        if (tmpmac[i] >= 'A' && tmpmac[i] <= 'Z')
//            tmpmac[i] = tmpmac[i] +32;
        destmac[j] = tmpmac[i];
        j++;
    }
    destmac[j] = 0;
    printf("tmp: %s\n", tmpmac);
    printf("mac: %s\n", destmac);

#endif

    return 0;
}

