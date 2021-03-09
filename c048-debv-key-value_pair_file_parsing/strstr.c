#include <stdio.h>
#include <string.h>
 
 
int main()
{
   const char key_val_pair[20] = "RUNOOB=runoob";
   const char equalsign[10] = "=";
   char *ret;
   char name[32] = "";
   char val[32] = "";
 
//   ret = strstr(key_val_pair, equalsign);   // strstr 和 strchr 都行
   ret = strchr(key_val_pair, '=');
 
   printf("子字符串是：|%s|\n", ret);
   printf("ret[0]: %c\n", ret[0]);

   memcpy(name, key_val_pair, ret-key_val_pair); //这里虽然只复制到 '='，没有 '\0'，但是初始化的时候，后面是有的。
   memcpy(val, ret+1, strlen(key_val_pair)-(ret-key_val_pair)-1);

   printf("ret-key_val_pair: %d\n", ret-key_val_pair);
   printf("strlen(key_val_pair): %d\n", strlen(key_val_pair));

   printf("name: %s\n", name);
   printf("val: %s\n", val);
   
   return(0);
}
