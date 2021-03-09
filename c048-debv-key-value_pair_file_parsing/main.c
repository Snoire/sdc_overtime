#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/utsname.h>

#define OSRELEASE "/usr/lib/os-release"
#define DEBVERSION "/etc/debian_version"

/*
 * Function: parse_file
 * Arguments:
 * token     - param name that needs to be looked up
 * fp        - string formatted path to the file
 */
char *parse_file(FILE *fp, const char *token)
{
    if (!token) {
        fprintf(stderr, "%s: invalid args\n", __func__);
        return NULL;
    }

    char name[128] = "";
    char val[128] = "";
    char pureval[128] = "";

    while (fscanf(fp, "%127[^=]=%127[^\n]%*c", name, val) == 2) {
        if (0 == strcmp(name, token)) {
//            fseek(fp, 0L, SEEK_SET);   //重置 file position indicator，或者用：
            rewind(fp);                  //只有重置了才能重复查找，如果只使用一次可以省略
            if (val[0] == '"') {
                memcpy(pureval, val+1, strlen(val)-2);
                return strdup(pureval);  //用 malloc 分配空间，要记得回收哦
            } else
                return strdup(val);
        }
    }

    return NULL;
}

int main()
{
    struct utsname uts;
	FILE *fp;
	char *pstr;
    char codename[32] = "";

    if (uname(&uts) == -1)
    {
        perror("uname");
        exit(-1);
    }

	fp = fopen(OSRELEASE, "r");
    if (fp == NULL) {
        fprintf(stderr, "%s: %s not found\n", __func__, OSRELEASE);
        exit(-1);
    }

    printf("System:      %s\n", uts.sysname);
    printf("Machine:     %s\n", uts.machine);
    printf("Hostname:    %s\n", uts.nodename);

#ifdef _GNU_SOURCE
    printf("Domain:      %s\n", uts.domainname);
#endif

	pstr = parse_file(fp, "NAME");
	printf("Kernel:      %s\n", pstr);
	free(pstr);     //调用一次 parse_file 就要回收一次
	fclose(fp);     //为了重复利用 fp，先把它指向的文件关掉

    fp = fopen(DEBVERSION, "r");
    fscanf(fp, "%31[^/\n]", codename);   //遇到 '/' 或 '\n' 则停止读取
    printf("Codename:    %s\n", codename);
    fclose(fp);

    printf("Release:     %s\n", uts.release);
    printf("Version:     %s\n", uts.version);

    return 0;
}

