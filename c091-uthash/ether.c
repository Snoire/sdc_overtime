#include <stdio.h>
#include <netinet/ether.h>

int main()
{
    char *macstr = NULL;
    char buf[18] = "";
    struct ether_addr ea, *p;

    macstr = "14:2E:5E:89:09:BE";
    ether_aton_r(macstr, &ea);
    //utarray_push_back(maclist, &ea);
    printf("1. ea: %lu\n", *(unsigned long *) &ea);

    macstr = "14:2E:5E:89:09:BE";
    ether_aton_r(macstr, &ea);
    printf("%lu\n", *(unsigned long *) &ea);

    macstr = "D4:3B:04:BF:59:14";
    ether_aton_r(macstr, &ea);
    printf("%lu\n", *(unsigned long *) &ea);

    macstr = "4E:A8:71:09:E6:94";
    ether_aton_r(macstr, &ea);
    printf("%lu\n", *(unsigned long *) &ea);

    macstr = "5C:87:9C:F0:AD:DE";
    ether_aton_r(macstr, &ea);
    printf("%lu\n", *(unsigned long *) &ea);

    return 0;
}
