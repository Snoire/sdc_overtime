#include <stdio.h>

int main()
{
    unsigned int rate = 1733453;
    //unsigned int rate = 1733000;
//    struct dev_info
//    {
//        char rate[9];
//    } dev;

#if 0
    if (rate % 1000)
        snprintf(dev.rate, sizeof(dev.rate), "%.1f", rate / 1000.0);
    else
        snprintf(dev.rate, sizeof(dev.rate), "%d", rate / 1000);

    printf("%s\n", dev.rate);
#elif 0
    if (rate % 1000)
        snprintf(dev.rate, sizeof(dev.rate), "%.1f", (rate / 100) / 10.0);
    else
        snprintf(dev.rate, sizeof(dev.rate), "%d", rate / 1000);

    printf("%s\n", dev.rate);
#else
    printf("%d%s\n", rate / 1000, (rate/500 & 1) ? ".5" : "");
#endif

    return 0;
}
