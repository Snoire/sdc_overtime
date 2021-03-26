#include <stdio.h>

int main()
{
    //unsigned int rate = 1733333;
    unsigned int rate = 1733000;
    struct dev_info
    {
        char rate[9];
    } dev;

    if (rate % 1000)
        snprintf(dev.rate, sizeof(dev.rate), "%.1f", rate / 1000.0);
    else
        snprintf(dev.rate, sizeof(dev.rate), "%d", rate / 1000);

    printf("%s\n", dev.rate);

    return 0;
}
