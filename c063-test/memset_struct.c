#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct dut_info_t_ {
    unsigned int band;
    char bssid[18];
    char ssid[64];
    char mac[18];
} dut_info_t;

typedef struct dut_list_t {
    unsigned int length;
    dut_info_t duts[1];
} dut_list_t;

int main()
{
    dut_list_t *dutlist = NULL;

    dutlist = (dut_list_t *) malloc(sizeof(dut_list_t) + sizeof(dut_info_t));
    printf("sizeof(dut_list_t): %d\n", sizeof(dut_list_t));
    printf("sizeof(dut_info_t): %d\n", sizeof(dut_info_t));
    dutlist->duts[1].mac[17] = 'a';
    memset(dutlist, 0, sizeof(dut_list_t) + sizeof(dut_info_t));

    for (int i = 0; i < 18; i++) {
        printf("dutlist->duts[1].mac[%d]: %d\n", i, dutlist->duts[1].mac[i]);
    }

    free(dutlist);

    return 0;
}
