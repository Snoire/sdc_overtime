//#include <stdio.h>
//#include <stdlib.h>
//int main ()
//{
//  FILE * pFile;
//  char buffer[][12] = {"1", "2"," 3", "4"}; //存入的是字符串
//  if((pFile = fopen ("myfile.txt", "wb"))==NULL)
//  {
//      printf("cant open the file");
//      exit(0);
//  }
//  //可以写多个连续的数据(这里一次写4个)
//  fwrite (buffer , sizeof(char [12]), 4, pFile);
//  fclose (pFile);
//  return 0;
//}

//https://www.cnblogs.com/xudong-bupt/p/3478297.html

#include <stdio.h>
#include <stdlib.h>
int main ()
{
  FILE * pFile;
  int buffer[] = {1, 2, 3, 4};
  if((pFile = fopen ("myfile.txt", "wb"))==NULL)
  {
      printf("cant open the file");
      exit(0);
  }
  //可以写多个连续的数据(这里一次写4个)
  fwrite (buffer , sizeof(int), 4, pFile);
  fclose (pFile);
  return 0;
}
