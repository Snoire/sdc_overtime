//https://codereview.stackexchange.com/questions/226293/parse-a-simple-key-value-config-file-in-c
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

#define TEXT "sample.txt"

/* 
 * Function: parse_param_file
 * Arguments:
 * token    - param name that needs to be looked up
 * buf      - buffer for string value. Pass NULL if unwanted
 * buf_int  - buffer for integer value. Pass NULL if unwanted
 * filename - string formatted path to the file 
 */
int parse_param_file(const char *token, char **buf, int *buf_int, const char *filename)
{
    if (!token || (!buf && !buf_int)) {    // token 为 NULL，或者 buf 和 buf_int 同时为 NULL
        fprintf(stderr, "%s: invalid args\n", __func__);
        return 1;
    }
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        fprintf(stderr, "%s: %s not found\n", __func__, filename);
        return 1;
    }

    char *left = malloc(128);
    char *right = malloc(128);
    char *dlim_ptr, *end_ptr;
    char fbuf[256];

    while (fgets(fbuf, 256, f)) {
        dlim_ptr = strstr(fbuf, "=");
        end_ptr = strstr(dlim_ptr, "\n");
        strncpy(left, fbuf, dlim_ptr - fbuf);
        strncpy(right, dlim_ptr + 1, end_ptr - dlim_ptr - 1);
        if (strcmp(left, token) == 0) {
            /* Param found */
            if (buf != NULL)
                *buf = strdup(right);
            if (buf_int != NULL)
                *buf_int = atoi(right);
            fclose(f);
            free(left);
            free(right);
            return 0;
        }
    }
    fclose(f);
    fprintf(stderr, "%s: Param not found in %s\n", __FUNCTION__, filename);
    free(left);
    free(right);
    return 1;
}

/* How to use parse_param_file() */
int main(void) {
    char *buf = malloc(128);
    int val = 0;

    /* Test 1 */
    printf("Test 1: bingo2\n");
    if (parse_param_file("bingo2", NULL, NULL, TEXT))
        fprintf(stderr, "parse_param_file() failed\n");
    printf("buf : %s\n", buf);
    printf("int : %d\n\n", val);

    /* Test 2 */
    printf("Test 2: bingo3242\n");
    if (parse_param_file("bingo3242", NULL, &val, TEXT))
        fprintf(stderr, "parse_param_file() failed\n");
    printf("buf : %s\n", buf);
    printf("int : %d\n\n", val);

    /* You must clear *buf and val if you want to reuse them as args again */
    /* Test 3 */
    printf("Test 3: bingo3\n");
    if (parse_param_file("bingo3", &buf, &val, TEXT))
        fprintf(stderr, "parse_param_file() failed\n");
    printf("buf : %s\n", buf);
    printf("int : %d\n", val);

    free(buf);
    return 0;
}

