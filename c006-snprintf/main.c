#include <stdio.h>
#include <stdlib.h>
int main()
{
#if 1
    char str[8] = "";
    int *p = NULL;
//    snprintf(str, sizeof(str), "123456789");
//    snprintf(str, 8, "123456789");
    snprintf(str, sizeof(str), "123456789");  // 由此看出，这边 sizeof 不用减 1

    printf("str[7]: %d\n", str[7]);
    printf("str: |%s|\n", str);
    printf("p: |%p|\n", p);
#else
	char dst1[10] ={0, },dst2[10] ={0, };
	char src1[10] ="aaa",src2[15] ="aaabbbcccddd";
	int size=sizeof(dst1);
	int ret1=0, ret2=0;

	ret1=snprintf(dst1, size, "str :%s", src1);
	ret2=snprintf(dst2, size, "str :%s", src2);
	printf("sizeof(dst1)=%d, src1=%s, \"str :%%s\"=%s%s, dst1=%s, ret1=%d, sizeof(src1)=%d\n", sizeof(dst1), src1, "str :", src1, dst1, ret1, sizeof(src1));
	printf("sizeof(dst2)=%d, src2=%s, \"str :%%s\"=%s%s, dst2=%s, ret2=%d\n", sizeof(dst2), src2, "str :", src2, dst2, ret2);
#endif

	return 0;
}
