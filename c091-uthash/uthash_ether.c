#include <stdlib.h>
#include <stdio.h>
#include <netinet/ether.h>
#include "uthash.h"

#if 0
struct ether_addr {
    uint8_t ether_addr_octet[6];
}
#endif

typedef struct {
    struct ether_addr ea;
    /* ... other data ... */
    UT_hash_handle hh;
} record_t;

int main(int argc, char *argv[]) {
    record_t l, *p, *r, *tmp, *records = NULL;
    char *macstr = NULL;

    r = (record_t *)malloc(sizeof *r);
    macstr = "14:2E:5E:89:09:BE";
    ether_aton_r(macstr, &r->ea);

//    memset(r, 0, sizeof *r);
    HASH_ADD(hh, records, ea, sizeof(struct ether_addr), r);

    memset(&l, 0, sizeof(record_t));
    macstr = "14:2E:5E:89:09:BE";
    ether_aton_r(macstr, &l.ea);
    //HASH_FIND(hh, records, &l.ea, sizeof(struct ether_addr), p);
    records = NULL;
    HASH_FIND(hh, records, &l.ea, sizeof(struct ether_addr), p);

    //if (p) printf("found %c %d\n", p->key.a, p->key.b);
    if (p) printf("found \n");

    HASH_ITER(hh, records, p, tmp) {
      HASH_DEL(records, p);
      free(p);
    }
    return 0;
}
