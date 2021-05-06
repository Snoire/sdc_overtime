#include <stdio.h>
#include <unistd.h>

int main()
{
    for (int i = 0; i < 3; i++) {
        sleep(i);
        printf("sleep: %ds\n", i);
    }

    return 0;
}
