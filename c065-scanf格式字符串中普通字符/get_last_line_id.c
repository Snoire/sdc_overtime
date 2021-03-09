#include <stdio.h>

int read_last_line_id(const char *file, char *log_id)
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
    } while (ch != '\n');

    fscanf(fp, "logId<%15[^>]", log_id);
    fclose(fp);

    return 0;
}

int main()
{
    int ret;
    char log_id[16] = "";

    ret = read_last_line_id("log.txt", log_id);
    printf("ret: %d, last line: |%s|\n", ret, log_id);

    return 0;
}

