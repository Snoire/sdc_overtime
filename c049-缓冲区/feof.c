#include <stdio.h>

int main()
{
    int ret;
	char buf[1024] = "";

	while (!feof(stdin)) {
        ret = -10;
		ret = scanf("%s\n", buf);
        printf("ret: %d, |%s|\n", ret, buf);
	}

	return 0;
}
