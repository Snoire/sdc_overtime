#include <stdio.h>

int main()
{
    FILE *fp;
    char buffer[1024] = "";
    
    if ((fp = popen("ip a", "r")) == NULL) {
        perror("popen");
        return -1;
    }

    fgets(buffer, sizeof(buffer), fp);
    printf("%s", buffer);


    pclose(fp);
    return 0;
}
