#include <stdio.h>
#include <string.h>

int main(void)
{
	char str[] = "root:x::0:root:/root:/bin/bash:";
	char *token;
    printf("%s, strlen: %d\n", str, strlen(str));

	token = strtok(str, ":");
	//printf("%s\n", token);
    printf("%s | %s\n", token, str);
	while ( (token = strtok(NULL, ":")) != NULL) {
		printf("%s | %s\n", token, str);
    }
	
    printf("strlen: %d\n", strlen(str));
	return 0;
}
