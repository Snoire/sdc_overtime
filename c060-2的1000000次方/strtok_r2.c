#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
	char str[] = "root:x::0:root:/root:/bin/bash:";
	char *token, *saveptr = NULL, *p = str;
    printf("%s, strlen: %ld\n", str, strlen(str));

#if 0
    for (int i = 1; ; i++, p = NULL) {
        token = strtok_r(p, ":", &saveptr);
        if (token == NULL)
            break;
        printf("%d: %s | %s\n", i, token, saveptr);
    }
#else
    /* 这样写更简洁呀 */
    for (int i = 1; (token = strtok_r(p, ":", &saveptr)); i++, p = NULL) {
        printf("%d: %s | %s\n", i, token, saveptr);
    }
#endif

	return 0;
}
