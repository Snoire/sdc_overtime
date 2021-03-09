/* get_arp_entry_ioctl.c */

/**url:
 * https://segmentfault.com/a/1190000005365739 
 *
 **usage:
 * $ arp -n
 * Address                  HWtype  HWaddress           Flags Mask            Iface
 * 172.17.63.253            ether   ee:ff:ff:ff:ff:ff   C                     eth0
 * $
 * $ ./get_arp_entry_ioctl eth0 172.17.63.253
 * MAC: ee:ff:ff:ff:ff:ff
 */


#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <net/if_arp.h>
#include <arpa/inet.h>

static void get_arp_entry(const char *, const char *);

int main(int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stderr,
        "Usage: %s [local interface name] [dst ip addres]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char ifname[IFNAMSIZ] = {'\0'};
    strncpy(ifname, argv[1], IFNAMSIZ-1);

    char ipaddr[INET_ADDRSTRLEN] = {'\0'};
    strncpy(ipaddr, argv[2], INET_ADDRSTRLEN);

    get_arp_entry(ifname, ipaddr);

    return 0;
}

static void get_arp_entry(const char *dev, const char *ip)
{
    int sfd, saved_errno, ret;
    unsigned char *mac;
    struct arpreq arp_req;
    struct sockaddr_in *sin;

    sin = (struct sockaddr_in *)&(arp_req.arp_pa);

    memset(&arp_req, 0, sizeof(arp_req));
    sin->sin_family = AF_INET;
    inet_pton(AF_INET, ip, &(sin->sin_addr));
    strncpy(arp_req.arp_dev, dev, IFNAMSIZ-1);

    sfd = socket(AF_INET, SOCK_DGRAM, 0);

    saved_errno = errno;
    ret = ioctl(sfd, SIOCGARP, &arp_req);
    if (ret < 0) {
        fprintf(stderr, "Get ARP entry failed : %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    errno = saved_errno;

    if (arp_req.arp_flags & ATF_COM) {
        mac = (unsigned char *)arp_req.arp_ha.sa_data;
        printf("MAC: %02x:%02x:%02x:%02x:%02x:%02x\n",
                mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    } else {
        printf("MAC: Not in the ARP cache.\n");
    }
}
