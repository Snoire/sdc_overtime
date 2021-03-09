#include <stdio.h>
#include <string.h>

int main()
{
    char *filtertable = "DHCPfilterForwardnas1_0";
    printf("DHCPfilterForwardnas1_0\n");

    if (strstr(filtertable, "DHCPfilterForward"))
        printf("DHCPfilterForward OK!\n");

    if (strstr(filtertable, "HCPfilterForward"))
        printf("HCPfilterForward OK!\n");

    if (strstr(filtertable, "DHCPf_ilterForward"))
        printf("DHCPf_ilterForward OK!\n");

    return 0;
}
