#include <stdio.h>
#include <stdlib.h>

int main()
{
    char str1[] = "12";
    char str2[] = "1";
    char str3[] = "0.1";
    char str4[] = "2.0";

    printf("%s, %s, %s, %s\n", str1, str2, str3, str4);
    printf("aoti: %d, %d, %d, %d\n", atoi(str1), atoi(str2), atoi(str3), atoi(str4));
    printf("aotf: %f, %f, %f, %f\n", atof(str1), atof(str2), atof(str3), atof(str4));

    return 0;
}
