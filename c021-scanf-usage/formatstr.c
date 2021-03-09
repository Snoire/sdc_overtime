#include <stdio.h>
#include <string.h>

int main()
{
    char str[10] = "";
    char name[10] = "";
    char val[10] = "";
    char pureval[10] = "";
    int a = 0, b = 0, c = 0;
/*
    printf("输入三个整形，隔以空白符\n");
    scanf("%d %d %d", &a, &b, &c);               //即使两个整形之间输入多个空白符（空格、TAB、换行），也同样可以匹配
    printf("a: %d, b: %d, c: %d\n", a, b, c);
*/ /*
    printf("输入a=%%d b=%%d c=%%d\n");
    scanf("a=%d b=%d c=%d", &a, &b, &c);         //如果输入 a=1 b=c'\n'，那么只有 a 能读到数据
    printf("a: %d, b: %d, c: %d\n", a, b, c);
*/ /*
    printf("输入a=%%d b=%%d c=%%d\n");
    scanf("a=%d b=%*d c=%d", &a, &c);            //读取 b，但是不用（但是你输入的时候要有 b）
    printf("a: %d, b: %d, c: %d\n", a, b, c);
*/ /*
    printf("%%[^]0-9-]\n");
    scanf("%[^]0-9-]", str);                     //读取一串字符，遇到 0-9、'-'、']'，或者遇到（如果指定）width 停止读取
    printf("str: %s\n", str);                    //换行符（空白符）也能读取哦
*/ /*
    printf("%%9[^]0-9-]\n");
    scanf("%9[^]0-9-]", str);                    //最多读取 9 个字符，要是指定 10，就没地方放 '\0' 了
    printf("str: %s\n", str);                    // man 手册页上说，空白符不计算在 width 里面，试了一下，好像不是这样
*/ /*
    printf("%%9[^]0-9-\\n]\n");
    scanf("%9[^]0-9-\n]", str);                  //再多加一个换行符 
    printf("str: %s\n", str);                    
*/ /*
    printf("%%9[^=]=%%9[^\\n]\n");
    scanf("%9[^=]=%9[^\n]", name, val);          //读取 name=val 
    printf("name: %s, val: %s\n", name, val);                    
*/ /*
    printf("%%9[^=]=\"%%9[^\"\\n]%%*c\n");
    scanf("%9[^=]=\"%9[^\"\n]%*c", name, val);          //读取 name="val"，最后把换行符也读取了，随之舍去 
    printf("name: %s, val: %s\n", name, val);                    
*/
    printf("读取 name=val 和 name=\"val\" 混合类型\n");
    scanf("%9[^=]=%9[^\n]", name, val);                 //读取 name=val 和 name="val" 混合类型 
    if (val[0] == '"')                                  //什么，你问我为什么要自找麻烦？去看一下 /usr/lib/os-release 的格式就知道了
        memcpy(pureval, val+1, strlen(val)-2);
    else
        memcpy(pureval, val, strlen(val));

    printf("name: %s, val: %s\n", name, pureval);                    

    return 0;
}

