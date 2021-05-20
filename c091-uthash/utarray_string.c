#include <stdio.h>
#include "utarray.h"

int main()
{
    UT_array *strs;
    char *s, **p;

    utarray_new(strs, &ut_str_icd);

    s = "hello";
    utarray_push_back(strs, &s);
    s = "world";
    utarray_push_back(strs, &s);

    p = NULL;                   /* 这样写就能从第一个开始数了 */
    while ((p = (char **) utarray_next(strs, p))) {
        printf("%s\n", *p);
    }

    utarray_free(strs);

    return 0;
}
