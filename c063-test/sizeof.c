#include <stdio.h>

typedef union {
    long i;     // 8
    int k[5];   // 4 * 5
    char c;     // 1
    int *x[5];  // 8 * 5
} DATE;

typedef struct {
    int cat;    // 4 (+4 padding)
    DATE cow;   // 40
    double dog; // 8
} Data;

DATE date;


struct test {   // 为啥上面是 8 字节对齐，这里就是 4 字节了？
    char ch;    // 1 (+3)
    int i;      // 4
    short s;    // 2 (+2)
};

#pragma pack(4)
struct test1 {
    char ch;    // 1 (+3)
    int i;      // 4
    short s;    // 2 (+2)
};
#pragma pack()

#pragma pack(2)
struct test2 {
    char ch;    // 1 (+1)
    int i;      // 4
    short s;    // 2
};
#pragma pack()

int main()
{
    printf("char: %zu, short: %zu, int: %zu, long: %zu, long long: %zu\n"
            "float: %zu, double: %zu\n"
            "Data: %zu, DATE: %zu\n"
            "test: %zu, test1: %zu, test2: %zu\n",
            sizeof(char), sizeof(short), sizeof(int),
            sizeof(long), sizeof(long long),
            sizeof(float), sizeof(double),
            sizeof(Data), sizeof(DATE),
            sizeof(struct test), sizeof(struct test1), sizeof(struct test2));
    return 0;
}
