#include <stdio.h>

int main()
{
    char tlist_1[1024] = "", tlist_2[1024] = "";
    char fname[7][8] = { "a1", "b1", "c1", "d1", "e1", "f1", "g1" };
    int i = 0, len_1, len_2 = 0;

    len_1 = snprintf(tlist_1, 1024, "%s;", fname[0]);
    len_2 = snprintf(tlist_2, 1024, "%s;", fname[0]);

    for (i = 1; i < 7; i++) {
        len_1 = snprintf(tlist_1, 1024, "%s%s;", tlist_1, fname[i]); /* snprintf 就不可以这样扩展了 */
        len_2 = sprintf(tlist_2, "%s%s;", tlist_2, fname[i]);  /* sprintf 居然可以自己给自己赋值 */
    }

    printf("tlist_1: %s\n", tlist_1);
    printf("tlist_2: %s\n", tlist_2);

    printf("由此可以看出 snprintf 和 sprintf 是不同的\n");
    printf("snprintf 在写入字符串前会把字符串清空，所以不会叠加\n");

    return 0;
}
