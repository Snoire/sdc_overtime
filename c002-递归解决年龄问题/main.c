//3377.html

# include <stdio.h>

int main()
{
	int age[5],num;
	age[0] = 10;

	for(int i=1;i<5;i++) {
		age[i] = age[i-1]+2;
	}

	printf("please input a number:\n");
	printf("请输入查询的数字:\n");
	scanf("%d",&num);
	printf("第%d个人的年龄是：%d岁\n",num,age[num-1]);

    return 0;
}
