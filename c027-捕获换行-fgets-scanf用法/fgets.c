#include <stdio.h>
#include <stdint.h>

#define COLOR_CYAN    "\x1b[36m"
#define COLOR_RESET   "\x1b[0m"


int main()
{
    while (1) {
        char str[5] = "";
        printf( COLOR_CYAN "(ot) " COLOR_RESET );

        // 最多读取 5-1 个字符，又因为 '\n' 也会放在里面，所以正常情况下只能读取 3 个字符
        // 是这个样子；[char] [char] [char] [\n] [0]
        // 如果输入字符多于 3 个，需要再次调用 fgets 读取
        // 有种特殊情况，如果输入 4 个字符，实际上也能放下，这时缓冲区还剩个 '\n' 在里面
        if (fgets(str, 5 , stdin) == NULL) { /* EOF */
            printf("^D\nbye..\n");
            break;
        }

        //只有在第四个字符既不是\n，也不是\0的时候，
        //也就是说缓冲区里有多余的字符时，才能去清空缓冲区，否则会卡住
        if( *(str+3)!='\n' && *(str+3)!=0 ) {
            scanf("%*[^\n]"); //逐个读取缓冲区中\n之前的其它字符
            scanf("%*c");     //再将这个\n读取并丢弃
        }
        
        /* parse input string */
        uint8_t opt = 0, val = 0;
        __attribute__((unused)) int ret = 0;
        ret = sscanf(str, "%c %hhu\n", &opt, &val); /* d150 这种情况也能解析出来，所以 val 的取值范围不一定是 2 位以下 */
//        printf("ret: %d, str: |%s|\n", ret, str);
        printf("%c, %hhu\n", opt, (val < 31) ? val : 0);
    }

    return 0;
}

