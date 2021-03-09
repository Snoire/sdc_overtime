#include <unistd.h>
#include <stdio.h>
int main(int argc, char * argv[])
{
    
    int i;
    printf("--------------------------\n");
    for(i=0;i<argc;i++)
    {
        printf("%s\n",argv[i]);
    }
    printf("--------------------------\n");
       //int aflag=0, bflag=0, cflag=0;
    
       int ch;
    printf("\n\n");
    printf("optind:%d，opterr：%d\n",optind,opterr);
    printf("--------------------------\n");
       while ((ch = getopt(argc, argv, "ab:c:de::")) != -1)
       {
        printf("optind: %d\n", optind);
           switch (ch) 
        {
               case 'a':
                       printf("HAVE option: -a\n\n");   
                       break;
               case 'b':
                       printf("HAVE option: -b\n"); 
                       printf("The argument of -b is %s\n\n", optarg);
                       break;
               case 'c':
                       printf("HAVE option: -c\n");
                       printf("The argument of -c is %s\n\n", optarg);
                       break;
               case 'd':
                   printf("HAVE option: -d\n");
                     break;
              case 'e':
                    printf("HAVE option: -e\n");
                    printf("The argument of -e is %s\n\n", optarg);
                  break;
              case '?':
                       printf("Unknown option: %c\n",(char)optopt);
                       break;
               }
       }
    
       printf("----------------------------\n");
      printf("optind=%d,argv[%d]=%s\n",optind,optind,argv[optind]);

    printf("--------------------------\n");
    for(i=0;i<argc;i++)
    {
        printf("%s\n",argv[i]);
    }
    printf("--------------------------\n\n");
    printf("输入: c9 zheng -b \"参数b\" han -c123 参数c \n你就能看到 getopt 多次执行后\n把选项和对应的参数按顺序放在前面，\n而其它既不是选项又不是参数的按顺序放在后面，\n而且把 optind 指向第一个非选项也非选项参数的字符\n");
    
	return 0;
}
