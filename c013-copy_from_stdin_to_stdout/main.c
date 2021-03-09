/* copy from stdin to stdout */
# include <stdio.h>
int main()
{
    int c;
    while( (c = getchar()) !=  EOF )
        putchar(c);
}

