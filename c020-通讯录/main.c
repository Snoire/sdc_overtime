#include<stdio.h>
#include<string.h>

//定义宏，联系人数组的长度，姓名长度，电话号码的长度 
#define NAME_LEN 22
#define TELNUM_LEN 16
#define LEN 100

typedef struct{    //这里少了一个结构体名，这样做，使得只能定义一次变量?
	char name[NAME_LEN];
	char telNum[TELNUM_LEN];
} Person; //给结构体起一个别名

//定义联系人数组，保存联系人个数，文件的名称
Person contacts[LEN];
int totalContactCount=0;
char *filePath="telbook.data";

//声明函数
void doAdd();
void doDelete();
void doUpdate();
void doList();
void doSearchByName();
void init();
void writeToFile();
 
char c; //用来清空输入缓冲区
 
int main()
{
	init();
	int flag = 1;//退出的标志
	int num = 0;
	while(flag)
	{	
		//编写控制程序
		printf("\n\n **************************\n");
		printf("****** 欢迎使用通讯录 ******\n");
		printf("****** 1、添加联系人  ******\n");
		printf("****** 2、删除联系人  ******\n");
		printf("****** 3、修改联系人  ******\n");
		printf("****** 4、查看联系人  ******\n");
		printf("****** 5、搜索联系人  ******\n");
		printf("****** 6、退出此系统  ******\n");
		printf(" **************************\n\n");
	
		printf("请输入1-6之间的序号，选择要执行的功能\n");
		//接收用户输入的编号
		
		scanf("%d",&num);   //如果这里输入字母，会一直死循环
                            //http://c.biancheng.net/cpp/html/3101.html
        while((c = getchar()) != '\n' && c != EOF); //在下次读取前清空缓冲区
                            //http://c.biancheng.net/cpp/html/3102.html
		if(num<1||num>6)
			printf("输入错误！\n");
		else
        {
			//根据不同的编号，执行不同的功能
			switch(num)
            {
				case 1:
					doAdd();
					break;
				case 2:
					doDelete();
					break;
				case 3:
					doUpdate();
					break;
				case 4:
					doList();
					break;
				case 5:
					doSearchByName();
					break;
				case 6:
					printf("正在退出系统...\n");
					printf("系统已经退出!\n");
					//return 0;
					flag = 0;
					break;
				default:
					break;
			} 
		}
	} 
    return 0;
}
 
 
 /**
 *  添加联系人
	1) 提示用户输入联系人信息
	2）接收联系人信息
	3）提示输入电话号码信息
	4）接收电话号码

	5）让用户再次确认添加联系人    1 确认  0 取消
	6）保存联系人信息到 联系人数组中
	7）让联系人的个数+1

	8) 把最新的数组，重新保存到文件中
 */
 
void doAdd(){
	printf("您正在执行的是添加联系人的操作：\n");
	
	//1. 提示用户输入联系人信息
	printf("请输入联系人姓名：     [*联系人姓名中间不能有空格，空格之后内容将被忽略]\n");
	 
	//2. 接受联系人信息
	char name[NAME_LEN];
	char telNum[TELNUM_LEN];

	scanf("%s",name);
    while((c = getchar()) != '\n' && c != EOF); //在下次读取前清空缓冲区

	//3.提示输入电话号码信息
	printf("请输入联系人电话号码:  [*联系人号码中间不能有空格]\n");
	//4）接收电话号码
	scanf("%s",telNum); 
    while((c = getchar()) != '\n' && c != EOF); //在下次读取前清空缓冲区
	 
	 
	//5.让用户再确认
		
	int queren = 0;
	printf("修改后联系人信息后，数据无法恢复，请确认修改: 0.取消  1.确认\n");
	scanf("%d",&queren);
    while((c = getchar()) != '\n' && c != EOF); //在下次读取前清空缓冲区
	
	if(queren){
		strcpy(contacts[totalContactCount].name, name);
		strcpy(contacts[totalContactCount].telNum, telNum);
	//  strcpy(contacts[totalContactCount].name,name);
		//strcpy(contacts[totalContactCount].telNum,telNum);
		
		totalContactCount++;
		writeToFile();
	} 
	printf("添加联系人成功！\n");
 }
 
 
 
 /**
 *  删除联系人
	1)提示用户输入一个要删除的联系人的编号
	2）判断编号是否合法
	3）再判断 要删除的元素 是否是数组的最后一个元素
		  如果是最后一个元素，总人数-1
		  如果不是最后一个元素，也就是中间的元素

		  移动元素
		   i = 编号   i< 总   i++

			  a[编号-1] = a[编号]

		  总人数-1

	 4)同步写入到文件中
 */
 
void doDelete(){
	printf("您正在执行的是删除联系人的操作：\n");
	doList();
	
	// 1 . 提示用户输入要删除的联系人的编号
	int nn;
	printf("请输入一个要删除的联系人的编号：\n");
	scanf("%d",&nn);
    while((c = getchar()) != '\n' && c != EOF); //在下次读取前清空缓冲区

	if(nn<1||nn>totalContactCount){
		return;
	} 
	 
	int queren = 0;
	printf("联系人删除后，无法恢复，请确认是否要删除：0 取消 1 确认");
	scanf("%d",&queren);
    while((c = getchar()) != '\n' && c != EOF); //在下次读取前清空缓冲区

	if(queren){
		if(nn==totalContactCount){
			totalContactCount--;
		}else{
			for(int i = nn; i <totalContactCount;i++){
				contacts[i-1]=contacts[i];
			}
			totalContactCount--;
		}
		writeToFile();
	}
	  
}
 
 /**
 *  修改联系人
	1) 提示用户输入一个联系人的编号
	2) 判断编号是否合法
	3）让用户输入新的联系人姓名和电话
	4) 接收用户的输入

	5）让用户再次确认删除
	6）把原来的姓名和电话进行更新
	7）同步保存到文件中
 */
 
void doUpdate(){
	printf("您正在执行的是修改联系人操作：\n");
	doList();
	
	int nn;
	printf("请输入一个要修改联系人的编号：\n");
	scanf("%d",&nn);
    while((c = getchar()) != '\n' && c != EOF); //在下次读取前清空缓冲区
	
	if(nn<1||nn>totalContactCount){
		return;
	}
	 
	char name[NAME_LEN];
	char telNum[TELNUM_LEN];

	printf("请输入联系人的姓名：   【*联系人姓名中间不能有空格】");
	scanf("%s",name);
    while((c = getchar()) != '\n' && c != EOF); //在下次读取前清空缓冲区
	printf("请输入联系人的电话：   【*联系人电话中间不能有空格】");
	scanf("%s",telNum); 
    while((c = getchar()) != '\n' && c != EOF); //在下次读取前清空缓冲区

	int queren = 0;
	printf("修改后的联系人信息后，数据无法恢复，请确认修改： 0 取消 1 确认");
	scanf("%d",&queren);
    while((c = getchar()) != '\n' && c != EOF); //在下次读取前清空缓冲区

	if(queren){
		strcpy(contacts[nn-1].name,name);
		strcpy(contacts[nn-1].telNum,telNum);
		
		writeToFile();
	} 
}
 
 
/**
 *  查询所有的联系人
	思路：
	1)先判断 totalContactCount == 0
	  如果等于0 表示没有联系人，提示：通讯录空无一人

		 不等于0 打印所有的联系人

	2）循环

	3）遍历输出所有的联系人信息
 */
 
void doList(){
	
	printf("您正在执行的是查询所有的联系人的操作：\n");
	
	if(totalContactCount==0){
		printf("您的通信录还很寂寞！\n");
		
	}else{
		printf("编号\t\t姓名\t\t电话\t\t\n");  //这里如果名字长短不一，可能会影响对齐
		for(int i = 0 ; i<totalContactCount;i++){
			printf("%d\t\t%s\t\t%s\t\t\n",i+1,contacts[i].name,contacts[i].telNum);
		}
	}
}
 
 
 
 /**
 * 搜索联系人
   1) 提示用户输入一个联系人的姓名
   2）接收这个姓名
   3）循环，遍历数组
	  //进行字符串的比较
	  //strcmp(contacts[i].name,name) == 0
	  //如果查找到了，输出这个联系人的电话号码

	  //如果没有查找到，提示：没有查找到

 */
 
void doSearchByName(){
	printf("您正在执行的是搜索联系人的操作：\n");
	
	char name[NAME_LEN];
	printf("请输入联系人的姓名：  【*联系人的姓名中间不能有空格】\n");
	scanf("%s",name);
    while((c = getchar()) != '\n' && c != EOF); //在下次读取前清空缓冲区
	
	int i ;
	for( i = 0 ; i < totalContactCount;i++){
		if(strcmp(contacts[i].name,name)==0){
			printf("您要查的联系人：%s的电话是：%s\n",name,contacts[i].telNum);
		break;
		}
	} 
	 
	if(i==totalContactCount){
		printf("对不起没有查到%s这个人！",name); 
	}
}
 
 
 /**
 *  初始化函数
	思路：

	1）定义文件指针，并且（尝试）打开文件
	2）如果能够打开这个文件(说明文件已经存在了)

		  i.把文件中存放联系人数量读取出来
		  ii.根据联系人的数量，把联系人信息全部读取出来，放到联系人数组中

	   如果文件打开失败了

		  i.创建文件
		  ii.写入联系人数量  0

	3）关闭文件指针
 */
 
 
void init(){
	printf("系统正在初始化.......\n");
	
	FILE *fp = fopen(filePath,"r");
	
	if(fp!=NULL){
		fread(&totalContactCount,sizeof(totalContactCount),1,fp);
		
		for(int i = 0 ; i < totalContactCount;i++){
			fread(&contacts[i],sizeof(Person),1,fp);
		}
	}else{
		fp = fopen(filePath,"w");
		
		fwrite(&totalContactCount,sizeof(totalContactCount),1,fp);
		printf("通讯录文件创建成功！\n");
	}
	fclose(fp);
	fp=NULL;
	printf("系统初始化完成！\n");
}
 
 /**
 *  把数组的内容重新写入到文件中
	1）打开文件，w
	2）判断是否打开成功
	3）先把联系人的数量写入到文件中
	4）把每个联系人的数据，都写入到文件中

	5）关闭文件
 */
 
 
void writeToFile(){
	FILE *fp = fopen(filePath,"w");
	if(fp!=NULL){
		fwrite(&totalContactCount,sizeof(totalContactCount),1,fp);
		for(int i = 0 ; i < totalContactCount;i++){
			fwrite(&contacts[i],sizeof(Person),1,fp);
		}
		printf("数据更新完毕！\n");
	}
	fclose(fp);
}
