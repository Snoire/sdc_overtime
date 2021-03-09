#include <stdio.h>
#include <stdlib.h>

int main () {
    FILE * fp;
    int buffer[4];
    if((fp=fopen("myfile.txt","rb"))==NULL)
    {
      printf("cant open the file");
      exit(0);
    }
    if(fread(buffer,sizeof(int),4,fp)!=4)   //可以一次读取
    {
        printf("file read error\n");
        exit(0);
    }

    for(int i=0;i<4;i++)
        printf("%d\n",buffer[i]);
    return 0;
}
