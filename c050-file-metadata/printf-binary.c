#include <stdio.h>

#define WIDTH 36 /* unsigned int: 4*8, white space: 1*7, '\0': 1*1 */

int main()
{
    unsigned int st_mode = 0X81ED;
    printf("st_mode: %#X\n", st_mode);

//    int i = 0, j = i;
//    char stmode[WIDTH] = "";
//    while (st_mode) {              /* print binary number */
//        if (st_mode & 1)
//            stmode[i] = '1';
//        else
//            stmode[i] = '0';
//
//        if ((j+1)%4 == 0) {
//            printf("%d, ", i);
//            ++i;
//            stmode[i] = ' ';
//        }
//
//        ++i;
//        ++j;
//
//        st_mode >>= 1;
//	}
//    printf("%s\n", stmode);

    int i = 0;
    char stmode[WIDTH] = "";
    while (st_mode) {              /* print binary number */
        if ((i+1)%5 == 0) {
            stmode[i] = ' ';
            ++i;
        }

        if (st_mode & 1)
            stmode[i] = '1';
        else
            stmode[i] = '0';

        ++i;

        st_mode >>= 1;
	}
//    printf("%s\n", stmode);        /* 倒序，高位在最后 */
    for (; i; i--)
        printf("%c", stmode[i-1]);   /* 正序，高位在前 */
    printf("\n");


	return 0;
}


