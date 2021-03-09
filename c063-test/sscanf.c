#include <stdio.h>
#include <string.h>
#include <errno.h>

int main()
{
    int __attribute__((unused)) port = -1;
    char ver[32] = "";
    char __attribute__((unused)) str1[128] = "wl0: Oct 29 2020 18:05:42 version 17.10.99.1302 (r779368) P FWID 01-5292d28a";
    char __attribute__((unused)) str2[128] = "wl0: Nov  6 2020 14:23:20 version 17.10.99.1302 (r779368) P FWID 01-5292d28a";
    char __attribute__((unused)) str3[32] = "eth1.0";

#if 0
    sscanf(str1, "%*[^v]version %s", ver);  // 没法直接定义 version 的位置，用 strstr
#else
    sscanf(strstr(str2, "version"), "version%s", ver);
//    sscanf(NULL, "version%s", ver);
#endif
    printf("ver: |%s|\n", ver);
    if (sscanf(str3, "eth%d", &port) != 1) {  // 成功接收的参数个数不为1
        return -EINVAL;
    }
    printf("port: |%d|\n", port);
    printf("error: %s\n", (char *) NULL);

    return 0;
}
