#include <stdio.h>
#include <stdlib.h>

char *getstr() {
    char *line = malloc(100), *linep = line;
    size_t lenmax = 100, len = lenmax;
    int c;

    if (line == NULL)
        return NULL;

    for (;;) {
        c = fgetc(stdin);
        if (c == EOF)
            break;

        if (--len == 0) {
            len = lenmax;
            char *linen = realloc(linep, lenmax *= 2);

            if(linen == NULL) {
                free(linep);
                return NULL;
            }
            line = linen + (line - linep);
            linep = linen;
        }

        if ((*line++ = c) == '\n')
            break;
    }
    *(line-1) = '\0'; //把最后的换行去掉
    return linep;
}

int main()
{
    char *p;
    p = getstr();
    printf("p = |%s|\n", p);

    return 0;
}


