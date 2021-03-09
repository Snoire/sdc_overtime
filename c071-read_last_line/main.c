#include <stdio.h>

int read_last_line(const char *file, char *last_line)
{
    int i = -1;
    char ch;
	FILE *fp;

	if ((fp = fopen(file, "r")) == NULL)
        return -1;
	
    do {  // 从最后往前找 \n
        i--;   // 最后一个可能是 \n，所以从 -2 开始
        fseek(fp, i, SEEK_END);
        ch = fgetc(fp);
//        printf("ch: |%c|\n", ch);  // debug
    } while (ch != '\n');

//    fgets(last_line, 1024, fp);
//    printf("last line: |%s|\n", last_line);  // debug
    fscanf(fp, "logId<%15[^>]", last_line);
    fclose(fp);

    return 0;
}

int main()
{
    int ret;
    char last_line[1024] = "";

    ret = read_last_line("log.txt", last_line);
    printf("ret: %d, last line: |%s|\n", ret, last_line);

    return 0;
}

