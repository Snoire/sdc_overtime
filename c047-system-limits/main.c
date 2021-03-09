#include <stdio.h>
#include <unistd.h>

int main()
{
    long lim;
    lim = sysconf(_SC_MQ_PRIO_MAX);
    printf("MQ_PRIO_MAX is %ld\n", lim);

    lim = pathconf("./", _PC_NAME_MAX);
    printf("NAME_MAX is %ld\n", lim);

    lim = sysconf(_SC_NGROUPS_MAX);
    printf("NGROUPS_MAX is %ld\n", lim);

    return 0;
}

